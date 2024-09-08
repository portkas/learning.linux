cmake_minimum_required(VERSION 3.28)
project(calc)
set(CMAKE_CXX_STANDARD 11)

# 包含头文件
include_directories(${CMAKE_SOURCE_DIR}/include)

# 搜索源文件
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# 指定生成动态库位置
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 生成动态库
add_library(calc SHARED ${SRC})