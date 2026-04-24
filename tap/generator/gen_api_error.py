"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import argparse
import os

class ErrorTypeGenerator:
    """ErrorType生成器"""

    def __init__(self, filename: str, prefix: str, name: str) -> None:
        self.filename = filename
        self.prefix = prefix
        self.name = name

    def run(self) -> None:
        """主函数"""
        self.f_cpp = open(self.filename, encoding='utf-8', errors='ignore')
        self.f_define = open(f"{self.prefix}_{self.name}_error_constant.py", "w", encoding="utf-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()

        print(f"{self.name}_ErrorType生成完毕")

    def process_line(self, line: str) -> None:
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        # MD
        if self.name == "md":
            if line.startswith("const int"):
                self.process_int(line)
        # TD
        elif self.name == "td":
            if "const int" in line:
                self.process_int(line)

    def process_int(self, line: str) -> None:
        """处理类型定义"""
        line = line.replace("\t", " ")
        line = line.split("//")[0]          # 去掉注释
        line = line.replace(";", "")
        if "=" not in line:
            return
        sectors = line.split("=")
        value = sectors[1].strip()

        words = sectors[0].split(" ")
        words = [word for word in words if word != ""]
        name = words[-1].strip()
        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='生成 TAP 错误码常量文件')
    parser.add_argument('--include-dir', required=True, help='TAP 头文件目录')
    parser.add_argument('--output-dir', required=True, help='输出目录')
    args = parser.parse_args()

    include_dir = args.include_dir
    output_dir = args.output_dir

    md_gen = ErrorTypeGenerator(
        os.path.join(include_dir, "TapAPIError.h"),
        "tap", "md"
    )
    md_gen.run()

    td_gen = ErrorTypeGenerator(
        os.path.join(include_dir, "iTapAPIError.h"),
        "tap", "td"
    )
    td_gen.run()