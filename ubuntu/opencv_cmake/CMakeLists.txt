cmake_minimum_required (VERSION 3.0.0)

# 输出
message("this is a simple output for cmake")

# 工程名字
project(sample_opencv_cmake)

set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS  "-g -fexec-charset=GBK")

# 查看opencv安装位置pkg-config opencv --libs
##### set一个XXX_DIR告诉CMake去哪里找XXXConfig.cmake这个东西 #####
set(OpenCV_DIR /usr/local/share/OpenCV)
find_package( OpenCV REQUIRED )

# message(STATUS "OpenCV library status:")
# message(STATUS "version: ${OpenCV_VERSION}")
# message(STATUS "libraries: ${OpenCV_LIBS}")
# message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")

# 头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 源文件
aux_source_directory(./ SrcFiles)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/Bin)
add_executable(sample_opencv_cmake ${SrcFiles})

target_link_libraries(sample_opencv_cmake ${OpenCV_LIBS})
