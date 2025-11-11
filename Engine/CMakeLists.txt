
file(GLOB CONTEXT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/context/*.c")

add_library (
	CuteEngine
	STATIC

    engine.c
	${CONTEXT_SRC}

)

target_link_libraries(CuteEngine PRIVATE CuteBytecode)

target_compile_options (
    CuteEngine
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteEngine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)