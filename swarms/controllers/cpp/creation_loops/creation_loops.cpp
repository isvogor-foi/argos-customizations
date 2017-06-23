#include "creation_loops.h"

/****************************************/
/****************************************/
 
CreationLoops::CreationLoops(){}

/****************************************/
/****************************************/

void CreationLoops::Init(TConfigurationNode& t_tree) {
	//GetSimulator().GetVisualization();
	AddRobot();
}

void CreationLoops::AddRobot(){
	// data packet size needs to be the same for all robots!
	CEFootBotEntity* fb = new CEFootBotEntity("fb88", "bcf", CVector3(0, 1, 0), CQuaternion(0,0,0,0), 3, 1000);
	AddEntity(*fb);
}


REGISTER_LOOP_FUNCTIONS(CreationLoops, "creation_functions")
