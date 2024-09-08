# 指定最小版本
cmake_minimum_required(VERSION 3.28)
# 定义工程名
project(Demo02)
# 指定C++标准
set(CMAKE_CXX_STANDARD 11)

# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(sortTest)
add_subdirectory(calcTest)