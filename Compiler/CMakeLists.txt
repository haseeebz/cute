
file(GLOB SPEC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/spec/*.cpp")
file(GLOB NODE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/node/*.cpp")
file(GLOB PARSER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp")
file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")

file(GLOB ANALYZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/analyzer/*.cpp")

file(GLOB TRANSPILER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/transpiler/*.cpp")

add_library (
	CuteCompiler
	STATIC

	${SPEC_SRC}
	${NODE_SRC}
	${PARSER_SRC}
	${TOKENIZER_SRC}
	${ANALYZER_SRC}
	${TRANSPILER_SRC}
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