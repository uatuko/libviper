add_subdirectory(viper)

add_library(libviper INTERFACE)
target_link_libraries(libviper
	INTERFACE viper
)

target_include_directories(libviper
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(libviper::viper ALIAS libviper)

