add_executable(example EXCLUDE_FROM_ALL
	main.cpp
)

cmake_path(SET example_conf_path ${CMAKE_CURRENT_SOURCE_DIR}/conf)
target_compile_definitions(example
	PRIVATE EXAMPLE_CONF_PATH="${example_conf_path}"
)

target_link_libraries(example
	PRIVATE libviper::viper
)

