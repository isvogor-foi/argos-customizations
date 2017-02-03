#
# E-pucky headers
#
# argos3/plugins/robots/e-pucky/simulator

PROJECT(epucky)
cmake_minimum_required(VERSION 3.5)
set(ARGOS_BUILD_FOR simulator) 

set(ARGOS3_HEADERS_PLUGINS_ROBOTS_EPUCKY_CONTROLINTERFACE
  control_interface/ci_battery_sensor.h)

set(ARGOS3_HEADERS_PLUGINS_ROBOTS_EPUCKY_SIMULATOR 
	simulator/dynamics2d_epucky_model.h 
  	simulator/battery_sensor.h
  	simulator/battery_sensor_equipped_entity.h
	simulator/epucky_entity.h
	)

#
# E-pucky sources
#

set(ARGOS3_SOURCES_PLUGINS_ROBOTS_EPUCKY 
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_EPUCKY_CONTROLINTERFACE}
      control_interface/ci_battery_sensor.cpp)

set(ARGOS3_SOURCES_PLUGINS_ROBOTS_EPUCKY 
	${ARGOS3_SOURCES_PLUGINS_ROBOTS_EPUCKY}
	${ARGOS3_HEADERS_PLUGINS_ROBOTS_EPUCKY_SIMULATOR}
    	simulator/dynamics2d_epucky_model.cpp
    	simulator/epucky_entity.cpp
      	simulator/battery_sensor.cpp
      	simulator/battery_sensor_equipped_entity.cpp)

  # Compile the graphical visualization only if the necessary libraries have been found


include(./ARGoSCheckQTOpenGL.cmake)

  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_EPUCKY_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_EPUCKY_SIMULATOR}
      simulator/qtopengl_epucky.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_EPUCKY
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_EPUCKY}
      simulator/qtopengl_epucky.h
      simulator/qtopengl_epucky.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)

#
# Create e-pucky plugin
#

add_library(argos3plugin_simulator_epucky SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_EPUCKY})
target_link_libraries(argos3plugin_simulator_epucky
  /usr/local/lib/argos3/libargos3plugin_simulator_entities.so	
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
  /usr/local/lib/argos3/libargos3plugin_simulator_dynamics2d.so)

if(ARGOS_BUILD_FOR_SIMULATOR AND ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_simulator_epucky argos3plugin_simulator_qtopengl)
endif(ARGOS_BUILD_FOR_SIMULATOR AND ARGOS_COMPILE_QTOPENGL)


