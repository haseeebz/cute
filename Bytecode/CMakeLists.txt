
add_library(
	cuteBytecode
	STATIC
    source.c
)

target_compile_options(cuteBytecode PRIVATE -Wall -Wextra -g)

target_include_directories(cuteBytecode PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)