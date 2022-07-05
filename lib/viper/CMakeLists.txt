add_library(viper
	config.cpp
	value.cpp
)

target_link_libraries(viper
	PUBLIC ryml::ryml
)

add_library(libviper::viper ALIAS viper)

# tests
add_executable(viper_tests
	config_test.cpp
	value_test.cpp
)

cmake_path(SET viper_testdata_path ${CMAKE_CURRENT_SOURCE_DIR}/testdata)
target_compile_definitions(viper_tests
	PRIVATE VIPER_TESTDATA_PATH="${viper_testdata_path}"
)

target_link_libraries(viper_tests
	PRIVATE viper
	PRIVATE gtest_main
)

include(GoogleTest)
gtest_discover_tests(viper_tests)

