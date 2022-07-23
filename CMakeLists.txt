cmake_minimum_required(VERSION 3.20)
project(libviper VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/dependencies.cmake)

option(ENABLE_COVERAGE "Enable code coverage" OFF)

enable_testing()
add_subdirectory(example)
add_subdirectory(lib)

