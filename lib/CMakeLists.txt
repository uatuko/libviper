add_subdirectory(viper)

add_library(libviper INTERFACE)
target_link_libraries(libviper
	INTERFACE viper
)

add_library(libviper::viper ALIAS libviper)

target_include_directories(libviper
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

