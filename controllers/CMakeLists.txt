add_library(base_station_controller MODULE base_station_obstacleavoidance.h base_station_obstacleavoidance.cpp)
target_link_libraries(base_station_controller
  /usr/local/lib/argos3/libargos3core_simulator.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
  /home/ivan/dev/argos-custom/argos3/plugins/robots/base-station/libargos3plugin_simulator_base_station.so)
