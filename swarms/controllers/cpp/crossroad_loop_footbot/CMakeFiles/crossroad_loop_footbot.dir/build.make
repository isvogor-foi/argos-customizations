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
CMAKE_SOURCE_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot

# Include any dependencies generated for this target.
include CMakeFiles/crossroad_loop_footbot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crossroad_loop_footbot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crossroad_loop_footbot.dir/flags.make

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o: CMakeFiles/crossroad_loop_footbot.dir/flags.make
CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o: crossroad_loop_footbot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/crossroad_loop_footbot.cpp

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/crossroad_loop_footbot.cpp > CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.i

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/crossroad_loop_footbot.cpp -o CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.s

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.requires:

.PHONY : CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.requires

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.provides: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.requires
	$(MAKE) -f CMakeFiles/crossroad_loop_footbot.dir/build.make CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.provides.build
.PHONY : CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.provides

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.provides.build: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o


CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o: CMakeFiles/crossroad_loop_footbot.dir/flags.make
CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o: crossroad_loop_footbot_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/crossroad_loop_footbot_automoc.cpp

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/crossroad_loop_footbot_automoc.cpp > CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.i

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/crossroad_loop_footbot_automoc.cpp -o CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.s

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.requires:

.PHONY : CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.requires

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.provides: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.requires
	$(MAKE) -f CMakeFiles/crossroad_loop_footbot.dir/build.make CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.provides.build
.PHONY : CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.provides

CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.provides.build: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o


# Object files for target crossroad_loop_footbot
crossroad_loop_footbot_OBJECTS = \
"CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o" \
"CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o"

# External object files for target crossroad_loop_footbot
crossroad_loop_footbot_EXTERNAL_OBJECTS =

libcrossroad_loop_footbot.so: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o
libcrossroad_loop_footbot.so: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o
libcrossroad_loop_footbot.so: CMakeFiles/crossroad_loop_footbot.dir/build.make
libcrossroad_loop_footbot.so: /home/ivan/dev/argos3/build_simulator/core/libargos3core_simulator.so
libcrossroad_loop_footbot.so: /home/ivan/dev/argos3/build_simulator/plugins/simulator/entities/libargos3plugin_simulator_entities.so
libcrossroad_loop_footbot.so: /home/ivan/dev/argos3/build_simulator/plugins/robots/foot-bot/libargos3plugin_simulator_footbot.so
libcrossroad_loop_footbot.so: /home/ivan/dev/argos3/build_simulator/plugins/simulator/visualizations/qt-opengl/libargos3plugin_simulator_qtopengl.so
libcrossroad_loop_footbot.so: /usr/lib/x86_64-linux-gnu/libglut.so
libcrossroad_loop_footbot.so: /usr/lib/x86_64-linux-gnu/libXmu.so
libcrossroad_loop_footbot.so: /usr/lib/x86_64-linux-gnu/libXi.so
libcrossroad_loop_footbot.so: /usr/lib/x86_64-linux-gnu/libGLU.so
libcrossroad_loop_footbot.so: /usr/lib/x86_64-linux-gnu/libGL.so
libcrossroad_loop_footbot.so: CMakeFiles/crossroad_loop_footbot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module libcrossroad_loop_footbot.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crossroad_loop_footbot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crossroad_loop_footbot.dir/build: libcrossroad_loop_footbot.so

.PHONY : CMakeFiles/crossroad_loop_footbot.dir/build

CMakeFiles/crossroad_loop_footbot.dir/requires: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot.cpp.o.requires
CMakeFiles/crossroad_loop_footbot.dir/requires: CMakeFiles/crossroad_loop_footbot.dir/crossroad_loop_footbot_automoc.cpp.o.requires

.PHONY : CMakeFiles/crossroad_loop_footbot.dir/requires

CMakeFiles/crossroad_loop_footbot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crossroad_loop_footbot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crossroad_loop_footbot.dir/clean

CMakeFiles/crossroad_loop_footbot.dir/depend:
	cd /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/crossroad_loop_footbot/CMakeFiles/crossroad_loop_footbot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crossroad_loop_footbot.dir/depend

