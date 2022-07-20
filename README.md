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


## Usage

```c++
#include <viper/config.h>

// A config can be constructed by passing in a config name (without the file extension) and a path to
// look for config files.
auto conf = viper::config("config.name", "/path/to/config/files");

// Reading configs can throw exceptions
try {
  conf.read();
} catch (const std::exception &e) {
  // TODO: handle exception
}

// Config values can be retrieved using a key path (`.` can be used to drill down into maps)
// Note: this will look for an environment variable with key PATH_TO_KEY and if set, return the env value
//       instead of the value from config file.
viper::value v = conf["path.to.key"];

// Convert to scalar/basic types using explicit conversions
auto b = bool{conf["path.to.key"]};
auto l = long{conf["path.to.key"]};
auto s = std::string{conf["path.to.key"]};

// Iterate through values
for (const auto &v : conf["array"]) {
  auto s = std::string{v};
}
```
