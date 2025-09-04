cmake_minimum_required(VERSION 3.10)
project(cute)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/cute/src/*.c")

add_executable(cute ${SRC_FILES})

target_compile_options(cute PRIVATE -Wall -Wextra -Wpedantic -g)

# Put the binary inside build/
set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
