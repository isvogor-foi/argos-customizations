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
CMAKE_SOURCE_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build

# Include any dependencies generated for this target.
include CMakeFiles/tree_loops.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tree_loops.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tree_loops.dir/flags.make

CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o: CMakeFiles/tree_loops.dir/flags.make
CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o: ../tree_qt_loops.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/tree_qt_loops.cpp

CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/tree_qt_loops.cpp > CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.i

CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/tree_qt_loops.cpp -o CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.s

CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.requires:

.PHONY : CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.requires

CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.provides: CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.requires
	$(MAKE) -f CMakeFiles/tree_loops.dir/build.make CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.provides.build
.PHONY : CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.provides

CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.provides.build: CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o


CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o: CMakeFiles/tree_loops.dir/flags.make
CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o: tree_loops_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o -c /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/tree_loops_automoc.cpp

CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/tree_loops_automoc.cpp > CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.i

CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/tree_loops_automoc.cpp -o CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.s

CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.requires:

.PHONY : CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.requires

CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.provides: CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.requires
	$(MAKE) -f CMakeFiles/tree_loops.dir/build.make CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.provides.build
.PHONY : CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.provides

CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.provides.build: CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o


# Object files for target tree_loops
tree_loops_OBJECTS = \
"CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o" \
"CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o"

# External object files for target tree_loops
tree_loops_EXTERNAL_OBJECTS =

libtree_loops.so: CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o
libtree_loops.so: CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o
libtree_loops.so: CMakeFiles/tree_loops.dir/build.make
libtree_loops.so: /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so
libtree_loops.so: /home/ivan/dev/argos-custom/argos3/plugins/simulator/visualizations/qt-mod/build/libargos3plugin_mod_qtopengl.so
libtree_loops.so: /usr/lib/x86_64-linux-gnu/libglut.so
libtree_loops.so: /usr/lib/x86_64-linux-gnu/libXmu.so
libtree_loops.so: /usr/lib/x86_64-linux-gnu/libXi.so
libtree_loops.so: /usr/lib/x86_64-linux-gnu/libGLU.so
libtree_loops.so: /usr/lib/x86_64-linux-gnu/libGL.so
libtree_loops.so: CMakeFiles/tree_loops.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared module libtree_loops.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tree_loops.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tree_loops.dir/build: libtree_loops.so

.PHONY : CMakeFiles/tree_loops.dir/build

CMakeFiles/tree_loops.dir/requires: CMakeFiles/tree_loops.dir/tree_qt_loops.cpp.o.requires
CMakeFiles/tree_loops.dir/requires: CMakeFiles/tree_loops.dir/tree_loops_automoc.cpp.o.requires

.PHONY : CMakeFiles/tree_loops.dir/requires

CMakeFiles/tree_loops.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tree_loops.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tree_loops.dir/clean

CMakeFiles/tree_loops.dir/depend:
	cd /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build /home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/tree_loops/build/CMakeFiles/tree_loops.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tree_loops.dir/depend
