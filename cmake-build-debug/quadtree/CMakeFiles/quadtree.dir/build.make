# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/geesara/software/clion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/geesara/software/clion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/geesara/project/tmp/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/geesara/project/tmp/cmake/cmake-build-debug

# Include any dependencies generated for this target.
include quadtree/CMakeFiles/quadtree.dir/depend.make

# Include the progress variables for this target.
include quadtree/CMakeFiles/quadtree.dir/progress.make

# Include the compile flags for this target's objects.
include quadtree/CMakeFiles/quadtree.dir/flags.make

quadtree/CMakeFiles/quadtree.dir/quadtree.cc.o: quadtree/CMakeFiles/quadtree.dir/flags.make
quadtree/CMakeFiles/quadtree.dir/quadtree.cc.o: ../quadtree/quadtree.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/geesara/project/tmp/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object quadtree/CMakeFiles/quadtree.dir/quadtree.cc.o"
	cd /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quadtree.dir/quadtree.cc.o -c /home/geesara/project/tmp/cmake/quadtree/quadtree.cc

quadtree/CMakeFiles/quadtree.dir/quadtree.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quadtree.dir/quadtree.cc.i"
	cd /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/geesara/project/tmp/cmake/quadtree/quadtree.cc > CMakeFiles/quadtree.dir/quadtree.cc.i

quadtree/CMakeFiles/quadtree.dir/quadtree.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quadtree.dir/quadtree.cc.s"
	cd /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/geesara/project/tmp/cmake/quadtree/quadtree.cc -o CMakeFiles/quadtree.dir/quadtree.cc.s

# Object files for target quadtree
quadtree_OBJECTS = \
"CMakeFiles/quadtree.dir/quadtree.cc.o"

# External object files for target quadtree
quadtree_EXTERNAL_OBJECTS =

quadtree/libquadtree.a: quadtree/CMakeFiles/quadtree.dir/quadtree.cc.o
quadtree/libquadtree.a: quadtree/CMakeFiles/quadtree.dir/build.make
quadtree/libquadtree.a: quadtree/CMakeFiles/quadtree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/geesara/project/tmp/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libquadtree.a"
	cd /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree && $(CMAKE_COMMAND) -P CMakeFiles/quadtree.dir/cmake_clean_target.cmake
	cd /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quadtree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
quadtree/CMakeFiles/quadtree.dir/build: quadtree/libquadtree.a

.PHONY : quadtree/CMakeFiles/quadtree.dir/build

quadtree/CMakeFiles/quadtree.dir/clean:
	cd /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree && $(CMAKE_COMMAND) -P CMakeFiles/quadtree.dir/cmake_clean.cmake
.PHONY : quadtree/CMakeFiles/quadtree.dir/clean

quadtree/CMakeFiles/quadtree.dir/depend:
	cd /home/geesara/project/tmp/cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/geesara/project/tmp/cmake /home/geesara/project/tmp/cmake/quadtree /home/geesara/project/tmp/cmake/cmake-build-debug /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree /home/geesara/project/tmp/cmake/cmake-build-debug/quadtree/CMakeFiles/quadtree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : quadtree/CMakeFiles/quadtree.dir/depend
