
file(GLOB NODE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/node/*.cpp")


add_library (
	CuteCompiler
	STATIC

	${NODE_SRC}
    compiler.cpp 

)

target_link_libraries(CuteCompiler PRIVATE CuteBytecode CuteTokenizer)

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