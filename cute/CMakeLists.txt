

add_executable (
	cute
	
	main.cpp
	core.cpp
)

target_link_libraries(cute PRIVATE CuteCompiler)
target_link_libraries(cute PRIVATE CuteEngine)
target_link_libraries(cute PRIVATE CuteBytecode)

target_compile_options (
    cute
    PRIVATE 
    -Wall -Wextra -g
)

set_target_properties (
    cute 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)