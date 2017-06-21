#include "tree_qt_loops.h"

 
TreeQtFunctions::TreeQtFunctions() {
   //RegisterUserFunction<TreeQtFunctions,CEFootBotEntity>(&TreeQtFunctions::Draw);
   //RegisterUserFunction<TreeQtFunctions,CEBaseStationEntity>(&TreeQtFunctions::Draw);

   m_pcBaseStation = dynamic_cast<CEBaseStationEntity*>(&CSimulator::GetInstance().GetSpace().GetEntity("fb100"));
   m_pcController = &dynamic_cast<CBuzzControllerBaseStation&>(m_pcBaseStation->GetControllableEntity().GetController());
   //m_pcMainWindow = GetMainWindow();

}
 

void TreeQtFunctions::DrawInWorld() {
	std::vector<std::string> result = Split(m_pcController->m_GeneratedTree,';');
	for(int i = 0; i < result.size(); i++){
		std::vector<std::string> current = Split(result[i],'-');
		std::stringstream strR1;
		strR1 << "fb" << current[0];

		std::stringstream strR2;
		strR2 << "fb" << current[1];

		CEntity *robot1 = &CSimulator::GetInstance().GetSpace().GetEntity(strR1.str());
		CEntity *robot2 = &CSimulator::GetInstance().GetSpace().GetEntity(strR2.str());

		CVector3 posRobot1;
		CVector3 posRobot2;

		if(std::atoi(current[0].c_str()) < 100){
			posRobot1 = (dynamic_cast<CEFootBotEntity*>(robot1))->GetEmbodiedEntity().GetOriginAnchor().Position;
		} else {
			posRobot1 = (dynamic_cast<CEBaseStationEntity*>(robot1))->GetEmbodiedEntity().GetOriginAnchor().Position;
		}

		if(std::atoi(current[1].c_str()) < 100){
			posRobot2 = (dynamic_cast<CEFootBotEntity*>(robot2))->GetEmbodiedEntity().GetOriginAnchor().Position;
		} else {
			posRobot2 = (dynamic_cast<CEBaseStationEntity*>(robot2))->GetEmbodiedEntity().GetOriginAnchor().Position;
		}

		posRobot1.SetZ(0.2);
		posRobot2.SetZ(0.2);

		DrawRay(CRay3(posRobot1, posRobot2), CColor::BLUE, 3);
	}
}



/****************************************/
/****************************************/

std::vector<std::string> TreeQtFunctions::Split(std::string str, char delimiter) {
  std::vector<std::string> internal;
  std::stringstream ss(str); // Turn the string into a stream.
  std::string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}
 
/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(TreeQtFunctions, "tree_loop_functions")
