cmake_minimum_required(VERSION 3.20)
project(external)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(app ${SRC})