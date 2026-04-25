<p align="center">
  <h3 align="center">TAP Wrapper</h3>
  <p align="center">
    Linux环境的TAP外盘封装器
    <br />
    <a href="./demo">查看Demo</a>
    ·
    <a href="https://github.com/pehmc/tap-wrapper/issues">报告Bug</a>
  </p>
</p>

<div align="center">

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

</div>

## 目录

- [上手指南](#上手指南)
  - [适配的版本](#适配的版本)
  - [安装步骤](#安装步骤)
- [文件目录说明](#文件目录说明)
- [使用到的框架](#使用到的框架)
- [鸣谢](#鸣谢)

### 上手指南

#### 适配的版本

1. tap v9.3.8

#### 安装步骤

1. 克隆仓库，
2. tap/v 管理版本
3. 运行 `python wrapper --version <...>`
4. `import ... from tap.api`

### 文件目录说明

封装成功后的tap目录：

``` python
tap
├── api
│   ├── __init__.py               # 暴露 api
│   ├── libcrypto.so.1.1
│   ├── libiTapTradeAPI.so
│   ├── libssl.so.1.1
│   ├── libTapDataCollectAPI.so
│   ├── libTapQuoteAPI.so
│   ├── tap_md_common_constant.py
│   ├── tap_md_common_struct.py
│   ├── tap_md_common_typedef.py
│   ├── tapmd.cpython-313-x86_64-linux-gnu.so
│   ├── tap_md_data_struct.py
│   ├── tap_md_data_typedef.py
│   ├── tap_md_error_constant.py
│   ├── tapmd.pyi
│   ├── tap_td_common_constant.py
│   ├── tap_td_common_struct.py
│   ├── tap_td_common_typedef.py
│   ├── taptd.cpython-313-x86_64-linux-gnu.so
│   ├── tap_td_data_constant.py
│   ├── tap_td_data_struct.py
│   ├── tap_td_data_typedef.py
│   ├── tap_td_error_constant.py
│   └── taptd.pyi
├── generator
│   ├── gen_api_commdef.py
│   ├── gen_api_error.py
│   ├── gen_api_functions.py
│   ├── gen_data_type.py
│   ├── gen.py
│   └── templates
│       ├── tap_header.j2
│       └── tap_source.j2
├── __init__.py
├── meson.build
├── v                       # 版本管理
│   ├── tap.h
│   └── v9.3.8
│       ├── include         # 官方头文件
│       │   ├── iTapAPICommDef.h
│       │   ├── iTapAPIError.h
│       │   ├── iTapDataCollectAPI.h
│       │   ├── iTapTradeAPIDataType.h
│       │   ├── iTapTradeAPI.h
│       │   ├── TapAPICommDef.h
│       │   ├── TapAPIError.h
│       │   ├── TapQuoteAPIDataType.h
│       │   └── TapQuoteAPI.h
│       ├── libs          # 官方库
│       │   ├── libcrypto.so.1.1
│       │   ├── libiTapTradeAPI.so
│       │   ├── libssl.so.1.1
│       │   ├── libTapDataCollectAPI.so
│       │   └── libTapQuoteAPI.so
│       └── src
│           ├── tapmd
│           │   ├── tapmd.cpp
│           │   └── tapmd.h
│           └── taptd
│               ├── taptd.cpp
│               └── taptd.h
└── wrapper.py
```

### 使用到的框架

- jinja2
- pybind11
- pybind11-stubgen
- meson

### 鸣谢

- [vnpy_tap](https://github.com/vnpy/vnpy_tap)

<!-- links -->
[your-project-path]:pehmc/tap-wrapper
[contributors-shield]: https://img.shields.io/github/contributors/pehmc/tap-wrapper.svg?style=flat-square
[contributors-url]: https://github.com/pehmc/tap-wrapper/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/pehmc/tap-wrapper.svg?style=flat-square
[forks-url]: https://github.com/pehmc/tap-wrapper/network/members
[stars-shield]: https://img.shields.io/github/stars/pehmc/tap-wrapper.svg?style=flat-square
[stars-url]: https://github.com/pehmc/tap-wrapper/stargazers
[issues-shield]: https://img.shields.io/github/issues/pehmc/tap-wrapper.svg?style=flat-square
[issues-url]: https://img.shields.io/github/issues/pehmc/tap-wrapper.svg
[license-shield]: https://img.shields.io/github/license/pehmc/tap-wrapper.svg?style=flat-square
[license-url]: https://github.com/pehmc/tap-wrapper/blob/master/LICENSE.txt




