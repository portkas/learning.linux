cmake_minimum_required(VERSION 3.15)
project(tennis0)

file(GLOB SRC *.cpp)
add_executable(app ${SRC})