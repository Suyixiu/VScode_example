# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build

# Include any dependencies generated for this target.
include CMakeFiles/cmake_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmake_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmake_test.dir/flags.make

CMakeFiles/cmake_test.dir/src/add.cpp.o: CMakeFiles/cmake_test.dir/flags.make
CMakeFiles/cmake_test.dir/src/add.cpp.o: ../src/add.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmake_test.dir/src/add.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmake_test.dir/src/add.cpp.o -c /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/src/add.cpp

CMakeFiles/cmake_test.dir/src/add.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmake_test.dir/src/add.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/src/add.cpp > CMakeFiles/cmake_test.dir/src/add.cpp.i

CMakeFiles/cmake_test.dir/src/add.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmake_test.dir/src/add.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/src/add.cpp -o CMakeFiles/cmake_test.dir/src/add.cpp.s

CMakeFiles/cmake_test.dir/src/add.cpp.o.requires:

.PHONY : CMakeFiles/cmake_test.dir/src/add.cpp.o.requires

CMakeFiles/cmake_test.dir/src/add.cpp.o.provides: CMakeFiles/cmake_test.dir/src/add.cpp.o.requires
	$(MAKE) -f CMakeFiles/cmake_test.dir/build.make CMakeFiles/cmake_test.dir/src/add.cpp.o.provides.build
.PHONY : CMakeFiles/cmake_test.dir/src/add.cpp.o.provides

CMakeFiles/cmake_test.dir/src/add.cpp.o.provides.build: CMakeFiles/cmake_test.dir/src/add.cpp.o


CMakeFiles/cmake_test.dir/src/sub.cpp.o: CMakeFiles/cmake_test.dir/flags.make
CMakeFiles/cmake_test.dir/src/sub.cpp.o: ../src/sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cmake_test.dir/src/sub.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmake_test.dir/src/sub.cpp.o -c /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/src/sub.cpp

CMakeFiles/cmake_test.dir/src/sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmake_test.dir/src/sub.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/src/sub.cpp > CMakeFiles/cmake_test.dir/src/sub.cpp.i

CMakeFiles/cmake_test.dir/src/sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmake_test.dir/src/sub.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/src/sub.cpp -o CMakeFiles/cmake_test.dir/src/sub.cpp.s

CMakeFiles/cmake_test.dir/src/sub.cpp.o.requires:

.PHONY : CMakeFiles/cmake_test.dir/src/sub.cpp.o.requires

CMakeFiles/cmake_test.dir/src/sub.cpp.o.provides: CMakeFiles/cmake_test.dir/src/sub.cpp.o.requires
	$(MAKE) -f CMakeFiles/cmake_test.dir/build.make CMakeFiles/cmake_test.dir/src/sub.cpp.o.provides.build
.PHONY : CMakeFiles/cmake_test.dir/src/sub.cpp.o.provides

CMakeFiles/cmake_test.dir/src/sub.cpp.o.provides.build: CMakeFiles/cmake_test.dir/src/sub.cpp.o


CMakeFiles/cmake_test.dir/main.cpp.o: CMakeFiles/cmake_test.dir/flags.make
CMakeFiles/cmake_test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cmake_test.dir/main.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmake_test.dir/main.cpp.o -c /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/main.cpp

CMakeFiles/cmake_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmake_test.dir/main.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/main.cpp > CMakeFiles/cmake_test.dir/main.cpp.i

CMakeFiles/cmake_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmake_test.dir/main.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/main.cpp -o CMakeFiles/cmake_test.dir/main.cpp.s

CMakeFiles/cmake_test.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/cmake_test.dir/main.cpp.o.requires

CMakeFiles/cmake_test.dir/main.cpp.o.provides: CMakeFiles/cmake_test.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cmake_test.dir/build.make CMakeFiles/cmake_test.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/cmake_test.dir/main.cpp.o.provides

CMakeFiles/cmake_test.dir/main.cpp.o.provides.build: CMakeFiles/cmake_test.dir/main.cpp.o


# Object files for target cmake_test
cmake_test_OBJECTS = \
"CMakeFiles/cmake_test.dir/src/add.cpp.o" \
"CMakeFiles/cmake_test.dir/src/sub.cpp.o" \
"CMakeFiles/cmake_test.dir/main.cpp.o"

# External object files for target cmake_test
cmake_test_EXTERNAL_OBJECTS =

../Bin/cmake_test: CMakeFiles/cmake_test.dir/src/add.cpp.o
../Bin/cmake_test: CMakeFiles/cmake_test.dir/src/sub.cpp.o
../Bin/cmake_test: CMakeFiles/cmake_test.dir/main.cpp.o
../Bin/cmake_test: CMakeFiles/cmake_test.dir/build.make
../Bin/cmake_test: CMakeFiles/cmake_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../Bin/cmake_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmake_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmake_test.dir/build: ../Bin/cmake_test

.PHONY : CMakeFiles/cmake_test.dir/build

CMakeFiles/cmake_test.dir/requires: CMakeFiles/cmake_test.dir/src/add.cpp.o.requires
CMakeFiles/cmake_test.dir/requires: CMakeFiles/cmake_test.dir/src/sub.cpp.o.requires
CMakeFiles/cmake_test.dir/requires: CMakeFiles/cmake_test.dir/main.cpp.o.requires

.PHONY : CMakeFiles/cmake_test.dir/requires

CMakeFiles/cmake_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmake_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmake_test.dir/clean

CMakeFiles/cmake_test.dir/depend:
	cd /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build /home/suyixiu/VScode/VScode_example/ubuntu/cmke_example/build/CMakeFiles/cmake_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmake_test.dir/depend

