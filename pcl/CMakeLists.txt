cmake_minimum_required(VERSION 3.5)
project(test_pcl)

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(test_pcl test_pcl.cpp)
target_link_libraries (test_pcl ${PCL_LIBRARIES} usb-1.0)
install(TARGETS test_pcl RUNTIME DESTINATION bin)