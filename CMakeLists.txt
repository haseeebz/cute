cmake_minimum_required(VERSION 3.10)

project(cute C)

set(SOURCES
    cute/main.c

    cute/lexer/tokens.c
	cute/lexer/lexer.c

	cute/atoms/atoms.c
	cute/parser/parser.c
)

add_executable(cute ${SOURCES})

target_compile_options(cute PRIVATE -Wall -Wextra -g)

set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
