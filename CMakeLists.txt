cmake_minimum_required(VERSION 3.10)
project(cute C CXX)

add_subdirectory(Bytecode)
add_subdirectory(Engine)
add_subdirectory(Compiler)



add_executable (
	cute
	main.cpp
)

target_link_libraries(cute PRIVATE CuteCompiler)
target_link_libraries(cute PRIVATE CuteEngine)
target_link_libraries(cute PRIVATE CuteBytecode)


target_compile_options (
    cute
    PRIVATE 
    -Wall -Wextra -g
)

set_target_properties (
    cute 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)