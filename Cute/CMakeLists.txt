add_library (
	CuteLib
	STATIC
    cute.cpp 
)


target_compile_options (
    CuteLib
    PRIVATE 
    -Wall -Wextra -g
)


target_include_directories (
    CuteLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)