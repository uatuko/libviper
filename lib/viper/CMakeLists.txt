add_library(viper
	config.cpp
	config.h
	value.cpp
	value.cpp
)

target_link_libraries(viper
	PUBLIC ryml::ryml
)

if (ENABLE_COVERAGE)
	target_compile_options(viper
		PRIVATE --coverage
	)

	target_link_options(viper
		INTERFACE -fprofile-arcs
	)
endif()

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

if (ENABLE_COVERAGE)
	target_compile_options(viper_tests
		PRIVATE --coverage
	)

	target_link_options(viper_tests
		PRIVATE -fprofile-arcs
	)
endif()

include(GoogleTest)
gtest_discover_tests(viper_tests)

