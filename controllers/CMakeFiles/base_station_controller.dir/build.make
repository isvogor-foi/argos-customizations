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
CMAKE_SOURCE_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers

# Include any dependencies generated for this target.
include CMakeFiles/base_station_controller.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/base_station_controller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/base_station_controller.dir/flags.make

CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o: CMakeFiles/base_station_controller.dir/flags.make
CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o: base_station_obstacleavoidance.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/controllers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers/base_station_obstacleavoidance.cpp

CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers/base_station_obstacleavoidance.cpp > CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.i

CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers/base_station_obstacleavoidance.cpp -o CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.s

CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.requires:

.PHONY : CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.requires

CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.provides: CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.requires
	$(MAKE) -f CMakeFiles/base_station_controller.dir/build.make CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.provides.build
.PHONY : CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.provides

CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.provides.build: CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o


# Object files for target base_station_controller
base_station_controller_OBJECTS = \
"CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o"

# External object files for target base_station_controller
base_station_controller_EXTERNAL_OBJECTS =

libbase_station_controller.so: CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o
libbase_station_controller.so: CMakeFiles/base_station_controller.dir/build.make
libbase_station_controller.so: /usr/local/lib/argos3/libargos3core_simulator.so
libbase_station_controller.so: /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
libbase_station_controller.so: /home/ivan/dev/argos-custom/argos3/plugins/robots/base-station/libargos3plugin_simulator_base_station.so
libbase_station_controller.so: CMakeFiles/base_station_controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/controllers/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libbase_station_controller.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base_station_controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/base_station_controller.dir/build: libbase_station_controller.so

.PHONY : CMakeFiles/base_station_controller.dir/build

CMakeFiles/base_station_controller.dir/requires: CMakeFiles/base_station_controller.dir/base_station_obstacleavoidance.cpp.o.requires

.PHONY : CMakeFiles/base_station_controller.dir/requires

CMakeFiles/base_station_controller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/base_station_controller.dir/cmake_clean.cmake
.PHONY : CMakeFiles/base_station_controller.dir/clean

CMakeFiles/base_station_controller.dir/depend:
	cd /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers /home/ivan/dev/argos-custom/argos3/plugins/robots/controllers/CMakeFiles/base_station_controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/base_station_controller.dir/depend

