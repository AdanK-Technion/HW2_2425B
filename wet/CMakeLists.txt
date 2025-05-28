cmake_minimum_required(VERSION 3.29)
project(wet)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet
        Utilities.cpp
        Matrix.cpp
        tests.cpp
)

