cmake_minimum_required(VERSION 3.29)
project(dry)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dry
    main.cpp
    Pirate.cpp
    Pirate.h)
