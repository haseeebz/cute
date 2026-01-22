
file(GLOB SPEC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/spec/*.cpp")

file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/*.cpp")
file(GLOB PARSER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp")
file(GLOB RESOLVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/resolver/*.cpp")


add_library (
	CuteCompiler
	STATIC

	${SPEC_SRC}

    ${TOKENIZER_SRC}
	${PARSER_SRC}
	${RESOLVER_SRC}
    compiler.cpp 
)

target_link_libraries(CuteCompiler PRIVATE CuteLib)

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