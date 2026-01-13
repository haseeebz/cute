
file(GLOB SPEC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/spec/*.cpp")

file(GLOB PARSER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp")
file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")


add_library (
	CuteCompiler
	STATIC

	${SPEC_SRC}
	${PARSER_SRC}
	${TOKENIZER_SRC}
    compiler.cpp 
)


target_compile_options (
    CuteCompiler
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteCompiler
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)