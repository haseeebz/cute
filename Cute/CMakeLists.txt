
file(GLOB LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB INTERN_SRC "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.c")

add_library (
	CuteLib
	STATIC
    ${LIB_SRC}
	${INTERN_SRC}
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