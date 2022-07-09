# libviper

[![license](https://img.shields.io/badge/license-MIT-green)](https://raw.githubusercontent.com/uditha-atukorala/libviper/main/LICENSE)
[![codecov](https://codecov.io/gh/uditha-atukorala/libviper/branch/main/graph/badge.svg?token=8EfwylKma6)](https://codecov.io/gh/uditha-atukorala/libviper)

A library for reading configs built using modern c++ standards.

> The name and concepts are heavily inspired by [Go viper](https://github.com/spf13/viper)


## Design goals

1. Favor a clean, intuitive and easy to use API over performance.
2. Use modern c++ standards (>=c++17).
3. Be capable of reading configs from a file and consider environment overrides when retrieving.
4. Use type conversions to retrieve config values in scalar/common types.
