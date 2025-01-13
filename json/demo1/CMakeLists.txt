cmake_minimum_required(VERSION 3.15)
project(jsontest)

include_directories(/usr/include/jsoncpp)
add_executable(app main.cpp)
target_link_libraries(app jsoncpp)