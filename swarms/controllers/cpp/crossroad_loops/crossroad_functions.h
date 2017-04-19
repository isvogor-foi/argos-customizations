#ifndef CROSSROAD_FUNCTIONS_H
#define CROSSROAD_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"
using namespace argos;

class CCrossroadFunctions : public CLoopFunctions {

public:

   CCrossroadFunctions();
   virtual ~CCrossroadFunctions() {}
   void Init(TConfigurationNode& t_node);
   void Update();
   void ResetPosition();
   virtual void PostStep();

private:
   // CFloorEntity* m_pcFloor;
   // int counter;
};

#endif
