"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import argparse
import importlib
import os
import re
import sys
from pathlib import Path
import jinja2


# 类型 -> pybind11 辅助 getter 函数名映射
TYPE_GETTER_MAP = {
    "int": "Int",
    "unsigned int": "UnsignedInt",
    "char": "Char",
    "string": "String",
    "double": "Double",
    "long long": "LongLong",
    "unsigned long long": "UnsignedLongLong",
    "unsigned short": "UnsignedShort",
    "unsigned char": "UnsignedChar",
}

# 内置 TAP 类型映射（不依赖外部模块）
TAP_TYPE_MAP = {
    "TAPIINT32": "int",
    "TAPIUINT32": "unsigned int",
    "TAPIINT64": "long long",
    "TAPIUINT64": "unsigned long long",
    "TAPIUINT16": "unsigned short",
    "TAPIUINT8": "unsigned char",
    "TAPIYNFLAG": "char",
    "TAPIYNFLAG2": "char",
    "TAPICHAR": "char",
    "TAPISTR_10": "string",
    "TAPISTR_20": "string",
    "TAPISTR_30": "string",
    "TAPISTR_40": "string",
    "TAPISTR_50": "string",
    "TAPISTR_70": "string",
    "TAPISTR_100": "string",
    "TAPISTR_300": "string",
    "TAPISTR_500": "string",
    "TAPISTR_2000": "string",
    "TAPIDATE": "string",
    "TAPITIME": "string",
    "TAPIRightIDType": "int",
    "TAPILOGLEVEL": "int",
}


class ApiGenerator:
    """API生成器"""

    def __init__(self, filename: str, prefix: str, name: str, class_name: str, output_dir: str):
        self.filename = filename
        self.prefix = prefix
        self.name = name
        self.class_name = class_name

        self.sub_dir = Path(output_dir) / f"{prefix}{name}"
        self.sub_dir.mkdir(parents=True, exist_ok=True)

        self.callbacks: dict[str, dict[str, str]] = {}
        self.functions: dict[str, dict[str, str]] = {}
        self.lines: dict[str, str] = {}
        self.global_functions: dict[str, dict[str, str]] = {}
        self.wrapped_globals: dict[str, dict] = {}  # <-- 新增：待包装为成员方法的全局函数

        self.structs: dict[str, dict[str, str]] = {}
        self.typedefs: dict[str, str] = {}
        self.load_constant()
        self.load_struct()

        self.jinja_env = jinja2.Environment(
            trim_blocks=True,
            lstrip_blocks=True,
            keep_trailing_newline=True
        )
        template_dir = Path(__file__).parent / "templates"
        if not template_dir.exists():
            raise RuntimeError(f"模板目录不存在: {template_dir}")
        self.jinja_env.loader = jinja2.FileSystemLoader(str(template_dir))
        self.header_template = self.jinja_env.get_template("tap_header.j2")
        self.source_template = self.jinja_env.get_template("tap_source.j2")

        if self.name == "md":
            self.base_class_name = "ITapQuoteAPINotify"
            self.api_type = "ITapQuoteAPI"
            self.module_name = "tapmd"
            self.pybind_var = "tapmd"
            self.namespace = ""
        else:
            self.base_class_name = "ITapTrade::ITapTradeAPINotify"
            self.api_type = "ITapTrade::ITapTradeAPI"
            self.module_name = "taptd"
            self.pybind_var = "taptd"
            self.namespace = "ITapTrade"

        self.ns_prefix = f"{self.namespace}::" if self.namespace else ""
        self.file_prefix = f"{self.prefix}{self.name}"

    def load_constant(self) -> None:
        if self.name == "md":
            module_names = ["tap_md_common_typedef", "tap_md_data_typedef"]
        elif self.name == "td":
            module_names = ["tap_td_common_typedef", "tap_td_data_typedef"]
        else:
            module_names = []

        for module_name in module_names:
            try:
                module = importlib.import_module(module_name)
                for name in dir(module):
                    if "__" not in name:
                        self.typedefs[name] = getattr(module, name)
                print(f"[+] 加载结构体模块: {module_name}, 共 {len([n for n in dir(module) if '__' not in n])} 个定义")
            except ModuleNotFoundError:
                print(f"[-] 无法加载结构体模块: {module_name}, 错误: {e}")

    def load_struct(self) -> None:
        if self.name == "md":
            module_names = ["tap_md_data_struct", "tap_md_common_struct"]
        elif self.name == "td":
            module_names = ["tap_td_data_struct", "tap_td_common_struct"]
        else:
            module_names = []

        for module_name in module_names:
            try:
                module = importlib.import_module(module_name)
                for name in dir(module):
                    if "__" not in name:
                        self.structs[name] = getattr(module, name)
                print(f"[+] 加载结构体模块: {module_name}, 共 {len([n for n in dir(module) if '__' not in n])} 个定义")
            except ModuleNotFoundError:
                print(f"[-] 无法加载结构体模块: {module_name}, 错误: {e}")

    def _resolve_type(self, tap_type: str) -> str:
        """将 TAP 类型解析为 C++ 友好类型。遇到结构体（映射为 'dict'）时返回原始类型名。"""
        base = tap_type.replace("const ", "").replace(" ", "").replace("*", "").replace("&", "")
        if "::" in base:
            base = base.split("::")[-1]

        # 先查内置表
        mapped = TAP_TYPE_MAP.get(base)
        if mapped:
            return mapped

        # 再查动态加载的 typedefs（可能是 'int'/'string'/'dict' 等）
        mapped = self.typedefs.get(base, base)
        if mapped and mapped != base:
            if mapped == "dict":           # 保留
                return base
            if mapped in TAP_TYPE_MAP:
                return TAP_TYPE_MAP[mapped]
            return mapped

        return base

    def _is_string_type(self, tap_type: str) -> bool:
        base = tap_type.replace("const ", "").replace(" ", "").replace("*", "").replace("&", "")
        if "::" in base:
            base = base.split("::")[-1]
        return base.startswith("TAPISTR") or base in ("TAPICHAR", "TAPIDATE", "TAPITIME")

    def _is_struct_type(self, cpp_type: str) -> bool:
        return cpp_type in self.structs

    def _is_primitive_type(self, cpp_type: str) -> bool:
        return cpp_type in ("int", "unsigned int", "long long", "unsigned long long",
                           "short", "unsigned short", "char", "unsigned char",
                           "double", "bool")

    def run(self) -> None:
        with open(self.filename, encoding='utf-8', errors='ignore') as f:
            for line in f:
                self.process_line(line)

        self.generate_header_define()
        self.generate_header_process()
        self.generate_header_on()
        self.generate_header_function()

        self.generate_source_task()
        self.generate_source_switch()
        self.generate_source_process()
        self.generate_source_function()
        self.generate_source_on()
        self.generate_source_module()
        self.generate_source_global()

        self.assemble()
        print(f"{self.name}_API生成成功 -> {self.sub_dir}")

    def process_line(self, line: str) -> None:
        stripped = line.strip()
        if not stripped or stripped.startswith("//") or stripped.startswith("/*") or stripped.startswith("*"):
            return
        if "//" in stripped:
            stripped = stripped[:stripped.index("//")].strip()

        line = stripped.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("\t", " ")
        line = line.replace("{}", "")
        line = re.sub(r'\s*=\s*[^,()]+', '', line)

        if "virtual" in line and "TAP_CDECL" in line and "(" in line:
            func_match = re.search(r'TAP_CDECL\s+(\w+)\s*\(', line)
            if func_match:
                func_name = func_match.group(1)
                if func_name.startswith("On"):
                    self.process_callback(line)
                else:
                    self.process_function(line)
        elif "TAP_DLLEXPORT" in line and "TAP_CDECL" in line and "(" in line and "virtual" not in line:
            self.process_global_function(line)

    def process_callback(self, line: str) -> None:
        name = line[line.index("On"):line.index("(")]
        line = line.replace("        ", "")
        line = line.replace(" = 0", "")
        line = line.replace(" TAP_CDECL", "")
        if "virtual  void  " in line:
            line = line.replace("virtual  void  ", "virtual void ")
        self.lines[name] = line
        self.callbacks[name] = self.generate_arg_dict(line)

    def process_function(self, line: str) -> None:
        name = line[line.index("TAP_CDECL") + 9 : line.index("(")].strip()
        self.functions[name] = self.generate_arg_dict(line)
        self.lines[name] = line

    def process_global_function(self, line: str) -> None:
        match = re.search(r'TAP_CDECL\s+(\w+)\s*\(', line)
        if not match:
            return
        global_name = match.group(1)

        wrapped = {
            "CreateTapQuoteAPI": ("int", "createTapQuoteAPI"),
            "SetTapQuoteAPIDataPath": ("int", "setTapQuoteAPIDataPath"),
            "SetTapQuoteAPILogLevel": ("int", "setTapQuoteAPILogLevel"),
            "GetTapQuoteAPIVersion": ("string", "getTapQuoteAPIVersion"),
            "CreateITapTradeAPI": ("int", "createITapTradeAPI"),
            "GetITapTradeAPIVersion": ("string", "getITapTradeAPIVersion"),
            "GetITapErrorDescribe": ("string", "getITapErrorDescribe"),
        }

        if global_name in wrapped:
            ret_type, py_name = wrapped[global_name]
            d = self.generate_arg_dict(line)

            # Create 函数只暴露 dict 参数，result 由内部处理，避免变量名冲突
            if global_name in ("CreateTapQuoteAPI", "CreateITapTradeAPI"):
                self.wrapped_globals[py_name] = {
                    "ret_type": ret_type,
                    "args": {"req": "const dict"},
                    "_global_name": global_name
                }
            else:
                self.wrapped_globals[py_name] = {
                    "ret_type": ret_type,
                    "args": d,
                    "_global_name": global_name
                }
            self.lines[py_name] = line
        else:
            self.global_functions[global_name] = self.generate_arg_dict(line)
            self.lines[global_name] = line

    def generate_arg_dict(self, line: str) -> dict:
        args_str = line[line.index("(") + 1:line.index(")")]
        if not args_str:
            return {}
        d = {}
        for arg in args_str.split(","):
            arg = arg.strip()
            if not arg:
                continue
            if arg.startswith("const "):
                arg = arg[6:]
            if " " in arg:
                idx = arg.rfind(" ")
                type_part = arg[:idx].strip()
                name_part = arg[idx+1:].strip()
                name = name_part.replace("*", "").replace("&", "").strip()
                tap_type = type_part.replace("*", "").replace("&", "").strip()
                if name_part.startswith("*"):
                    tap_type += "*"
                if name and tap_type:
                    d[name] = tap_type
        return d

    def _write_to_subdir(self, filename: str, content_generator):
        filepath = self.sub_dir / filename
        with open(filepath, "w", encoding='utf-8') as f:
            content_generator(f)

    def generate_header_define(self) -> None:
        def write_content(f):
            for n, name in enumerate(self.callbacks.keys()):
                f.write(f"#define {name.upper()} {n}\n")
        self._write_to_subdir(f"{self.file_prefix}_header_define.h", write_content)

    def generate_header_process(self) -> None:
        def write_content(f):
            for name in self.callbacks.keys():
                name = name.replace("On", "process", 1)
                f.write(f"void {name}(Task *task);\n\n")
        self._write_to_subdir(f"{self.file_prefix}_header_process.h", write_content)

    def generate_header_on(self) -> None:
        def write_content(f):
            for function_name, d in self.callbacks.items():
                on_name = function_name.replace("On", "on", 1)
                args_list = []
                for name, tap_type in d.items():
                    cpp_type = self._resolve_type(tap_type)
                    if self._is_string_type(tap_type):
                        args_list.append(f"const string &{name}")
                    elif self._is_primitive_type(cpp_type):
                        if cpp_type == "unsigned int":
                            args_list.append(f"unsigned int {name}")
                        elif cpp_type == "unsigned short":
                            args_list.append(f"unsigned short {name}")
                        elif cpp_type == "unsigned long long":
                            args_list.append(f"unsigned long long {name}")
                        elif cpp_type == "long long":
                            args_list.append(f"long long {name}")
                        elif cpp_type == "double":
                            args_list.append(f"double {name}")
                        elif cpp_type == "bool":
                            args_list.append(f"bool {name}")
                        elif cpp_type == "char":
                            args_list.append(f"char {name}")
                        else:
                            args_list.append(f"int {name}")
                    else:
                        # 默认视为结构体（dict）
                        args_list.append(f"const dict &{name}")
                args_str = ", ".join(args_list)
                f.write(f"virtual void {on_name}({args_str}) {{}};\n\n")
        self._write_to_subdir(f"{self.file_prefix}_header_on.h", write_content)

    def generate_header_function(self) -> None:
        def write_content(f):
            for function_name, d in self.functions.items():
                if function_name == "SetAPINotify":
                    f.write(f"int setAPINotify();\n\n")
                    continue

                req_name = function_name[0].lower() + function_name[1:]
                args_list = []
                for name, tap_type in d.items():
                    cpp_type = self._resolve_type(tap_type)
                    if cpp_type == "unsigned int" or name == "sessionID":
                        continue  # sessionID，内部处理
                    elif self._is_string_type(tap_type):
                        args_list.append(f"const string &{name}")
                    elif self._is_primitive_type(cpp_type):
                        if cpp_type == "unsigned int":
                            args_list.append(f"unsigned int {name}")
                        elif cpp_type == "unsigned short":
                            args_list.append(f"unsigned short {name}")
                        elif cpp_type == "unsigned long long":
                            args_list.append(f"unsigned long long {name}")
                        elif cpp_type == "long long":
                            args_list.append(f"long long {name}")
                        elif cpp_type == "double":
                            args_list.append(f"double {name}")
                        elif cpp_type == "bool":
                            args_list.append(f"bool {name}")
                        elif cpp_type == "char":
                            args_list.append(f"char {name}")
                        else:
                            args_list.append(f"int {name}")
                    else:
                        # 默认视为结构体指针
                        args_list.append(f"const dict &{name}")
                args_str = ", ".join(args_list)
                f.write(f"int {req_name}({args_str});\n\n")

            # 追加：全局函数包装为成员方法声明（vnpy 风格）
            for py_name, info in self.wrapped_globals.items():
                ret_type = info["ret_type"]
                args_list = []
                for arg_name, arg_type in info["args"].items():
                    cpp_type = self._resolve_type(arg_type)
                    if self._is_string_type(arg_type):
                        args_list.append(f"const string &{arg_name}")
                    elif self._is_primitive_type(cpp_type):
                        if cpp_type == "unsigned int":
                            args_list.append(f"unsigned int {arg_name}")
                        elif cpp_type == "unsigned short":
                            args_list.append(f"unsigned short {arg_name}")
                        elif cpp_type == "unsigned long long":
                            args_list.append(f"unsigned long long {arg_name}")
                        elif cpp_type == "long long":
                            args_list.append(f"long long {arg_name}")
                        elif cpp_type == "double":
                            args_list.append(f"double {arg_name}")
                        elif cpp_type == "bool":
                            args_list.append(f"bool {arg_name}")
                        elif cpp_type == "char":
                            args_list.append(f"char {arg_name}")
                        else:
                            args_list.append(f"int {arg_name}")
                    else:
                        args_list.append(f"const dict &{arg_name}")
                args_str = ", ".join(args_list)
                f.write(f"{ret_type} {py_name}({args_str});\n\n")

            # 追加 init/exit 辅助方法声明
            f.write("    void init();\n\n")

        self._write_to_subdir(f"{self.file_prefix}_header_function.h", write_content)

    def generate_source_task(self) -> None:
        def write_content(f):
            for name, d in self.callbacks.items():
                line = self.lines[name]
                clean_line = line.replace("virtual", "").strip()
                clean_line = clean_line.replace(" = 0", "").replace("=0", "")
                f.write(clean_line.replace("void ", f"void {self.class_name}::", 1) + "\n")
                f.write("{\n")
                f.write("\tTask task = Task();\n")
                f.write(f"\ttask.task_name = {name.upper()};\n")

                for pname, tap_type in d.items():
                    if pname == "errorCode":
                        f.write(f"\ttask.task_error = {pname};\n")
                    elif pname == "sessionID":
                        f.write(f"\ttask.task_id = {pname};\n")
                    elif pname == "isLast":
                        f.write(f"\ttask.task_last = {pname};\n")
                    elif self._is_string_type(tap_type):
                        f.write(f"\ttask.task_string = std::string({pname});\n")
                    elif self._is_primitive_type(self._resolve_type(tap_type)):
                        f.write(f"\ttask.task_int = {pname};\n")
                    else:
                        # 默认视为结构体指针，深拷贝到堆上
                        struct_type = self._resolve_type(tap_type)
                        f.write(f"\tif ({pname}) {{\n")
                        f.write(f"\t\ttask.task_data = new {self.ns_prefix}{struct_type}(*{pname});\n")
                        f.write(f"\t}}\n")
                
                f.write("\tthis->task_queue.push(task);\n")
                f.write("};\n\n")
        self._write_to_subdir(f"{self.file_prefix}_source_task.cpp", write_content)

    def generate_source_switch(self) -> None:
        def write_content(f):
            for name in self.callbacks.keys():
                process_name = name.replace("On", "process", 1)
                f.write(f"case {name.upper()}:\n")
                f.write("{\n")
                f.write(f"\tthis->{process_name}(&task);\n")
                f.write("\tbreak;\n")
                f.write("}\n\n")
        self._write_to_subdir(f"{self.file_prefix}_source_switch.cpp", write_content)

    def _write_struct_fields_to_dict(self, f, cpp_var: str, py_dict: str, fields: dict, indent: str, is_pointer: bool = False) -> None:
        """递归生成 C++ 结构体字段 → pybind11::dict 的代码"""
        for sfield, stype in fields.items():
            access = f"{cpp_var}->{sfield}" if is_pointer else f"{cpp_var}.{sfield}"
            if stype == "string":
                f.write(f'{indent}{py_dict}["{sfield}"] = std::string({access});\n')
            elif stype in TYPE_GETTER_MAP:
                f.write(f'{indent}{py_dict}["{sfield}"] = {access};\n')
            elif stype in self.structs:
                # 嵌套结构体：变量名基于父 dict 名，避免同层级冲突
                nested_dict = f"{py_dict}_{sfield}_dict"
                f.write(f'{indent}pybind11::dict {nested_dict};\n')
                self._write_struct_fields_to_dict(f, access, nested_dict, self.structs[stype], indent, is_pointer=False)
                f.write(f'{indent}{py_dict}["{sfield}"] = {nested_dict};\n')   # 追加：把子 dict 挂到父 dict
            else:
                f.write(f'{indent}// TODO: unsupported type "{stype}" for field "{sfield}"\n')

    def generate_source_process(self) -> None:
        def write_content(f):
            for name, d in self.callbacks.items():
                process_name = name.replace("On", "process", 1)
                on_name = name.replace("On", "on", 1)
                f.write(f"void {self.class_name}::{process_name}(Task *task)\n")
                f.write("{\n")
                if not d:
                    f.write(f"\tthis->{on_name}();\n")
                    f.write("};\n\n")
                else:
                    f.write("\tgil_scoped_acquire acquire;\n")
                    args = []
                    for pname, tap_type in d.items():
                        if pname == "errorCode":
                            args.append("task->task_error")
                        elif pname == "sessionID":
                            args.append("task->task_id")
                        elif pname == "isLast":
                            args.append("task->task_last")
                        elif self._is_string_type(tap_type):
                            args.append("task->task_string")
                        elif self._is_primitive_type(self._resolve_type(tap_type)):
                            args.append("task->task_int")
                        else:
                            # 默认从 task_data 还原结构体
                            struct_type = self._resolve_type(tap_type)
                            f.write(f"\tpybind11::dict {pname};\n")
                            f.write(f"\tif (task->task_data) {{\n")
                            f.write(f"\t\t{self.ns_prefix}{struct_type} *p = ({self.ns_prefix}{struct_type}*)task->task_data;\n")

                            if struct_type in self.structs:
                                self._write_struct_fields_to_dict(f, "p", pname, self.structs[struct_type], "\t\t", is_pointer=True)
 
                            f.write(f"\t\tdelete p;\n")
                            f.write(f"\t}}\n")
                            args.append(pname)
                    
                    args_str = ", ".join(args)
                    f.write(f"\tthis->{on_name}({args_str});\n")
                    f.write("};\n\n")
        self._write_to_subdir(f"{self.file_prefix}_source_process.cpp", write_content)

    def generate_source_function(self) -> None:
        def write_content(f):
            for name, d in self.functions.items():
                req_name = name[0].lower() + name[1:]
                raw_line = self.lines.get(name, "")
                raw_args = raw_line[raw_line.index("(")+1:raw_line.index(")")] if "(" in raw_line and ")" in raw_line else ""

                if name == "SetAPINotify":
                    f.write(f"int {self.class_name}::setAPINotify()\n")
                    f.write("{\n")
                    f.write(f"\tint i = this->api->SetAPINotify(this);\n")
                    f.write("\treturn i;\n")
                    f.write("};\n\n")
                    continue

                session_param = None
                biz_params = []
                for pname, tap_type in d.items():
                    cpp_type = self._resolve_type(tap_type)
                    if cpp_type == "unsigned int" or pname == "sessionID":
                        session_param = pname
                    else:
                        biz_params.append((pname, tap_type, cpp_type))
                
                args_list = []
                for pname, tap_type, cpp_type in biz_params:
                    if self._is_string_type(tap_type):
                        args_list.append(f"const string &{pname}")
                    elif self._is_primitive_type(cpp_type):
                        if cpp_type == "unsigned int":
                            args_list.append(f"unsigned int {pname}")
                        elif cpp_type == "unsigned short":
                            args_list.append(f"unsigned short {pname}")
                        elif cpp_type == "unsigned long long":
                            args_list.append(f"unsigned long long {pname}")
                        elif cpp_type == "long long":
                            args_list.append(f"long long {pname}")
                        elif cpp_type == "double":
                            args_list.append(f"double {pname}")
                        elif cpp_type == "bool":
                            args_list.append(f"bool {pname}")
                        elif cpp_type == "char":
                            args_list.append(f"char {pname}")
                        else:
                            args_list.append(f"int {pname}")
                    else:
                        # 默认视为结构体指针
                        args_list.append(f"const dict &{pname}")
                args_str = ", ".join(args_list)
                
                f.write(f"int {self.class_name}::{req_name}({args_str})\n")
                f.write("{\n")
                if session_param:
                    f.write(f"\t{self.ns_prefix}TAPIUINT32 session;\n")
                
                call_args = []
                if session_param:
                    call_args.append("&session")
                
                for pname, tap_type, cpp_type in biz_params:
                    pattern = rf'(?:const\s+)?(?:\w+::)?(\w+(?:_\w+)?)\s*(\*)?\s*{pname}\b'
                    m = re.search(pattern, raw_args)
                    raw_base = m.group(1) if m else tap_type
                    has_star = m and m.group(2)
                    is_tapstr = raw_base.startswith("TAPISTR")
                    
                    if self._is_string_type(tap_type):
                        if is_tapstr:
                            parts = raw_base.split("_")
                            if len(parts) >= 2 and parts[1].isdigit():
                                num = parts[1]
                                arr_size = int(num) + 1
                                f.write(f"\tchar {pname}_buf[{arr_size}] = {{}};\n")
                                f.write(f"\tstrncpy({pname}_buf, {pname}.c_str(), {arr_size} - 1);\n")
                                f.write(f"\t{pname}_buf[{arr_size} - 1] = '\\0';\n")
                                if has_star:
                                    call_args.append(f"&{pname}_buf")
                                else:
                                    call_args.append(f"{pname}_buf")
                            else:
                                f.write(f"\t// TODO: non-standard TAPISTR format: {raw_base}\n")
                                call_args.append(f"const_cast<char*>({pname}.c_str())")
                        elif has_star:
                            call_args.append(f"const_cast<char*>({pname}.c_str())")
                        else:
                            call_args.append(f"{pname}[0]")
                    
                    elif self._is_primitive_type(cpp_type):
                        call_args.append(pname)
                    
                    else:
                        # 默认视为结构体参数
                        f.write(f"\t{self.ns_prefix}{cpp_type} {pname}_req = {{}};\n")
                        if cpp_type in self.structs:
                            struct_fields = self.structs[cpp_type]
                            for sfield, stype in struct_fields.items():
                                if stype == "string":
                                    f.write(f'\tgetString({pname}, "{sfield}", {pname}_req.{sfield});\n')
                                elif stype in TYPE_GETTER_MAP:
                                    getter = TYPE_GETTER_MAP[stype]
                                    f.write(f'\tget{getter}({pname}, "{sfield}", &{pname}_req.{sfield});\n')
                                else:
                                    f.write(f'\t// TODO: unsupported type "{stype}" for field "{sfield}"\n')
                        else:
                            f.write(f'\t// TODO: struct "{cpp_type}" definition not found in generated modules\n')
                        call_args.append(f"&{pname}_req")
                
                f.write(f"\tint i = this->api->{name}({', '.join(call_args)});\n")
                f.write("\treturn i;\n")
                f.write("};\n\n")

            # 追加：全局函数包装为成员方法实现
            for py_name, info in self.wrapped_globals.items():
                global_name = info["_global_name"]

                if global_name == "CreateTapQuoteAPI":
                    f.write(f"""int {self.class_name}::createTapQuoteAPI(const dict &req)
                    {{
                    TAPIINT32 iResult = 0;
                    TapAPIApplicationInfo appInfo;
                    memset(&appInfo, 0, sizeof(appInfo));
                    """)

                    for sfield, stype in self.structs["TapAPIApplicationInfo"].items():
                        if stype == "string":
                            f.write(f'\tgetString(req, "{sfield}", appInfo.{sfield});\n')
                        elif stype in TYPE_GETTER_MAP:
                            f.write(f'\tget{TYPE_GETTER_MAP[stype]}(req, "{sfield}", &appInfo.{sfield});\n')

                    f.write("""\n\tthis->api = CreateTapQuoteAPI(&appInfo, iResult);
                    \tif (this->api)
                    \t{
                    \t\tthis->api->SetAPINotify(this);
                    \t}
                    \treturn iResult;
                    };
                    """)

                elif global_name == "CreateITapTradeAPI":
                    f.write(f"""int {self.class_name}::createITapTradeAPI(const dict &req)
                    {{
                    ITapTrade::TAPIINT32 iResult = 0;
                    ITapTrade::TapAPIApplicationInfo appInfo;
                    memset(&appInfo, 0, sizeof(appInfo));
                    """)

                    for sfield, stype in self.structs["TapAPIApplicationInfo"].items():
                        if stype == "string":
                            f.write(f'\tgetString(req, "{sfield}", appInfo.{sfield});\n')
                        elif stype in TYPE_GETTER_MAP:
                            f.write(f'\tget{TYPE_GETTER_MAP[stype]}(req, "{sfield}", &appInfo.{sfield});\n')

                    f.write("""\n\tthis->api = CreateITapTradeAPI(&appInfo, iResult);
                    \tif (this->api)
                    \t{
                    \t\tthis->api->SetAPINotify(this);
                    \t}
                    \treturn iResult;
                    };
                    """)

                elif global_name == "SetTapQuoteAPIDataPath":
                    f.write(f"""int {self.class_name}::setTapQuoteAPIDataPath(const string &path)
                    {{
                    return SetTapQuoteAPIDataPath(path.c_str());
                    }};
                    """)

                elif global_name == "SetTapQuoteAPILogLevel":
                    f.write(f"""int {self.class_name}::setTapQuoteAPILogLevel(int level)
                    {{
                    return SetTapQuoteAPILogLevel(static_cast<TAPILOGLEVEL>(level));
                    }};
                    """)

                elif global_name == "GetTapQuoteAPIVersion":
                    f.write(f"""string {self.class_name}::getTapQuoteAPIVersion()
                    {{
                    const char *v = GetTapQuoteAPIVersion();
                    return std::string(v ? v : "");
                    }};
                    """)

                elif global_name == "GetITapTradeAPIVersion":
                    f.write(f"""string {self.class_name}::getITapTradeAPIVersion()
                    {{
                    const char *v = GetITapTradeAPIVersion();
                    return std::string(v ? v : "");
                    }};
                    """)

                elif global_name == "GetITapErrorDescribe":
                    f.write(f"""string {self.class_name}::getITapErrorDescribe(int errorCode)
                    {{
                    const char *desc = GetITapErrorDescribe(errorCode);
                    return std::string(desc ? desc : "");
                    }};
                    """)
            # 追加 init() 实现（启动 task 线程，类似 CTP 风格）
            f.write(f"""void {self.class_name}::init()
            {{
            this->active = true;
            this->task_thread = thread(&{self.class_name}::processTask, this);
            }};
            """)
        self._write_to_subdir(f"{self.file_prefix}_source_function.cpp", write_content)

    def generate_source_on(self) -> None:
        def write_content(f):
            for name, d in self.callbacks.items():
                on_name = name.replace("On", "on", 1)
                args = []
                bind_args = ["void", self.class_name, on_name]
                for field, tap_type in d.items():
                    cpp_type = self._resolve_type(tap_type)
                    if self._is_string_type(tap_type):
                        args.append(f"const string &{field}")
                        bind_args.append(f"{field}")
                    elif self._is_primitive_type(cpp_type):
                        if cpp_type == "unsigned int":
                            args.append(f"unsigned int {field}")
                        elif cpp_type == "unsigned short":
                            args.append(f"unsigned short {field}")
                        elif cpp_type == "unsigned long long":
                            args.append(f"unsigned long long {field}")
                        elif cpp_type == "long long":
                            args.append(f"long long {field}")
                        elif cpp_type == "double":
                            args.append(f"double {field}")
                        elif cpp_type == "bool":
                            args.append(f"bool {field}")
                        elif cpp_type == "char":
                            args.append(f"char {field}")
                        else:
                            args.append(f"int {field}")
                        bind_args.append(f"{field}")
                    else:
                        args.append(f"const dict &{field}")
                        bind_args.append(f"{field}")
                
                args_str = ", ".join(args)
                bind_args_str = ", ".join(bind_args)
                f.write(f"void {on_name}({args_str}) override\n")
                f.write("{\n")
                f.write("\ttry\n")
                f.write("\t{\n")
                f.write(f"\t\tPYBIND11_OVERLOAD({bind_args_str});\n")
                f.write("\t}\n")
                f.write("\tcatch (const error_already_set &e)\n")
                f.write("\t{\n")
                f.write("\t\tcout << e.what() << endl;\n")
                f.write("\t}\n")
                f.write("};\n\n")
        self._write_to_subdir(f"{self.file_prefix}_source_on.cpp", write_content)

    def generate_source_module(self) -> None:
        def write_content(f):
            for name in self.functions.keys():
                req_name = name[0].lower() + name[1:]
                f.write(f'\t.def("{req_name}", &{self.class_name}::{req_name})\n')
            f.write("\n")
            for name in self.callbacks.keys():
                name = name.replace("On", "on", 1)
                f.write(f'\t.def("{name}", &{self.class_name}::{name})\n')
            f.write("\n")
            
            # 追加：全局函数包装的 pybind11 绑定
            for py_name in self.wrapped_globals.keys():
                f.write(f'\t.def("{py_name}", &{self.class_name}::{py_name})\n')
            f.write(f'\t.def("init", &{self.class_name}::init)\n')            
            f.write(";\n")

        self._write_to_subdir(f"{self.file_prefix}_source_module.cpp", write_content)

    def generate_source_global(self) -> None:
        def write_content(f):
            # 以下函数已包装为类成员方法，不在模块级重复暴露
            wrapped_names = {info["_global_name"] for info in self.wrapped_globals.values()}

            for name, d in self.global_functions.items():
                if name in wrapped_names:
                    continue

                py_name = name[0].lower() + name[1:]
                if not d:
                    f.write(f'\tm.def("{py_name}", &{name});\n')
                else:
                    f.write(f'\t// TODO: {name} has parameters, manual binding recommended\n')
                    f.write(f'\t// m.def("{py_name}", &{name});\n')

        self._write_to_subdir(f"{self.file_prefix}_source_global.cpp", write_content)

    def _read_file(self, filename: str) -> str:
        filepath = self.sub_dir / filename
        if filepath.exists():
            return filepath.read_text(encoding='utf-8').strip()
        return ""

    def assemble(self):
        virtual_funcs = []
        for name, line in self.lines.items():
            if name in self.callbacks:
                clean_line = line.replace(" = 0", "").replace("=0", "").strip()
                virtual_funcs.append(f"    {clean_line};")

        context = {
            'h_filename': os.path.basename(self.filename),
            'defines': self._read_file(f"{self.file_prefix}_header_define.h"),
            'class_name': self.class_name,
            'base_class_name': self.base_class_name,
            'api_type': self.api_type,
            'virtual_functions': "\n".join(virtual_funcs),
            'process_declarations': self._read_file(f"{self.file_prefix}_header_process.h"),
            'on_declarations': self._read_file(f"{self.file_prefix}_header_on.h"),
            'function_declarations': self._read_file(f"{self.file_prefix}_header_function.h"),
            'file_prefix': self.file_prefix,
            'task_content': self._read_file(f"{self.file_prefix}_source_task.cpp"),
            'switch_content': self._read_file(f"{self.file_prefix}_source_switch.cpp"),
            'process_content': self._read_file(f"{self.file_prefix}_source_process.cpp"),
            'function_content': self._read_file(f"{self.file_prefix}_source_function.cpp"),
            'on_content': self._read_file(f"{self.file_prefix}_source_on.cpp"),
            'module_content': self._read_file(f"{self.file_prefix}_source_module.cpp"),
            'global_content': self._read_file(f"{self.file_prefix}_source_global.cpp"),
            'module_name': self.module_name,
            'pybind_var': self.pybind_var,
            'namespace': self.namespace,
        }

        header_path = self.sub_dir / f"{self.file_prefix}.h"
        with open(header_path, 'w', encoding='utf-8') as f:
            f.write(self.header_template.render(context))

        source_path = self.sub_dir / f"{self.file_prefix}.cpp"
        with open(source_path, 'w', encoding='utf-8') as f:
            f.write(self.source_template.render(context))

        for pattern in ["*_header_*.h", "*_source_*.cpp"]:
            for f in self.sub_dir.glob(pattern):
                f.unlink()
        print(f"[*] 已组装并清理中间文件: {self.sub_dir}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='生成 TAP API 函数绑定')
    parser.add_argument('--include-dir', required=True, help='TAP 头文件目录')
    parser.add_argument('--output-dir', required=True, help='输出目录（如 tap/版本号/src）')
    args = parser.parse_args()

    include_dir = args.include_dir
    output_dir = args.output_dir

    if output_dir not in sys.path:
        sys.path.insert(0, output_dir)

    md_gen = ApiGenerator(
        os.path.join(include_dir, "TapQuoteAPI.h"),
        "tap", "md", "MdApi",
        output_dir
    )
    md_gen.run()

    td_gen = ApiGenerator(
        os.path.join(include_dir, "iTapTradeAPI.h"),
        "tap", "td", "TdApi",
        output_dir
    )
    td_gen.run()