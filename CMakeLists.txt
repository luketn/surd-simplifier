cmake_minimum_required(VERSION 3.20)

project(surd_simplifier CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(surd_simplifier Surd.h main.cpp)
