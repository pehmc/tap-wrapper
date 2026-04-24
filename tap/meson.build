#
# Copyright (c) 2026 pehmc. Apache 2.0 License.
# See LICENSE file in the project root for full license information.
#

project(
  'tap-wrapper-linux',
  'cpp',
  version: 'stable',
  license: 'Apache',
  meson_version: '>=1.9.0',
  default_options: [
    'buildtype=release',
    'cpp_std=c++17',
    'warning_level=2',
  ],
)

# 通过环境变量接收版本目录名
tap_version = run_command('python3', '-c',
  'import os; print(os.environ.get("TAP_VERSION", "v9.3.8"))',
  check: true
).stdout().strip()
version_dir = 'v' / tap_version
message('[*] 构建tap版本: ' + tap_version)

py = import('python').find_installation(pure: false)
py_dep = py.dependency()

pybind11_include_dir = run_command('python3', '-c', 'import pybind11; print(pybind11.get_include())', check: true).stdout().strip()
message('[*] 使用pybind11路径: ' + pybind11_include_dir)

pybind11_dep = declare_dependency(
  compile_args: ['-I' + pybind11_include_dir]
)

cpp = meson.get_compiler('cpp')
message('[*] 构建目标系统: ' + host_machine.system())

# 版本特定路径
lib_dir = meson.current_source_dir() / version_dir / 'libs'

include_dirs = include_directories(
  version_dir + '/include',
  version_dir + '/src',
)

extra_cpp_args = [
  '-O3',
  '-fPIC',
  '-Wno-delete-incomplete',
  '-Wno-sign-compare',
]

extra_link_args = [
  '-lstdc++',
]

# 查找tap库（编译链接必需）
tapmdapi_lib = cpp.find_library('TapQuoteAPI', 
                                      dirs: [lib_dir],
                                      required: true)
itaptradeapi_lib = cpp.find_library('iTapTradeAPI', 
                                      dirs: [lib_dir],
                                      required: true)

# 创建MD模块（install: false，产物由 gen.py 手动整理）
md_module = py.extension_module(
  'tapmd',
  sources: [version_dir + '/src/tapmd/tapmd.cpp'],
  include_directories: include_dirs,
  dependencies: [py_dep, pybind11_dep, tapmdapi_lib],
  cpp_args: extra_cpp_args,
  build_rpath: '$ORIGIN',  # 关键：编译时写入ELF，确保复制到api/后能找到同目录官方库
  install: false
)

# 创建TD模块
td_module = py.extension_module(
  'taptd',
  sources: [version_dir + '/src/taptd/taptd.cpp'],
  include_directories: include_dirs,
  dependencies: [py_dep, pybind11_dep, itaptradeapi_lib],
  cpp_args: extra_cpp_args,
  build_rpath: '$ORIGIN',
  install: false
)