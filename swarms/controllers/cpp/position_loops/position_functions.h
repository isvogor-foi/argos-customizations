#ifndef CROSSROAD_FUNCTIONS_H
#define CROSSROAD_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_render.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_camera.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/utility/logging/argos_log.h>

#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#endif

using namespace argos;

class CPositionFunctions : public CLoopFunctions {

public:

   CPositionFunctions();
   virtual ~CPositionFunctions() {}
   void Init(TConfigurationNode& t_node);
   void Update();
   virtual void PostStep();

private:
	CSimulator* m_Simulator;

	CQTOpenGLRender* m_Renderer;
	CQTOpenGLCamera* m_Camera;
	CQTOpenGLCamera::SSettings* m_CameraSettings;


};

#endif
