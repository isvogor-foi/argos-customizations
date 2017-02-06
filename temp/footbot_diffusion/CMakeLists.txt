add_library(efootbot_diffusion MODULE efootbot_diffusion.h efootbot_diffusion.cpp)
target_link_libraries(efootbot_diffusion
  /usr/local/lib/argos3/libargos3core_simulator.so
  /usr/local/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so)
