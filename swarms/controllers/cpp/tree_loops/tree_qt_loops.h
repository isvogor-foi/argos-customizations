#ifndef TREE_QT_FUNCTIONS_H
#define TREE_QT_FUNCTIONS_H

//#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/base-station/simulator/base_station_entity.h"
#include "/home/ivan/dev/buzz-ext/buzz/src/buzz/argos/buzz_controller_base_station.h"
#include <argos3/core/simulator/simulator.h>
#include <vector>
#include <string>
#include <sstream>

using namespace argos;
 
class TreeQtFunctions : public CQTOpenGLUserFunctions {
 
public:
 
   TreeQtFunctions();
 
   virtual ~TreeQtFunctions() {}
 
   void Draw(CEFootBotEntity& c_entity);

   void Draw(CEBaseStationEntity& c_entity);

private:
   std::vector<std::string> Split(std::string str, char delimiter);
   void DrawTree(CVector3 currentEntityPosition, CQuaternion currentEntityOrientation, std::string current_id);

   CBuzzControllerBaseStation* m_pcController;
   CEBaseStationEntity* m_pcBaseStation;
   CEFootBotEntity* m_pcFb;


};
 
#endif
