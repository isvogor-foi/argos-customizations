PROJECT(charging_station)
cmake_minimum_required(VERSION 3.5)

 include(./ARGoSCheckQTOpenGL.cmake)

add_library(id_loop_functions MODULE 
  floor_power_functions.h
  floor_power_functions.cpp)

target_link_libraries(id_loop_functions
  /home/ivan/dev/argos3/core/libargos3core_simulator.so
  /home/ivan/dev/argos3/plugins/simulator/entities/libargos3plugin_simulator_entities.so
  /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so
  /home/ivan/dev/argos3/plugins/simulator/visualizations/qt-opengl/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})


