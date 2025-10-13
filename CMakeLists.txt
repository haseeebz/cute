cmake_minimum_required(VERSION 3.10)
project(cute C)


add_subdirectory(Bytecode)
# add_subdirectory(Engine)

add_executable(
	cute
	Cute/main.c
)

target_link_libraries(cute PRIVATE CuteBytecode)
# target_link_libraries(cute PRIVATE CuteEngine)

target_compile_options(cute PRIVATE -Wall -Wextra -g -I.)

set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
