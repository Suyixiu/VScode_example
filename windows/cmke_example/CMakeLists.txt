cmake_minimum_required (VERSION 3.0.0)

# 输出
set(message_show "this is a simple output for cmake")
message(${message_show})

# 工程名字
project(cmake_test)

set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS  "-g -fexec-charset=GBK")

# 添加include路径
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 源文件
aux_source_directory(./src SrcFiles)
aux_source_directory(./ SrcFiles)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/Bin)
add_executable(cmake_test ${SrcFiles})

