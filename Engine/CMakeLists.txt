
file(GLOB EXE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/exe/*.c")

add_library (
	CuteEngine
	STATIC

    ${EXE_SRC}
    engine.c
   
)

target_link_libraries(CuteEngine PRIVATE CuteByte)

target_compile_options (
    CuteEngine 
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteEngine 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)