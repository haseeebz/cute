

add_library
(
	CuteEngine
	STATIC

)


target_compile_options
(
    CuteEngine 
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories
(
    CuteEngine 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)