cmake_minimum_required(VERSION 3.20)
project(libviper VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/dependencies.cmake)

option(LIBVIPER_ENABLE_COVERAGE "Enable code coverage" OFF)
option(LIBVIPER_ENABLE_TESTING "Enable testing" OFF)

if (LIBVIPER_ENABLE_TESTING)
	enable_testing()
endif()

add_subdirectory(example)
add_subdirectory(lib)

