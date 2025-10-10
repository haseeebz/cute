add_library(
	bytecodeLib
	STATIC
    loader.c
)

target_compile_options(bytecodeLib PRIVATE -Wall -Wextra -g)

target_include_directories(bytecodeLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
