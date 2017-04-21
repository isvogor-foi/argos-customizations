#ifndef CROSSROAD_FUNCTIONS_H
#define CROSSROAD_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_render.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_camera.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
using namespace argos;

class CCrossroadFunctions : public CLoopFunctions {

public:

   CCrossroadFunctions();
   virtual ~CCrossroadFunctions() {}
   void Init(TConfigurationNode& t_node);
   void Update();
   virtual void PostStep();

private:
   	void ResetPosition();
	void SetPovCamera();

	CSimulator* m_Simulator;

	CQTOpenGLRender *m_Renderer;
	CQTOpenGLCamera *m_Camera;
	CQTOpenGLCamera::SSettings *m_CameraSettings;
	CEFootBotEntity *m_SelectedEntity;
};

#endif
