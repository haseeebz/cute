cmake_minimum_required(VERSION 3.10)
project(cute C)


add_subdirectory(Engine)


add_executable
(
	cute
	main.c
)

target_link_libraries(cute PRIVATE CuteEngine)

target_compile_options
(
    cute
    PRIVATE 
    -Wall -Wextra -g
)

set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)