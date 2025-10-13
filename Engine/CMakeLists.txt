
add_library(
	cuteEngine
	STATIC
    engine.c
	frame.c
)

target_compile_options(cuteEngine PRIVATE -Wall -Wextra -g)
target_link_libraries(cuteEngine PUBLIC cuteEngine)

target_include_directories(cuteEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
