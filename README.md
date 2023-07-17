# libviper

[![license](https://img.shields.io/badge/license-MIT-green)](https://raw.githubusercontent.com/uditha-atukorala/libviper/main/LICENSE)
[![codecov](https://codecov.io/gh/uditha-atukorala/libviper/branch/main/graph/badge.svg?token=8EfwylKma6)](https://codecov.io/gh/uditha-atukorala/libviper)
[![build](https://github.com/uditha-atukorala/libviper/actions/workflows/build.yaml/badge.svg?branch=main)](https://github.com/uditha-atukorala/libviper/actions/workflows/build.yaml)
[![release](https://img.shields.io/github/v/release/uditha-atukorala/libviper)](https://github.com/uditha-atukorala/libviper/releases)

A library for reading configs built using modern c++ standards.

> The name and concepts are heavily inspired by [Go viper](https://github.com/spf13/viper)


## Design goals

1. Favor a clean, intuitive and easy to use API over performance.
2. Use modern c++ standards (>=c++17).
3. Be capable of reading configs from a file and consider environment overrides when retrieving.
4. Use type conversions to retrieve config values in scalar/common types.


## Install
### CMake

```cmake
include(FetchContent)

# libviper
FetchContent_Declare(libviper
  URL      https://github.com/uditha-atukorala/libviper/archive/refs/tags/v0.3.1.tar.gz
  URL_HASH SHA256=24a79fe54708a315394938f7946dab35aa69b884f0fab4ac0a9fa42b60c93313
)
FetchContent_MakeAvailable(libviper)
```

```cmake
target_link_libraries(<target>
  PRIVATE
    libviper::viper
)
```


## Usage

```c++
#include <viper/config.h>

// A config can be constructed by passing in a config name (without the file extension)
// and optionally a path to look for config files.
auto conf = viper::config("config.name", std::filesystem::current_path() / "conf");
// auto conf = viper::config("config.name", "/path/to/config/files");
// auto conf = viper::config("config.name"); // Looks for configs in the current working directory

// Reading configs can throw exceptions
try {
  conf.read();
} catch (const std::exception &e) {
  // TODO: handle exception
}
```

Most of the time configs need to be shared throughout the program. Convenience methods, `viper::init()` and `viper::conf()`,
can be used to initialise and use configs as a shared single instance.
```c++
#include <viper/viper.h>

try {
  viper::init("config.name");
  // viper::init("config.name", "/path/to/config/files");
  // viper::init("config.name", std::filesystem::current_path() / "conf");
} catch (const std::exception &e) {
  // TODO: handle exception
}

auto conf = *viper::conf(); // dereference `std::shared_ptr<viper::config>` to `viper::config`
```

```c++
// Config values can be retrieved using a key path (`.` can be used to drill down into maps)
// Note: this will look for an environment variable with key PATH_TO_KEY and if set, return
//       the env value instead of the value from config file.
viper::value v = conf["path.to.key"];

// Convert to scalar/basic types using explicit conversions
auto b = conf["path.to.key"].get<bool>();
auto d = double{conf["path.to.key"]};
auto l = long{conf["path.to.key"]};
auto s = conf["path.to.key"].get<std::string>();

// Iterate through values
for (const auto &v : conf["array"]) {
  auto s = std::string{v};
}
```
