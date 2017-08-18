#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include "position_functions.h"
#include <QImage>


static const Real POV_HEIGHT = 0.2f;

CPositionFunctions::CPositionFunctions(){}

void CPositionFunctions::Init(TConfigurationNode& t_node) {
}

void CPositionFunctions::PostStep(){

	if(GetSimulator().GetSpace().GetSimulationClock() % 10 == 0){
		CSpace::TMapPerType& efootbots = GetSpace().GetEntitiesByType("efootbot");
		for(CSpace::TMapPerType::iterator it = efootbots.begin(); it != efootbots.end(); ++it) {
			CEFootBotEntity& efootbot = *any_cast<CEFootBotEntity*>(it->second);

			std::stringstream x_coord;
			std::stringstream y_coord;
			x_coord << efootbot.GetEmbodiedEntity().GetOriginAnchor().Position.GetX();
			y_coord << efootbot.GetEmbodiedEntity().GetOriginAnchor().Position.GetY();
			//LOG << "Pos: " << x_coord.str() << ", " << y_coord.str();
			LOGERR << "Pos: (" << efootbot.GetId() << "): " << x_coord.str() << " " << y_coord.str() << std::endl;
		}
	}
}


REGISTER_LOOP_FUNCTIONS(CPositionFunctions, "position_functions")
