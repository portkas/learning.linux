cmake_minimum_required(VERSION 3.10)
project(calc)

# 搜索源文件
aux_source_directory(./ SRC)
# 指定包含的头文件
include_directories(${HEADPATH})
# 指定静态库生成的路径
set(LIBRARY_OUTPUT_PATH ${LIBPATH})
# 生成静态库
add_library(${CALCLIB} STATIC ${SRC})
