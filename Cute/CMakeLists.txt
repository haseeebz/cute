
file(GLOB LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_library (
	CuteLib
	STATIC
    ${LIB_SRC}
)

target_compile_options (
    CuteLib
    PRIVATE 
    -Wall -Wextra -g
)

target_include_directories (
    CuteLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)