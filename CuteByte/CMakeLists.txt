
add_library (
	CuteByte
	STATIC
    bytes.c
)


target_compile_options (
    CuteByte
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteByte
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)