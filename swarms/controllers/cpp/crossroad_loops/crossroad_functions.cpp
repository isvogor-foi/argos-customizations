#include <argos3/core/utility/logging/argos_log.h>
#include "crossroad_functions.h"

/****************************************/
/****************************************/

CCrossroadFunctions::CCrossroadFunctions() {
}

/****************************************/
/****************************************/


void CCrossroadFunctions::Init(TConfigurationNode& t_node) {
   std::cout <<" I shall run this only once... " <<std::endl;
   m_pcFloor = &GetSpace().GetFloorEntity();
   counter = 0;
   //Update();
}
/****************************************/
/****************************************/

void CCrossroadFunctions::Update(){
   CSpace::TMapPerType& m_cFootbots = GetSpace().GetEntitiesByType("efootbot");

   for(CSpace::TMapPerType::iterator it = m_cFootbots.begin(); it != m_cFootbots.end(); ++it) {
	/* Get handle to foot-bot entity and controller */
	CEFootBotEntity& cFootBot = *any_cast<CEFootBotEntity*>(it->second);
	//CFootBotForaging& cController = dynamic_cast<CFootBotForaging&>(cFootBot.GetControllableEntity().GetController());
	/* Count how many foot-bots are in which state */
	//if(! cController.IsResting()) ++unWalkingFBs;
	//else ++unRestingFBs;
	/* Get the position of the foot-bot on the ground as a CVector2 */

	//CEFootBotEntity efb;
	//efb.GetEmbodiedEntity().MoveTo(vec3, quat, false);
	CQuaternion quat = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Orientation;
	CVector3 vec3 = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position;
	vec3.SetX(vec3.GetX() - 1.0f);

	//CVector3 vec3 = CVector3(1.0, 0.0, 0.0);
	//CQuaternion quat = CQuaternion();

	cFootBot.GetEmbodiedEntity().MoveTo(vec3, quat, false);
	//cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position.SetX(0.0f);
	//cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position.SetY(0.0f);


	CVector2 cPos;
	cPos.Set(cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
			 cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position.GetY());
	std::cout << "Pos: " << cPos << std::endl;
   }
}

/****************************************/
/****************************************/

void CCrossroadFunctions::PostStep(){
	if(counter == 70)
		Update();
	counter++;
}


REGISTER_LOOP_FUNCTIONS(CCrossroadFunctions, "crossroad_functions")
