"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import argparse
import importlib
import os
import sys
from pathlib import Path

class CommonTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str, name: str) -> None:
        self.filename = filename
        self.prefix = prefix
        self.name = name
        self.typedefs: dict = {}
        self.struct_names: set = set()

    def run(self) -> None:
        """主函数"""
        self.f_cpp = open(self.filename, encoding='utf-8', errors='ignore')
        self.f_define = open(f"{self.prefix}_{self.name}_common_constant.py", "w", encoding='utf-8')
        self.f_typedef = open(f"{self.prefix}_{self.name}_common_typedef.py", "w", encoding='utf-8')
        self.f_struct = open(f"{self.prefix}_{self.name}_common_struct.py", "w", encoding='utf-8')

        self.add_supplement()

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        self.process_struct()

        self.f_cpp.close()
        self.f_struct.close()

        print(f"{self.name}_CommonType生成完毕")

    def process_struct(self) -> None:
        f_cpp_struct = open(self.filename, encoding='utf-8', errors='ignore')
        for line in f_cpp_struct:
            line_ = line.replace("\n", "")
            line = line_.replace(";", "")

            if "struct" in line:
                self.process_declare(line)
            elif "{" in line:
                self.process_start(line)
            elif line.strip().startswith("}") and self.name == "md":
                self.process_end(line)
            elif "};" in line_ and self.name == "td":
                self.process_end(line)
            elif "///<" in line:
                self.process_member(line)

        f_cpp_struct.close()

    def process_declare(self, line: str) -> None:
        words = line.split(" ")
        words = [w for w in words if w and w != "{"]
        if len(words) >= 2:
            name = words[-1]
            self.struct_names.add(name)   # 记录结构体名
            new_line = f"{name} = {{\n"
            self.f_struct.write(new_line)

    def process_member(self, line: str) -> None:
        sector = line.split("///<")[0]
        words = sector.split("\t")
        words = [word for word in words if word != ""]

        if len(words) == 1:
            words = words[0].split(" ")
            words = [word for word in words if word != ""]

        name = words[1].strip()
        if "[" in name:
            name = name.split("[")[0]

        type_name = words[0].strip()
        if type_name in self.typedefs:
            py_type = self.typedefs[type_name]
        elif type_name in self.struct_names:   # <-- 需要配合 struct_names 集合
            py_type = type_name
        else:
            py_type = "dict"

        new_line = f'    "{name}": "{py_type}",\n'
        self.f_struct.write(new_line)

    def process_start(self, line: str) -> None:
        pass

    def process_end(self, line: str) -> None:
        new_line = "}\n\n"
        self.f_struct.write(new_line)

    def process_line(self, line: str) -> None:
        line = line.replace("\n", "")
        line = line.replace(";", "")

        # MD
        if self.name == "md":
            if line.startswith("typedef char"):
                self.process_char_md(line)
            elif line.startswith("const"):
                self.process_const_md(line)
        # TD
        elif self.name == "td":
            if "typedef char" in line:
                self.process_char_td(line)
            elif "const" in line and "=" in line:
                self.process_const_td(line)

    def process_char_md(self, line: str) -> None:
        rest = line[len("typedef char"):].strip()
        if "[" in rest:
            name = rest.split("[")[0].strip()
            py_type = "string"
        else:
            name = rest.strip()
            py_type = "char"

        self.f_typedef.write(f'{name} = "{py_type}"\n')
        self.typedefs[name] = py_type       # <-- 关键：同步到内存

    def process_char_td(self, line: str) -> None:
        line = line.replace("\t", " ")
        words = line.split(" ")
        words = [word for word in words if word != ""]

        name = words[-1]
        if "[" in name:
            name = name.split("[")[0]
            py_type = "string"
        else:
            py_type = "char"

        self.f_typedef.write(f'{name} = "{py_type}"\n')
        self.typedefs[name] = py_type       # <-- 关键：同步到内存


    def process_const_md(self, line: str) -> None:
        line = line.split("//")[0]      # 先去掉注释
        sectors = line.split("=")
        if len(sectors) < 2:
            return
        value = sectors[1].replace("'", '"').strip()

        words = sectors[0].split("\t")
        words = [word for word in words if word != ""]
        if len(words) < 2:
            return
        name = words[1].strip()

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_const_td(self, line: str) -> None:
        line = line.split("//")[0]      # 先去掉注释
        line = line.replace("\t", " ")
        sectors = line.split("=")
        if len(sectors) < 2:
            return
        value = sectors[1].replace(";", "").replace("'", '"').strip()

        words = sectors[0].split(" ")
        words = [word for word in words if word != ""]
        name = words[-1].strip()

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def add_supplement(self) -> None:
        supplements = [
            ('TAPIINT32', 'int'),
            ('TAPIUINT32', 'unsigned int'),
            ('TAPIINT64', 'long long'),
            ('TAPIUINT64', 'unsigned long long'),
            ('TAPIUINT16', 'unsigned short'),
            ('TAPIUINT8', 'unsigned char'),
            ('TAPIREAL64', 'double'),
        ]

        if self.name == "md":
            supplements += [
                ('TAPIYNFLAG', 'char'),
                ('TAPILOGLEVEL', 'char'),
                ('TAPICommodityType', 'char'),
                ('TAPICallOrPutFlagType', 'char'),
                ('TAPIMACTYPE', 'string'),
                ('TAPISecondSerialIDType', 'string'),
                ('TAPIClientIDType', 'string'),
            ]
        elif self.name == "td":
            supplements += [
                ('TAPIYNFLAG', 'char'),
                ('TAPIPasswordType', 'char'),
                ('TAPILOGLEVEL', 'char'),
                ('TAPIOptionType', 'char'),
                ('TAPICommodityType', 'char'),
                ('TAPICallOrPutFlagType', 'char'),
            ]

        for name, py_type in supplements:
            self.f_typedef.write(f'{name} = "{py_type}"\n')
            self.typedefs[name] = py_type   # <-- 关键：同步到内存


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='生成 TAP 公共常量/类型文件')
    parser.add_argument('--include-dir', required=True, help='TAP 头文件目录')
    parser.add_argument('--output-dir', required=True, help='输出目录')
    args = parser.parse_args()

    include_dir = args.include_dir
    output_dir = args.output_dir

    md_gen = CommonTypeGenerator(
        os.path.join(include_dir, "TapAPICommDef.h"),
        "tap", "md"
    )
    md_gen.run()

    td_gen = CommonTypeGenerator(
        os.path.join(include_dir, "iTapAPICommDef.h"),
        "tap", "td"
    )
    td_gen.run()