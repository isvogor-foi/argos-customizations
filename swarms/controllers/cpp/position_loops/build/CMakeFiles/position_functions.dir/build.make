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
CMAKE_SOURCE_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build

# Include any dependencies generated for this target.
include CMakeFiles/position_functions.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/position_functions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/position_functions.dir/flags.make

CMakeFiles/position_functions.dir/position_functions.cpp.o: CMakeFiles/position_functions.dir/flags.make
CMakeFiles/position_functions.dir/position_functions.cpp.o: ../position_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/position_functions.dir/position_functions.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/position_functions.dir/position_functions.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/position_functions.cpp

CMakeFiles/position_functions.dir/position_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/position_functions.dir/position_functions.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/position_functions.cpp > CMakeFiles/position_functions.dir/position_functions.cpp.i

CMakeFiles/position_functions.dir/position_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/position_functions.dir/position_functions.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/position_functions.cpp -o CMakeFiles/position_functions.dir/position_functions.cpp.s

CMakeFiles/position_functions.dir/position_functions.cpp.o.requires:

.PHONY : CMakeFiles/position_functions.dir/position_functions.cpp.o.requires

CMakeFiles/position_functions.dir/position_functions.cpp.o.provides: CMakeFiles/position_functions.dir/position_functions.cpp.o.requires
	$(MAKE) -f CMakeFiles/position_functions.dir/build.make CMakeFiles/position_functions.dir/position_functions.cpp.o.provides.build
.PHONY : CMakeFiles/position_functions.dir/position_functions.cpp.o.provides

CMakeFiles/position_functions.dir/position_functions.cpp.o.provides.build: CMakeFiles/position_functions.dir/position_functions.cpp.o


CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o: CMakeFiles/position_functions.dir/flags.make
CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o: position_functions_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/position_functions_automoc.cpp

CMakeFiles/position_functions.dir/position_functions_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/position_functions.dir/position_functions_automoc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/position_functions_automoc.cpp > CMakeFiles/position_functions.dir/position_functions_automoc.cpp.i

CMakeFiles/position_functions.dir/position_functions_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/position_functions.dir/position_functions_automoc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/position_functions_automoc.cpp -o CMakeFiles/position_functions.dir/position_functions_automoc.cpp.s

CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.requires:

.PHONY : CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.requires

CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.provides: CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.requires
	$(MAKE) -f CMakeFiles/position_functions.dir/build.make CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.provides.build
.PHONY : CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.provides

CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.provides.build: CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o


# Object files for target position_functions
position_functions_OBJECTS = \
"CMakeFiles/position_functions.dir/position_functions.cpp.o" \
"CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o"

# External object files for target position_functions
position_functions_EXTERNAL_OBJECTS =

libposition_functions.so: CMakeFiles/position_functions.dir/position_functions.cpp.o
libposition_functions.so: CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o
libposition_functions.so: CMakeFiles/position_functions.dir/build.make
libposition_functions.so: /home/ivan/dev/argos3/build_simulator/core/libargos3core_simulator.so
libposition_functions.so: /home/ivan/dev/argos3/build_simulator/plugins/simulator/entities/libargos3plugin_simulator_entities.so
libposition_functions.so: /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so
libposition_functions.so: /home/ivan/dev/argos3/build_simulator/plugins/simulator/visualizations/qt-opengl/libargos3plugin_simulator_qtopengl.so
libposition_functions.so: /usr/lib/x86_64-linux-gnu/libglut.so
libposition_functions.so: /usr/lib/x86_64-linux-gnu/libXmu.so
libposition_functions.so: /usr/lib/x86_64-linux-gnu/libXi.so
libposition_functions.so: /usr/lib/x86_64-linux-gnu/libGLU.so
libposition_functions.so: /usr/lib/x86_64-linux-gnu/libGL.so
libposition_functions.so: CMakeFiles/position_functions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module libposition_functions.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/position_functions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/position_functions.dir/build: libposition_functions.so

.PHONY : CMakeFiles/position_functions.dir/build

CMakeFiles/position_functions.dir/requires: CMakeFiles/position_functions.dir/position_functions.cpp.o.requires
CMakeFiles/position_functions.dir/requires: CMakeFiles/position_functions.dir/position_functions_automoc.cpp.o.requires

.PHONY : CMakeFiles/position_functions.dir/requires

CMakeFiles/position_functions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/position_functions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/position_functions.dir/clean

CMakeFiles/position_functions.dir/depend:
	cd /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/position_loops/build/CMakeFiles/position_functions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/position_functions.dir/depend

