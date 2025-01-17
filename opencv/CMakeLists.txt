cmake_minimum_required(VERSION 3.10)
project(OpenCVExample)

find_package(OpenCV REQUIRED)
add_executable(app matbuild.cpp)
target_link_libraries(app ${OpenCV_LIBS})