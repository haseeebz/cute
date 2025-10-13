
add_library(
	CuteEngine
	STATIC
    engine.c
	atom.c 
	context.c
)

target_compile_options(CuteEngine PRIVATE -Wall -Wextra -g)
target_link_libraries(CuteEngine PUBLIC CuteBytecode)

target_include_directories(CuteEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
