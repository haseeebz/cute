
file(GLOB TOKENIZER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#file(GLOB WRITER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/writer/*.cpp")

add_library (
	CuteTokenizer
	STATIC

    ${TOKENIZER_SRC}

)

target_compile_options (
    CuteTokenizer
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteTokenizer
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)