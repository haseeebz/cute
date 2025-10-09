cmake_minimum_required(VERSION 3.10)
project(cute C)

add_subdirectory(engine)
add_subdirectory(bytecode)

add_executable(cute
    cute/main.c
)

target_link_libraries(cute PRIVATE engineLib)
target_link_libraries(cute PRIVATE bytecodeLib)


target_compile_options(cute PRIVATE -Wall -Wextra -g)

set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
