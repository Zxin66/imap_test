# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yangzonglin/iFPGA-submit/fpga-map-tool/build

# Include any dependencies generated for this target.
include test/CMakeFiles/test_cut.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_cut.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_cut.dir/flags.make

test/CMakeFiles/test_cut.dir/test_cut.cpp.o: test/CMakeFiles/test_cut.dir/flags.make
test/CMakeFiles/test_cut.dir/test_cut.cpp.o: /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA/test/test_cut.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangzonglin/iFPGA-submit/fpga-map-tool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_cut.dir/test_cut.cpp.o"
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test && /usr/bin/g++-11  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_cut.dir/test_cut.cpp.o -c /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA/test/test_cut.cpp

test/CMakeFiles/test_cut.dir/test_cut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_cut.dir/test_cut.cpp.i"
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA/test/test_cut.cpp > CMakeFiles/test_cut.dir/test_cut.cpp.i

test/CMakeFiles/test_cut.dir/test_cut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_cut.dir/test_cut.cpp.s"
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA/test/test_cut.cpp -o CMakeFiles/test_cut.dir/test_cut.cpp.s

test/CMakeFiles/test_cut.dir/test_cut.cpp.o.requires:

.PHONY : test/CMakeFiles/test_cut.dir/test_cut.cpp.o.requires

test/CMakeFiles/test_cut.dir/test_cut.cpp.o.provides: test/CMakeFiles/test_cut.dir/test_cut.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_cut.dir/build.make test/CMakeFiles/test_cut.dir/test_cut.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_cut.dir/test_cut.cpp.o.provides

test/CMakeFiles/test_cut.dir/test_cut.cpp.o.provides.build: test/CMakeFiles/test_cut.dir/test_cut.cpp.o


# Object files for target test_cut
test_cut_OBJECTS = \
"CMakeFiles/test_cut.dir/test_cut.cpp.o"

# External object files for target test_cut
test_cut_EXTERNAL_OBJECTS =

test/test_cut: test/CMakeFiles/test_cut.dir/test_cut.cpp.o
test/test_cut: test/CMakeFiles/test_cut.dir/build.make
test/test_cut: test/CMakeFiles/test_cut.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yangzonglin/iFPGA-submit/fpga-map-tool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_cut"
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_cut.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold unit_test_cut
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test && ./test_cut

# Rule to build all files generated by this target.
test/CMakeFiles/test_cut.dir/build: test/test_cut

.PHONY : test/CMakeFiles/test_cut.dir/build

test/CMakeFiles/test_cut.dir/requires: test/CMakeFiles/test_cut.dir/test_cut.cpp.o.requires

.PHONY : test/CMakeFiles/test_cut.dir/requires

test/CMakeFiles/test_cut.dir/clean:
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test && $(CMAKE_COMMAND) -P CMakeFiles/test_cut.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_cut.dir/clean

test/CMakeFiles/test_cut.dir/depend:
	cd /home/yangzonglin/iFPGA-submit/fpga-map-tool/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA /home/yangzonglin/iFPGA-submit/fpga-map-tool/iFPGA/test /home/yangzonglin/iFPGA-submit/fpga-map-tool/build /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test /home/yangzonglin/iFPGA-submit/fpga-map-tool/build/test/CMakeFiles/test_cut.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_cut.dir/depend

