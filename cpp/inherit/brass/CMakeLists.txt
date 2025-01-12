cmake_minimum_required(VERSION 3.15)
project(brass)

add_executable( test1 
                brass.cpp
                usebrass1.cpp)

add_executable( test2
                brass.cpp
                usebrass2.cpp)