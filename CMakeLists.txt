cmake_minimum_required(VERSION 3.15)
project(ASSN2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
add_executable(ASSN2
        main.cpp
        database.cpp
        menu.cpp
        headers/menu.h headers/post.h post.cpp member.cpp headers/member.h headers/list.h list.cpp)
