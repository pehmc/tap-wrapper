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
3. 运行 `python wrapper <version>`
4. `from tap.api import ...`

### 文件目录说明

封装成功后的tap目录：

``` python
tap
├── api
│   ├── con
│   │   ├── md
│   │   │   └── TapQuoteAPI20260511.log
│   │   └── td
│   ├── __init__.py
│   ├── mdapi.py
│   ├── _mdapi.so
│   │   ├── __init__.cpython-313.pyc
│   │   ├── mdapi.cpython-313.pyc
│   │   └── tdapi.cpython-313.pyc
│   ├── tdapi.py
│   └── _tdapi.so
├── __init__.py
├── interface
│   ├── mdapi.i
│   └── tdapi.i
├── v
│   └── v9.3.8
│       ├── include
│       │   ├── iTapAPICommDef.h
│       │   ├── iTapAPIError.h
│       │   ├── iTapDataCollectAPI.h
│       │   ├── iTapTradeAPIDataType.h
│       │   ├── iTapTradeAPI.h
│       │   ├── TapAPICommDef.h
│       │   ├── TapAPIError.h
│       │   ├── TapQuoteAPIDataType.h
│       │   └── TapQuoteAPI.h
│       ├── libs
│       │   ├── libcrypto.so.1.1
│       │   ├── libiTapTradeAPI.so
│       │   ├── libssl.so.1.1
│       │   ├── libTapDataCollectAPI.so
│       │   └── libTapQuoteAPI.so
│       └── src
│           ├── mdapi.py
│           ├── mdapi_wrap.cpp
│           ├── mdapi_wrap.h
│           ├── mdapi_wrap.o
│           ├── tdapi.py
│           ├── tdapi_wrap.cpp
│           ├── tdapi_wrap.h
│           └── tdapi_wrap.o
└── wrapper.py

```

### 使用到的框架

- swig 4.4.1
- python 3.13

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




