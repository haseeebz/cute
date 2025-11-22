
file(GLOB ASSEMBLER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#file(GLOB WRITER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/writer/*.cpp")

add_library (
	CuteAssembler
	STATIC

	${ASSEMBLER_SRC}
)

target_link_libraries(CuteAssembler PRIVATE CuteBytecode CuteTokenizer)

target_compile_options (
    CuteAssembler
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteAssembler
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)