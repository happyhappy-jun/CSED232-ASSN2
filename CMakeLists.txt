cmake_minimum_required(VERSION 3.15)
project(ASSN2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ASSN2
        main.cpp
        database.cpp
        menu.cpp
        menu.h)
