cmake_minimum_required(VERSION 3.28)
project(calcTest)
set(CMAKE_CXX_STANDARD 11)

# 包含头文件
include_directories(${CMAKE_SOURCE_DIR}/include)

# 搜索源文件
# file(GLOB SRC &{CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
aux_source_directory(./ SRC)

# 指定动态库文件位置
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 指定生成的可执行文件位置
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 生成可执行文件
add_executable(calcapp ${SRC})

# 链接动态库
target_link_libraries(calcapp calc)