#ifndef ID_QTUSER_FUNCTIONS_H
#define ID_QTUSER_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
//#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"

using namespace argos;

class CIDQTUserFunctions : public CQTOpenGLUserFunctions {

public:

   CIDQTUserFunctions();

   virtual ~CIDQTUserFunctions() {}

   void Draw(CEFootBotEntity& c_entity);
   
};

#endif
