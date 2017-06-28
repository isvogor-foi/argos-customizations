PROJECT(charging_station)
cmake_minimum_required(VERSION 3.5)

include(./ARGoSCheckQTOpenGL.cmake)
LINK_DIRECTORIES(/usr/local/lib/argos3/)

add_library(tree_loops MODULE 
  tree_qt_loops.h
  tree_qt_loops.cpp)


target_link_libraries(tree_loops
  argos3core_simulator
  argos3plugin_simulator_entities
  /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so
  /home/ivan/dev/argos-custom/argos3/plugins/simulator/visualizations/qt-mod/build/libargos3plugin_mod_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})


