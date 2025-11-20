
file(GLOB CORE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/core/*.c")
file(GLOB STATE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/state/*.c")

add_library (
	CuteEngine
	STATIC

    ${CORE_SRC}
	${STATE_SRC}

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