PROJECT(charging_station)
cmake_minimum_required(VERSION 3.5)

 include(./ARGoSCheckQTOpenGL.cmake)
 
add_library(position_functions MODULE
  position_functions.cpp
  position_functions.h)

target_link_libraries(position_functions
  /home/ivan/dev/argos3/build_simulator/core/libargos3core_simulator.so
  /home/ivan/dev/argos3/build_simulator/plugins/simulator/entities/libargos3plugin_simulator_entities.so
  /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so
  /home/ivan/dev/argos3/build_simulator/plugins/simulator/visualizations/qt-opengl/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )
