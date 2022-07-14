cmake_minimum_required(VERSION 3.22)
project(surd_simplifier C)

set(CMAKE_C_STANDARD 20)

include_directories(.)

add_executable(surd_simplifier
        Surd.h main.cpp)
