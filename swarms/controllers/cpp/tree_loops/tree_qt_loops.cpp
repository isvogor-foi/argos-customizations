#include "tree_qt_loops.h"

 
TreeQtFunctions::TreeQtFunctions(){
   RegisterUserFunction<TreeQtFunctions,CEFootBotEntity>(&TreeQtFunctions::Draw);
   RegisterUserFunction<TreeQtFunctions,CEBaseStationEntity>(&TreeQtFunctions::Draw);

   SetFbControllerName("bcf");
   SetBsControllerName("bsf");

   m_treeDrawn = false;
   menuDrawn = false;

   m_pcBaseStation = dynamic_cast<CEBaseStationEntity*>(&CSimulator::GetInstance().GetSpace().GetEntity("fb100"));
   m_pcController = &dynamic_cast<CBuzzControllerBaseStation&>(m_pcBaseStation->GetControllableEntity().GetController());

   m_pcRNG = CRandom::CreateRNG("argos");
}

void TreeQtFunctions::DrawInWorld() {
	// todo: return multiple trees
	// todo: play around with graph partitions
	// todo: add a buzz function to remove robots
	// todo: draw a sea surface for Li
	std::vector<std::string> result = Split(m_pcController->m_GeneratedTree,';');
	if(m_treeDrawn){
		for(std::vector<Edge>::size_type i = 0; i != treeEdges.size(); i++) {
			DrawRay(CRay3(treeEdges[i].m_nodeStart, treeEdges[i].m_nodeEnd), CColor::BLUE, 3);
		}
	} else {
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

		posRobot1.SetZ(0.1);
		posRobot2.SetZ(0.1);

		treeEdges.push_back(Edge(posRobot1, posRobot2));
		m_treeDrawn = true;
		}
	}
}

/****************************************/
/****************************************/

void TreeQtFunctions::Draw(CEFootBotEntity& c_entity) {
	CBuzzControllerEFootBot *controller = &dynamic_cast<CBuzzControllerEFootBot&>(c_entity.GetControllableEntity().GetController());
	std::string message = c_entity.GetId() + ": " + controller->GetDebugMsg();
	DrawText(CVector3(0.0, 0.0, 0.3), message.c_str());
	DrawRay(CRay3(CVector3(0,0,0.1), CVector3(0.14,0,0.1)), CColor::YELLOW, 2);
}

/****************************************/
/****************************************/


void TreeQtFunctions::Draw(CEBaseStationEntity& c_entity) {
	CBuzzControllerBaseStation *controller = &dynamic_cast<CBuzzControllerBaseStation&>(c_entity.GetControllableEntity().GetController());
	std::string message = c_entity.GetId() + ": " + controller->GetDebugMsg();
	DrawText(CVector3(0.0, 0.0, 0.3), message.c_str());
	DrawRay(CRay3(CVector3(0,0,0.1), CVector3(0.14,0,0.1)), CColor::YELLOW, 2);
}


/****************************************/
/****************************************/

void TreeQtFunctions::KeyPressed(QKeyEvent* pc_event){ }

/****************************************/
/****************************************/

void TreeQtFunctions::DrawOverlay(QPainter& c_painter){ }


/****************************************/
/****************************************/

//std::string TreeQtFunctions::GetControllerName(){
//	return "bcf";
//}

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

int TreeQtFunctions::GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG){
	CRange < UInt32 > cRange(min, max);
	int random = pcRNG->Uniform(cRange);
	return random;
}

/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(TreeQtFunctions, "tree_loop_functions")
