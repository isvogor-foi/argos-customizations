add_library(footbot_diffusion MODULE footbot_diffusion.h footbot_diffusion.cpp)
target_link_libraries(footbot_diffusion
  /usr/local/lib/argos3/libargos3core_simulator.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so 
  /home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/libargos3plugin_simulator_efootbot.so)
