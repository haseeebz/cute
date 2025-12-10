
file(GLOB NODE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/node/*.cpp")
file(GLOB PARSER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp")
file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")

file(GLOB EMITTER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/emitter/*.cpp")

add_library (
	CuteCompiler
	STATIC

	${NODE_SRC}
	${PARSER_SRC}
	${TOKENIZER_SRC}
	${EMITTER_SRC}
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