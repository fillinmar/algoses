# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fillinmar/algoses/2модуль/4sem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fillinmar/algoses/2модуль/4sem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/4sem.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/4sem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/4sem.dir/flags.make

CMakeFiles/4sem.dir/main.cpp.o: CMakeFiles/4sem.dir/flags.make
CMakeFiles/4sem.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fillinmar/algoses/2модуль/4sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/4sem.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/4sem.dir/main.cpp.o -c /home/fillinmar/algoses/2модуль/4sem/main.cpp

CMakeFiles/4sem.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4sem.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fillinmar/algoses/2модуль/4sem/main.cpp > CMakeFiles/4sem.dir/main.cpp.i

CMakeFiles/4sem.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4sem.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fillinmar/algoses/2модуль/4sem/main.cpp -o CMakeFiles/4sem.dir/main.cpp.s

# Object files for target 4sem
4sem_OBJECTS = \
"CMakeFiles/4sem.dir/main.cpp.o"

# External object files for target 4sem
4sem_EXTERNAL_OBJECTS =

4sem: CMakeFiles/4sem.dir/main.cpp.o
4sem: CMakeFiles/4sem.dir/build.make
4sem: CMakeFiles/4sem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fillinmar/algoses/2модуль/4sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 4sem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/4sem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/4sem.dir/build: 4sem

.PHONY : CMakeFiles/4sem.dir/build

CMakeFiles/4sem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/4sem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/4sem.dir/clean

CMakeFiles/4sem.dir/depend:
	cd /home/fillinmar/algoses/2модуль/4sem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fillinmar/algoses/2модуль/4sem /home/fillinmar/algoses/2модуль/4sem /home/fillinmar/algoses/2модуль/4sem/cmake-build-debug /home/fillinmar/algoses/2модуль/4sem/cmake-build-debug /home/fillinmar/algoses/2модуль/4sem/cmake-build-debug/CMakeFiles/4sem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/4sem.dir/depend

