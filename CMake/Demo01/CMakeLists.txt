# 指定最小版本
cmake_minimum_required(VERSION 3.28)
# 定义工程名
project(Demo01)
# 指定C++标准
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 搜索源文件建立列表
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/calc CALC_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sort SORT_SRC)

# 包含头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 生成可执行文件
add_executable(app main.cpp ${CALC_SRC} ${SORT_SRC})
