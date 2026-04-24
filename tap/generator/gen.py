"""
Copyright (c) 2026 pehmc. Apache 2.0 License.
See LICENSE file in the project root for full license information.
"""

import argparse
import glob
import os
import subprocess
import sys


def delete_tap_files(dirs):
    """删除 tap_ 开头的中间文件"""
    for d in dirs:
        if not os.path.exists(d):
            continue
        pattern = os.path.join(d, "tap_*")
        for f in glob.glob(pattern):
            if os.path.isfile(f):
                try:
                    os.remove(f)
                    print(f"已删除: {f}")
                except Exception as e:
                    print(f"删除失败 {f}: {e}")


def run_step(script_name, include_dir, output_dir, error_message):
    """执行单个生成步骤，自动传递路径参数"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    script_path = os.path.join(script_dir, script_name)

    if not os.path.exists(script_path):
        print(f"找不到脚本: {script_path}")
        sys.exit(1)

    try:
        result = subprocess.run([
            sys.executable, script_path,
            '--include-dir', include_dir,
            '--output-dir', output_dir
        ], cwd=script_dir)
        if result.returncode != 0:
            print(error_message)
            sys.exit(1)
    except Exception as e:
        print(f"执行 {script_name} 时发生错误: {e}")
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description='生成 TAP C++ 绑定代码')
    parser.add_argument('--include-dir', required=True, help='TAP 头文件所在目录')
    parser.add_argument('--output-dir', required=True, help='输出 C++ 源码的根目录')
    args = parser.parse_args()

    include_dir = args.include_dir
    output_dir = args.output_dir
    generator_dir = os.path.dirname(os.path.abspath(__file__))

    print(f"头文件目录: {include_dir}")
    print(f"输出目录: {output_dir}")

    # 创建输出子目录
    os.makedirs(os.path.join(output_dir, 'tapmd'), exist_ok=True)
    os.makedirs(os.path.join(output_dir, 'taptd'), exist_ok=True)

    # 清理旧的中间文件
    delete_tap_files([generator_dir, output_dir])

    # 定义生成步骤（按依赖顺序）
    steps = [
        # 先产生公共类型定义
        ('gen_api_commdef.py', "生成 TAP 公共常量/类型失败"),
        ('gen_api_error.py', "生成 TAP 错误码常量失败"),
        ('gen_data_type.py', "生成 TAP 数据结构定义失败"),
        # 最后生成 API 绑定片段（依赖上面的结构体描述）
        ('gen_api_functions.py', "生成 TAP API 函数绑定失败"),
    ]

    for script_name, error_msg in steps:
        run_step(script_name, include_dir, output_dir, error_msg)

    print("\n所有 TAP 生成步骤已完成！")


if __name__ == '__main__':
    main()