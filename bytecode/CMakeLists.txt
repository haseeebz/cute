
add_library (
	CuteBytecode
	STATIC
    bytes.c
)


target_compile_options (
    CuteBytecode
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteBytecode
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
