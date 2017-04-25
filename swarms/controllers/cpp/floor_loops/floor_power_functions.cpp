#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include "floor_power_functions.h"

static const Real POV_HEIGHT = 0.2f;

CFloorPowerFunctions::CFloorPowerFunctions() {
}

/****************************************/
/****************************************/

void CFloorPowerFunctions::Init(TConfigurationNode& t_node) {
    m_pcFloor = &GetSpace().GetFloorEntity();
}

/****************************************/
/****************************************/

void CFloorPowerFunctions::SetPovCamera()
{
    m_Renderer = dynamic_cast<CQTOpenGLRender*>(&GetSimulator().GetVisualization());
    m_Camera = &m_Renderer->GetMainWindow().GetOpenGLWidget().GetCamera();
    m_CameraSettings = &m_Camera->GetActiveSettings();
    m_SelectedEntity = dynamic_cast<CEFootBotEntity*>(m_Renderer->GetMainWindow().GetOpenGLWidget().GetSelectedEntity());

    if(m_SelectedEntity != NULL){
        // get robot position and orientation
        CVector3 pos_vec = m_SelectedEntity->GetEmbodiedEntity().GetOriginAnchor().Position;
        CQuaternion orientation = m_SelectedEntity->GetEmbodiedEntity().GetOriginAnchor().Orientation;

        // get robot angle
        CRadians cZAngle, cYAngle, cXAngle;
        orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

        // calculate camera direction vector
        double x = pos_vec.GetX() + cos(cZAngle.GetValue());
        double y = pos_vec.GetY() + sin(cZAngle.GetValue());
        // fixate X so you don't get tilt
        m_CameraSettings->Up.SetX(0);

        // set position and viewpoint target
        m_CameraSettings->Position.Set((double)(pos_vec.GetX()), (double)(pos_vec.GetY()), POV_HEIGHT);
        m_CameraSettings->Target.Set(x, y, POV_HEIGHT);
    }
}

/****************************************/
/****************************************/

void CFloorPowerFunctions::PostStep(){
	ResetPosition();
    SetPovCamera();

}

/****************************************/
/****************************************/

CColor CFloorPowerFunctions::GetFloorColor(const CVector2& c_position_on_plane) {

	if(c_position_on_plane.GetX() < -1.0f) {
      return CColor::GRAY50;
   }
   return CColor::GRAY20;

}

/****************************************/
/****************************************/

void CFloorPowerFunctions::ResetPosition(){
	CSpace::TMapPerType& m_cFootbots = GetSpace().GetEntitiesByType("efootbot");

	for(CSpace::TMapPerType::iterator it = m_cFootbots.begin(); it != m_cFootbots.end(); ++it) {
		CEFootBotEntity& cFootBot = *any_cast<CEFootBotEntity*>(it->second);

		CQuaternion qOrientation = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Orientation;
		CVector3 vPosition = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position;

		// check up/down robots
		if(vPosition.GetX() >= 7.7 || vPosition.GetX() <= -7.7){ // map edge
			vPosition.SetX(vPosition.GetX() - (vPosition.GetX() * 2));
		}
		// check left/right robots
		if(vPosition.GetY()>= 7.7 || vPosition.GetY() <= -7.7){
			vPosition.SetY(vPosition.GetY() - (vPosition.GetY() * 2));
		}
		cFootBot.GetEmbodiedEntity().MoveTo(vPosition, qOrientation, false);

		std::cout<<"Current floor color: " << m_pcFloor->GetColorAtPoint(vPosition.GetX(), vPosition.GetY());
	}
}


REGISTER_LOOP_FUNCTIONS(CFloorPowerFunctions, "floor_power_functions")
