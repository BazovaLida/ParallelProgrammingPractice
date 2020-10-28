cmake_minimum_required(VERSION 3.17)
project(PP_with_OpenMP)

set(CMAKE_CXX_STANDARD 14)

add_executable(PP_with_OpenMP main.cpp Data.cpp Data.h)