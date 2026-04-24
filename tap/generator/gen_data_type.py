"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import argparse
import importlib
import os
import sys
from pathlib import Path


class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str, name: str) -> None:
        self.filename = filename
        self.prefix = prefix
        self.name = name
        self.typedefs: dict = {}
        self.struct_names: set = set()

    def load_common_structs(self) -> None:
        """加载 common struct 中的结构体名，用于识别 data struct 里的嵌套类型"""
        if self.name == "md":
            module_name = "tap_md_common_struct"
        else:
            module_name = "tap_td_common_struct"
    
        try:
            module = importlib.import_module(module_name)
            for name in dir(module):
                if "__" not in name:
                    obj = getattr(module, name)
                    if isinstance(obj, dict):
                        self.struct_names.add(name)
            print(f"[+] Loaded common struct names: {module_name}, count={len(self.struct_names)}")
        except ModuleNotFoundError as e:
            print(f"[-] Missing common struct: {module_name}, {e}")

    def load_constant(self) -> None:
        root_dir = Path(__file__)
        if str(root_dir) not in sys.path:
            sys.path.insert(0, str(root_dir))

        module_names = ["tap_td_common_typedef", "tap_md_common_typedef"]
        for module_name in module_names:
            module = importlib.import_module(module_name)

            for name in dir(module):
                if "__" not in name:
                    self.typedefs[name] = getattr(module, name)

    def run(self) -> None:
        """主函数"""
        self.f_cpp = open(self.filename, encoding='utf-8', errors='ignore')
        if self.name == "td":
            self.f_define = open(f"{self.prefix}_{self.name}_data_constant.py", "w", encoding="utf-8")
        self.f_typedef = open(f"{self.prefix}_{self.name}_data_typedef.py", "w", encoding="utf-8")
        self.f_struct = open(f"{self.prefix}_{self.name}_data_struct.py", "w", encoding="utf-8")

        self.load_constant()
        self.load_common_structs()

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        if self.name == "td":
            self.f_define.close()
        self.f_typedef.close()
        self.f_struct.close()

        print(f"{self.name}_DataType生成完毕")

    def process_line(self, line: str) -> None:
        line_ = line.replace("\n", "")
        line = line_.replace(";", "")

        # MD
        if self.name == "md":
            if line.startswith("typedef"):
                self.process_typedef_md(line)
            elif "struct" in line:
                self.process_declare(line)
            elif "{" in line:
                self.process_start(line)
            elif "}" in line and "@" not in line:
                self.process_end(line)
            elif "///<" in line:
                self.process_member(line)
        # TD
        elif self.name == "td":
            if "typedef" in line:
                self.process_typedef_td(line)
            elif "const" in line:
                self.process_const(line)
            elif "struct" in line:
                self.process_declare(line)
            elif line.startswith("    {"):
                self.process_start(line)
            elif "};" in line_:
                self.process_end(line)
            elif "=" not in line and "//" in line:
                if "!" not in line and "！" not in line and "#" not in line and "TapTradeAPI" not in line:
                    self.process_member(line)
            elif "#" not in line and "!" not in line and "=" not in line and "*" not in line and "(" not in line and "namespace" not in line and len(line) != 0:
                self.process_special(line)

    def process_special(self, line: str) -> None:
        line = line.replace("\t", " ")
        words = line.split(" ")
        words = [word for word in words if word != ""]

        if len(words) == 2 or len(words) == 3:
            name = words[1]
            type_ = words[0]

            if type_ in self.typedefs:
                py_type = self.typedefs[type_]
            elif type_ in self.struct_names:   # <-- 新增
                py_type = type_
            else:
                py_type = "dict"

            new_line = f'    "{name}": "{py_type}",\n'
            self.f_struct.write(new_line)

    def process_declare(self, line: str) -> None:
        line = line.replace("\t", " ")
        words = line.split(" ")
        words = [w for w in words if w and w != "{"]
        if len(words) >= 2:
            name = words[-1]
            self.struct_names.add(name)   # 记录到 struct_names
            new_line = f"{name} = {{\n"
            self.f_struct.write(new_line)

    def process_start(self, line: str) -> None:
        pass

    def process_end(self, line: str) -> None:
        new_line = "}\n\n"
        self.f_struct.write(new_line)

    def process_member(self, line: str) -> None:
        sector = line.split("///<")[0]
        words = sector.split("\t")
        words = [word for word in words if word != ""]

        if len(words) == 1:
            words = words[0].split(" ")
            words = [word for word in words if word != ""]

        if len(words) < 2:
            return

        name = words[1].strip()
        if "//" in name:
            return

        if not name:
            name = words[-1]

        if "[" in name:
            name = name.split("[")[0]

        type_name = words[0].strip()
        if type_name in self.typedefs:
            py_type = self.typedefs[type_name]
        elif type_name in self.struct_names:   # ← 新增：匹配已知结构体
            py_type = type_name
        else:
            py_type = "dict"

        new_line = f'    "{name}": "{py_type}",\n'
        self.f_struct.write(new_line)

    def process_typedef_md(self, line: str) -> None:
        words = line.split(" ")[-1].split("\t")
        words = [word for word in words if word != ""]

        name = words[-1]
        py_type = self.typedefs[words[0]]
        new_line = f'{name} = "{py_type}"\n'

        self.f_typedef.write(new_line)
        self.typedefs[name] = py_type

    def process_typedef_td(self, line: str) -> None:
        line = line.replace("\t", " ")
        words = line.split(" ")
        words = [word for word in words if word != ""]

        name = words[-1]
        if "[" in name:
            name = name.split("[")[0]
            py_type = "string"
        else:
            base_type = words[1]
            if base_type == "struct":
                # typedef struct X X; 保留结构体原名
                py_type = words[2] if len(words) > 2 else words[-2]
            else:
                # 不要回退为 dict，保留原始名（让 gen_api_functions 自行判断）
                py_type = self.typedefs.get(base_type, base_type)

        self.typedefs[name] = py_type
        new_line = f'{name} = "{py_type}"\n'
        self.f_typedef.write(new_line)

        # 只有真正无法识别且不是 struct typedef 时，才写 short2full
        if py_type == "dict" and words[1] != "struct":
            short2full = f"{name} = {words[-2]}\n"
            if words[-2] == "char":
                return
            self.f_struct.write(short2full)

    def process_const(self, line: str) -> None:
        line = line.replace("\t", " ")
        sectors = line.split("=")
        value = sectors[1].replace("'", '"').strip()

        words = sectors[0].split(" ")
        words = [word for word in words if word != ""]

        name = words[-1].strip()

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='生成 TAP 数据结构及常量文件')
    parser.add_argument('--include-dir', required=True, help='TAP 头文件目录')
    parser.add_argument('--output-dir', required=True, help='输出目录')
    args = parser.parse_args()

    include_dir = args.include_dir
    output_dir = args.output_dir

    md_gen = DataTypeGenerator(
        os.path.join(include_dir, "TapQuoteAPIDataType.h"),
        "tap", "md"
    )
    md_gen.run()

    td_gen = DataTypeGenerator(
        os.path.join(include_dir, "iTapTradeAPIDataType.h"),
        "tap", "td"
    )
    td_gen.run()