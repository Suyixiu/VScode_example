cmake_minimum_required(VERSION 2.6)
project(pcl_show_a_pcd)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcl_show_a_pcd pcl_show_a_pcd.cpp)

target_link_libraries (pcl_show_a_pcd ${PCL_LIBRARIES})

install(TARGETS pcl_show_a_pcd RUNTIME DESTINATION bin)