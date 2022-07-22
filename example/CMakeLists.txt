add_executable(${PROJECT_NAME}_example EXCLUDE_FROM_ALL
	main.cpp
)

cmake_path(SET example_conf_path ${CMAKE_CURRENT_SOURCE_DIR}/conf)
target_compile_definitions(${PROJECT_NAME}_example
	PRIVATE EXAMPLE_CONF_PATH="${example_conf_path}"
)

target_link_libraries(${PROJECT_NAME}_example
	PRIVATE libviper::viper
)

