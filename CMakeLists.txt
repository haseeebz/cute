cmake_minimum_required(VERSION 3.10)

project(cute C)

set(SOURCES
    src/main.c
    src/other.c
)

add_executable(cute ${SOURCES})

# Force the binary into build/bin/exe
set_target_properties(my_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)
