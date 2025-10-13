
add_library(
	engineLib
	STATIC
    engine.c
	frame.c
)

target_compile_options(engineLib PRIVATE -Wall -Wextra -g)
target_link_libraries(engineLib PUBLIC bytecodeLib)

target_include_directories(engineLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
