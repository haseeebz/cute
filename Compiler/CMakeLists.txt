
file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")
file(GLOB PARSER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp")
file(GLOB WRITER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/writer/*.cpp")

add_library (
	CuteCompiler
	STATIC

    ${TOKENIZER_SRC}
	${PARSER_SRC}
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