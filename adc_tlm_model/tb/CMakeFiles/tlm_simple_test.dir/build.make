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
CMAKE_SOURCE_DIR = /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3

# Include any dependencies generated for this target.
include tb/CMakeFiles/tlm_simple_test.dir/depend.make

# Include the progress variables for this target.
include tb/CMakeFiles/tlm_simple_test.dir/progress.make

# Include the compile flags for this target's objects.
include tb/CMakeFiles/tlm_simple_test.dir/flags.make

tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o: tb/CMakeFiles/tlm_simple_test.dir/flags.make
tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o: tb/tlm_simple_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o"
	cd /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o -c /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb/tlm_simple_test.cpp

tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.i"
	cd /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb/tlm_simple_test.cpp > CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.i

tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.s"
	cd /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb/tlm_simple_test.cpp -o CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.s

tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.requires:

.PHONY : tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.requires

tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.provides: tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.requires
	$(MAKE) -f tb/CMakeFiles/tlm_simple_test.dir/build.make tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.provides.build
.PHONY : tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.provides

tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.provides.build: tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o


# Object files for target tlm_simple_test
tlm_simple_test_OBJECTS = \
"CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o"

# External object files for target tlm_simple_test
tlm_simple_test_EXTERNAL_OBJECTS =

bin/tlm_simple_test: tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o
bin/tlm_simple_test: tb/CMakeFiles/tlm_simple_test.dir/build.make
bin/tlm_simple_test: /usr/local/systemc-ams-2.1/lib-linux64/libsystemc-ams.so
bin/tlm_simple_test: /usr/local/systemc-2.3/lib-linux64/libsystemc.so
bin/tlm_simple_test: tb/CMakeFiles/tlm_simple_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/tlm_simple_test"
	cd /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tlm_simple_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tb/CMakeFiles/tlm_simple_test.dir/build: bin/tlm_simple_test

.PHONY : tb/CMakeFiles/tlm_simple_test.dir/build

tb/CMakeFiles/tlm_simple_test.dir/requires: tb/CMakeFiles/tlm_simple_test.dir/tlm_simple_test.cpp.o.requires

.PHONY : tb/CMakeFiles/tlm_simple_test.dir/requires

tb/CMakeFiles/tlm_simple_test.dir/clean:
	cd /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb && $(CMAKE_COMMAND) -P CMakeFiles/tlm_simple_test.dir/cmake_clean.cmake
.PHONY : tb/CMakeFiles/tlm_simple_test.dir/clean

tb/CMakeFiles/tlm_simple_test.dir/depend:
	cd /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3 /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3 /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb /home/sleebarr/EMECS_TUK/VP/vp_tasks/exercise_3/tb/CMakeFiles/tlm_simple_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tb/CMakeFiles/tlm_simple_test.dir/depend

