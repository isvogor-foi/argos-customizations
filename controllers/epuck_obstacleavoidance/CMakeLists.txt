add_library(epuck_obstacleavoidance MODULE epuck_obstacleavoidance.h epuck_obstacleavoidance.cpp)
target_link_libraries(epuck_obstacleavoidance
  #argos3core_simulator
  #argos3plugin_simulator_epuck
  #argos3plugin_simulator_genericrobot)
  /usr/local/lib/argos3/libargos3core_simulator.so
  #/usr/local/lib/argos3/libargos3plugin_simulator_epucky.so
  /home/ivan/dev/argos-custom/argos3/plugins/robots/e-pucky/libargos3plugin_simulator_epucky.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so)