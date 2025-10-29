
file(GLOB LEXER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")

add_library (
	CuteCompiler
	STATIC

    ${LEXER_SRC}
    compiler.cpp 

)

target_link_libraries(CuteCompiler PRIVATE CuteByte)

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