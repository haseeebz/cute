cmake_minimum_required(VERSION 3.10)

project(cute C)

set(SOURCES
    cute/main.c

	cute/core/core.c

	cute/parser/node.c
	cute/parser/parser.c

	cute/parser/lexer/tokens.c
	cute/parser/lexer/lexer.c
)

add_executable(cute ${SOURCES})

target_compile_options(cute PRIVATE -Wall -Wextra -g)

set_target_properties(cute PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
