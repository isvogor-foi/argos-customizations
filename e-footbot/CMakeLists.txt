#
# Foot-bot headers
#

PROJECT(efootbot)
cmake_minimum_required(VERSION 3.5)
set(ARGOS_BUILD_FOR simulator) 


set(ARGOS3_HEADERS_PLUGINS_ROBOTS_EFOOTBOT_CONTROLINTERFACE
  control_interface/ci_efootbot_base_ground_sensor.h
  control_interface/ci_efootbot_distance_scanner_actuator.h
  control_interface/ci_efootbot_distance_scanner_sensor.h
  control_interface/ci_efootbot_encoder_sensor.h
  control_interface/ci_efootbot_gripper_actuator.h
  control_interface/ci_efootbot_light_sensor.h
  control_interface/ci_efootbot_motor_ground_sensor.h
  control_interface/ci_efootbot_proximity_sensor.h
  control_interface/ci_efootbot_turret_actuator.h
  control_interface/ci_efootbot_turret_encoder_sensor.h)
# argos3/plugins/robots/foot-bot/simulator


  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_EFOOTBOT_SIMULATOR
    simulator/dynamics2d_efootbot_model.h
    # simulator/physx_efootbot_model.h
    simulator/efootbot_base_ground_rotzonly_sensor.h
    simulator/efootbot_distance_scanner_default_actuator.h
    simulator/efootbot_distance_scanner_equipped_entity.h
    simulator/efootbot_distance_scanner_rotzonly_sensor.h
    simulator/efootbot_entity.h
    simulator/efootbot_gripper_default_actuator.h
    simulator/efootbot_light_rotzonly_sensor.h
    simulator/efootbot_motor_ground_rotzonly_sensor.h
    simulator/efootbot_proximity_default_sensor.h
    simulator/efootbot_turret_default_actuator.h
    simulator/efootbot_turret_encoder_default_sensor.h
    simulator/efootbot_turret_entity.h)

#
# Foot-bot sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_EFOOTBOT
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_EFOOTBOT_CONTROLINTERFACE}
  control_interface/ci_efootbot_base_ground_sensor.cpp
  control_interface/ci_efootbot_distance_scanner_actuator.cpp
  control_interface/ci_efootbot_distance_scanner_sensor.cpp
  control_interface/ci_efootbot_encoder_sensor.cpp
  control_interface/ci_efootbot_gripper_actuator.cpp
  control_interface/ci_efootbot_light_sensor.cpp
  control_interface/ci_efootbot_motor_ground_sensor.cpp
  control_interface/ci_efootbot_proximity_sensor.cpp
  control_interface/ci_efootbot_turret_actuator.cpp
  control_interface/ci_efootbot_turret_encoder_sensor.cpp)

  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_EFOOTBOT
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_EFOOTBOT}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_EFOOTBOT_SIMULATOR}
    simulator/dynamics2d_efootbot_model.cpp
    # simulator/physx_efootbot_model.cpp
    simulator/efootbot_base_ground_rotzonly_sensor.cpp
    simulator/efootbot_distance_scanner_default_actuator.cpp
    simulator/efootbot_distance_scanner_equipped_entity.cpp
    simulator/efootbot_distance_scanner_rotzonly_sensor.cpp
    simulator/efootbot_entity.cpp
    simulator/efootbot_gripper_default_actuator.cpp
    simulator/efootbot_light_rotzonly_sensor.cpp
    simulator/efootbot_motor_ground_rotzonly_sensor.cpp
    simulator/efootbot_proximity_default_sensor.cpp
    simulator/efootbot_turret_default_actuator.cpp
    simulator/efootbot_turret_encoder_default_sensor.cpp
    simulator/efootbot_turret_entity.cpp)
  # Compile the graphical visualization only if the necessary libraries have been found
  include(./ARGoSCheckQTOpenGL.cmake)
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_EFOOTBOT_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_EFOOTBOT_SIMULATOR}
      simulator/qtopengl_efootbot.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_EFOOTBOT
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_EFOOTBOT}
      simulator/qtopengl_efootbot.h
      simulator/qtopengl_efootbot.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)

#
# Create foot-bot plugin
#
add_library(argos3plugin_simulator_efootbot SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_EFOOTBOT})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_efootbot
  /usr/local/lib/argos3/libargos3plugin_${ARGOS_BUILD_FOR}_genericrobot.so
  /usr/local/lib/argos3/libargos3plugin_${ARGOS_BUILD_FOR}_dynamics2d.so)
  # argos3plugin_${ARGOS_BUILD_FOR}_physx)
if(ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_efootbot /usr/local/lib/argos3/libargos3plugin_${ARGOS_BUILD_FOR}_qtopengl.so)
endif(ARGOS_COMPILE_QTOPENGL)


