#
# Base Station headers
#
# argos3/plugins/robots/base-station/simulator

PROJECT(base-station)
cmake_minimum_required(VERSION 3.5)
set(ARGOS_BUILD_FOR_SIMULATOR simulator) 

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_BASE_STATION_SIMULATOR
    simulator/dynamics2d_base_station_model.h
    # simulator/physx_base_station_model.h
    simulator/base_station_entity.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)
#
# E-puck sources
#
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_BASE_STATION
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_BASE_STATION}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_BASE_STATION_SIMULATOR}
    simulator/dynamics2d_base_station_model.cpp
    # simulator/physx_base_station_model.cpp
    simulator/base_station_entity.cpp)
  # Compile the graphical visualization only if the necessary libraries have been found
  include(./ARGoSCheckQTOpenGL.cmake)
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_BASE_STATION_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_BASE_STATION_SIMULATOR}
      simulator/qtopengl_base_station.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_BASE_STATION
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_BASE_STATION}
      simulator/qtopengl_base_station.h
      simulator/qtopengl_base_station.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Create e-puck plugin
#
add_library(argos3plugin_simulator_base_station SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_BASE_STATION})
target_link_libraries(argos3plugin_simulator_base_station
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
  /usr/local/lib/argos3/libargos3plugin_simulator_dynamics2d.so)
  # argos3plugin_simulator_physx)
if(ARGOS_BUILD_FOR_SIMULATOR AND ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_simulator_base_station /usr/local/lib/argos3/libargos3plugin_simulator_qtopengl.so)
endif(ARGOS_BUILD_FOR_SIMULATOR AND ARGOS_COMPILE_QTOPENGL)
