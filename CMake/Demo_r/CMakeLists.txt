# # 指定最小版本
# cmake_minimum_required(VERSION 3.28)
# # 定义工程名
# project(Demo01)
# # 指定C++标准
# set(CMAKE_CXX_STANDARD 11)

# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# # 搜索源文件建立列表
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/calc CALC_SRC)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sort SORT_SRC)

# # 包含头文件
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# # 生成可执行文件
# add_executable(app main.cpp ${CALC_SRC} ${SORT_SRC})

cmake_minimum_required(VERSION 3.10)
project(Demo_r)
# 定义变量
# 静态库生成路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
# 可执行程序存储目录
set(EXECPATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件路径
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)
# 库文件的名字
set(CALCLIB calc)
set(SORTLIB sort)
# 可执行程序的名字
set(APPNAME1 app1)
set(APPNAME2 app2)

# 给当前节点添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test01)
add_subdirectory(test02)
