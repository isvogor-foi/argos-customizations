#ifndef FLOOR_POWER_FUNCTIONS_H
#define FLOOR_POWER_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/simulator/efootbot_entity.h"
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_render.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_camera.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/swarms/controllers/cpp/footbot_diffusion/efootbot_diffusion.h"

using namespace argos;

class CFloorPowerFunctions : public CLoopFunctions {

public:

   CFloorPowerFunctions();
   virtual ~CFloorPowerFunctions() {}
   void Init(TConfigurationNode& t_node);
   void Update();
   virtual void PostStep();
   virtual CColor GetFloorColor(const CVector2& c_position_on_plane);

private:
   	void ResetPosition();
	void SetPovCamera();

	CSimulator* m_Simulator;
	CFloorEntity* m_pcFloor;

	CQTOpenGLRender *m_Renderer;
	CQTOpenGLCamera *m_Camera;
	CQTOpenGLCamera::SSettings *m_CameraSettings;
	CEFootBotEntity *m_SelectedEntity;
	CEFootBotDiffusion* m_pcController;
	CEFootBotEntity* m_pcEFootBot;

};

#endif
