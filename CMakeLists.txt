cmake_minimum_required(VERSION 3.18)
project(6502_CPU)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
add_executable(6502_CPU main.cc cpu.cc)
