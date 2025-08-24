cmake_minimum_required(VERSION 3.10)

project(MathEval VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(math main.cpp ${SOURCES})
target_compile_options(math PRIVATE -g -Wall -Wextra -O2)

