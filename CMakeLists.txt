cmake_minimum_required(VERSION 3.10)
project(cute C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Bytecode)
add_subdirectory(Tokenizer)

add_subdirectory(Assembler)
add_subdirectory(Compiler)

add_subdirectory(Engine)

add_subdirectory(Cute)