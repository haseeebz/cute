
file(GLOB SPEC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/spec/*.cpp")
file(GLOB NODE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/node/*.cpp")
file(GLOB PARSER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp")
file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")

file(GLOB ANALYZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/analyzer/*.cpp")
file(GLOB EMITTER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/emitter/*.cpp")

file(GLOB WRITER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/bytecode/*.cpp")


add_library (
	CuteCompiler
	STATIC

	${SPEC_SRC}
	${NODE_SRC}
	${PARSER_SRC}
	${TOKENIZER_SRC}
	${ANALYZER_SRC}
	${EMITTER_SRC}
	${WRITER_SRC}
    compiler.cpp 

)

target_link_libraries(CuteCompiler PRIVATE CuteBytecode)

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