# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mrrobot/repos/Cube-GLES2-PVR_PSP2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build

# Include any dependencies generated for this target.
include CMakeFiles/Cube-GLES2-PVR_PSP2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Cube-GLES2-PVR_PSP2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Cube-GLES2-PVR_PSP2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Cube-GLES2-PVR_PSP2.dir/flags.make

CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj: CMakeFiles/Cube-GLES2-PVR_PSP2.dir/flags.make
CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj: ../src/main.cpp
CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj: CMakeFiles/Cube-GLES2-PVR_PSP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj"
	/usr/local/vitasdk/bin/arm-vita-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj -MF CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj.d -o CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj -c /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/src/main.cpp

CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.i"
	/usr/local/vitasdk/bin/arm-vita-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/src/main.cpp > CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.i

CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.s"
	/usr/local/vitasdk/bin/arm-vita-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/src/main.cpp -o CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.s

# Object files for target Cube-GLES2-PVR_PSP2
Cube__GLES2__PVR_PSP2_OBJECTS = \
"CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj"

# External object files for target Cube-GLES2-PVR_PSP2
Cube__GLES2__PVR_PSP2_EXTERNAL_OBJECTS =

Cube-GLES2-PVR_PSP2: CMakeFiles/Cube-GLES2-PVR_PSP2.dir/src/main.cpp.obj
Cube-GLES2-PVR_PSP2: CMakeFiles/Cube-GLES2-PVR_PSP2.dir/build.make
Cube-GLES2-PVR_PSP2: CMakeFiles/Cube-GLES2-PVR_PSP2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Cube-GLES2-PVR_PSP2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Cube-GLES2-PVR_PSP2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Cube-GLES2-PVR_PSP2.dir/build: Cube-GLES2-PVR_PSP2
.PHONY : CMakeFiles/Cube-GLES2-PVR_PSP2.dir/build

CMakeFiles/Cube-GLES2-PVR_PSP2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Cube-GLES2-PVR_PSP2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Cube-GLES2-PVR_PSP2.dir/clean

CMakeFiles/Cube-GLES2-PVR_PSP2.dir/depend:
	cd /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mrrobot/repos/Cube-GLES2-PVR_PSP2 /home/mrrobot/repos/Cube-GLES2-PVR_PSP2 /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build /home/mrrobot/repos/Cube-GLES2-PVR_PSP2/cmake_build/CMakeFiles/Cube-GLES2-PVR_PSP2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Cube-GLES2-PVR_PSP2.dir/depend
