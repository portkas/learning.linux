cmake_minimum_required(VERSION 3.28)
project(sort)
set(CMAKE_CXX_STANDARD 11)

# 包含库文件
include_directories(${CMAKE_SOURCE_DIR}/include)

# 搜索源文件
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# 指定动态库生成位置
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 生成动态库
add_library(sort SHARED ${SRC})