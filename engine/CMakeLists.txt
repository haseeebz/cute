
add_library(
	engineLib
	STATIC
    engine.c
	frame.c
)

target_include_directories(engineLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
