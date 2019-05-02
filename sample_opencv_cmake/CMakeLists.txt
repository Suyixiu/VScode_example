cmake_minimum_required (VERSION 3.0.0)

# 输出
message("this is a simple output for cmake")

# 工程名字
project(sample_opencv_cmake)

set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS  "-g -fexec-charset=GBK")

set(OpenCV_DIR C:/software/opencv/opencv/build/x64/MinGW/lib)
find_package( OpenCV REQUIRED )

# 头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 源文件
aux_source_directory(./ SrcFiles)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/Bin)
add_executable(sample_opencv_cmake ${SrcFiles})

target_link_libraries(sample_opencv_cmake ${OpenCV_LIBS})
