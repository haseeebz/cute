cmake_minimum_required(VERSION 3.10)

project(cute C)

set(SOURCES
    cute/main.c
    cute/lexer/tokens.c
)

add_executable(cute ${SOURCES})

set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
