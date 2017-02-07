PROJECT(footbot_controller)
cmake_minimum_required(VERSION 3.5)

add_library(efootbot_diffusion MODULE efootbot_diffusion.h efootbot_diffusion.cpp)
target_link_libraries(efootbot_diffusion
  /usr/local/lib/argos3/libargos3core_simulator.so
  /usr/local/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
  /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so)
