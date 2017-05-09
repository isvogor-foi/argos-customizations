PROJECT(charging_station)
cmake_minimum_required(VERSION 3.5)

 include(./ARGoSCheckQTOpenGL.cmake)
 
add_library(crossroad_loop_footbot MODULE
  crossroad_loop_footbot.h
  crossroad_loop_footbot.cpp)

target_link_libraries(crossroad_loop_footbot
  /home/ivan/dev/argos3/core/libargos3core_simulator.so
  /home/ivan/dev/argos3/plugins/simulator/entities/libargos3plugin_simulator_entities.so
  /home/ivan/dev/argos3/plugins/robots/foot-bot/libargos3plugin_simulator_footbot.so
  /home/ivan/dev/argos3/plugins/simulator/visualizations/qt-opengl/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )
