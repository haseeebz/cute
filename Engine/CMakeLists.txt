
#file(GLOB WRITER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/writer/*.cpp")

add_library (
	CuteEngine
	STATIC

    engine.c

)

target_link_libraries(CuteEngine PRIVATE CuteBytecode)

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