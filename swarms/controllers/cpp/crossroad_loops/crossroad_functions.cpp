#include <argos3/core/utility/logging/argos_log.h>
#include "crossroad_functions.h"

/****************************************/
/****************************************/

CCrossroadFunctions::CCrossroadFunctions() {
}

/****************************************/
/****************************************/


void CCrossroadFunctions::Init(TConfigurationNode& t_node) {
   //m_pcFloor = &GetSpace().GetFloorEntity();
}

/****************************************/
/****************************************/

void CCrossroadFunctions::PostStep(){
	ResetPosition();
}

/****************************************/
/****************************************/

void CCrossroadFunctions::ResetPosition(){
	CSpace::TMapPerType& m_cFootbots = GetSpace().GetEntitiesByType("efootbot");

	for(CSpace::TMapPerType::iterator it = m_cFootbots.begin(); it != m_cFootbots.end(); ++it) {
		CEFootBotEntity& cFootBot = *any_cast<CEFootBotEntity*>(it->second);

		CQuaternion qOrientation = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Orientation;
		CVector3 vPosition = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position;

		//std::cout << "Orientation: " << quat.GetX() <<std::endl;

		// check up/down robots
		if(vPosition.GetX() >= 4.7 || vPosition.GetX() <= -4.7){
			vPosition.SetX(vPosition.GetX() - (vPosition.GetX() * 2));
		}
		// check left/right robots
		if(vPosition.GetY()>= 4.7 || vPosition.GetY() <= -4.7){
			vPosition.SetY(vPosition.GetY() - (vPosition.GetY() * 2));
		}

		cFootBot.GetEmbodiedEntity().MoveTo(vPosition, qOrientation, false);
	}
}


REGISTER_LOOP_FUNCTIONS(CCrossroadFunctions, "crossroad_functions")
