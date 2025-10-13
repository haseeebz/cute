
add_library(
	CuteEngine
	STATIC
    engine.c
	frame.c
)

target_compile_options(CuteEngine PRIVATE -Wall -Wextra -g)
target_link_libraries(CuteEngine PUBLIC CuteEngine)

target_include_directories(CuteEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
