# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\software\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\software\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\build

# Include any dependencies generated for this target.
include CMakeFiles/sample_opencv_cmake.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sample_opencv_cmake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sample_opencv_cmake.dir/flags.make

CMakeFiles/sample_opencv_cmake.dir/main.cpp.obj: CMakeFiles/sample_opencv_cmake.dir/flags.make
CMakeFiles/sample_opencv_cmake.dir/main.cpp.obj: CMakeFiles/sample_opencv_cmake.dir/includes_CXX.rsp
CMakeFiles/sample_opencv_cmake.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sample_opencv_cmake.dir/main.cpp.obj"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\sample_opencv_cmake.dir\main.cpp.obj -c C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\main.cpp

CMakeFiles/sample_opencv_cmake.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample_opencv_cmake.dir/main.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\main.cpp > CMakeFiles\sample_opencv_cmake.dir\main.cpp.i

CMakeFiles/sample_opencv_cmake.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample_opencv_cmake.dir/main.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\main.cpp -o CMakeFiles\sample_opencv_cmake.dir\main.cpp.s

# Object files for target sample_opencv_cmake
sample_opencv_cmake_OBJECTS = \
"CMakeFiles/sample_opencv_cmake.dir/main.cpp.obj"

# External object files for target sample_opencv_cmake
sample_opencv_cmake_EXTERNAL_OBJECTS =

../Bin/sample_opencv_cmake.exe: CMakeFiles/sample_opencv_cmake.dir/main.cpp.obj
../Bin/sample_opencv_cmake.exe: CMakeFiles/sample_opencv_cmake.dir/build.make
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_stitching341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_superres341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_videostab341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_aruco341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_bgsegm341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_bioinspired341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_ccalib341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_dpm341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_face341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_fuzzy341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_hdf341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_hfs341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_img_hash341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_line_descriptor341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_optflow341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_reg341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_rgbd341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_saliency341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_stereo341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_structured_light341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_surface_matching341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_tracking341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_xfeatures2d341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_ximgproc341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_xobjdetect341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_xphoto341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_shape341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_photo341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_datasets341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_ml341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_plot341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_video341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_calib3d341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_features2d341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_highgui341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_videoio341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_phase_unwrapping341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_flann341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_imgcodecs341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_objdetect341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_imgproc341.dll.a
../Bin/sample_opencv_cmake.exe: C:/software/opencv/opencv/build/x64/mingw/lib/libopencv_core341.dll.a
../Bin/sample_opencv_cmake.exe: CMakeFiles/sample_opencv_cmake.dir/linklibs.rsp
../Bin/sample_opencv_cmake.exe: CMakeFiles/sample_opencv_cmake.dir/objects1.rsp
../Bin/sample_opencv_cmake.exe: CMakeFiles/sample_opencv_cmake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\Bin\sample_opencv_cmake.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sample_opencv_cmake.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sample_opencv_cmake.dir/build: ../Bin/sample_opencv_cmake.exe

.PHONY : CMakeFiles/sample_opencv_cmake.dir/build

CMakeFiles/sample_opencv_cmake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\sample_opencv_cmake.dir\cmake_clean.cmake
.PHONY : CMakeFiles/sample_opencv_cmake.dir/clean

CMakeFiles/sample_opencv_cmake.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\build C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\build C:\Users\Suyixiu\Desktop\vscode\VScode_exsample\opencv_cmake\build\CMakeFiles\sample_opencv_cmake.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sample_opencv_cmake.dir/depend

