#include "tree_qt_loops.h"

 
TreeQtFunctions::TreeQtFunctions(){
   RegisterUserFunction<TreeQtFunctions,CEFootBotEntity>(&TreeQtFunctions::Draw);
   RegisterUserFunction<TreeQtFunctions,CEBaseStationEntity>(&TreeQtFunctions::Draw);

   m_treeDrawn = false;
   menuDrawn = false;

   m_pcBaseStation = dynamic_cast<CEBaseStationEntity*>(&CSimulator::GetInstance().GetSpace().GetEntity("fb100"));
   m_pcController = &dynamic_cast<CBuzzControllerBaseStation&>(m_pcBaseStation->GetControllableEntity().GetController());
   m_pcRNG = CRandom::CreateRNG("argos");

   if(&GetMainWindow() != NULL){
	   CQTOpenGLWidget* mw = &GetMainWindow().GetOpenGLWidget();
	   std::cout<< "OK!!!!!!!!!!!!!!"<< GetMainWindow().getMyBool() <<std::endl;


   } else {
	   std::cout<< "NUL!!!!!!!!!!!!!!!"<<std::endl;
   }

}

void TreeQtFunctions::DrawInWorld() {

	  if(&GetMainWindow() != NULL){
		   CQTOpenGLWidget* mw = &GetMainWindow().GetOpenGLWidget();
		   mw->SelectEntity(m_pcBaseStation->GetEmbodiedEntity());
		   std::cout<< "OK!!!!!!!!!!!!!!"<< GetMainWindow().getMyBool() <<std::endl;

	   } else {
		   std::cout<< "NUL!!!!!!!!!!!!!!!"<<std::endl;
	   }

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
	std::string message = c_entity.GetId() + ": " + m_pcController->GetDebugMsg();
	DrawText(CVector3(0.0, 0.0, 0.3), message.c_str());
}

/****************************************/
/****************************************/

void TreeQtFunctions::Draw(CEBaseStationEntity& c_entity) {
	std::string message = c_entity.GetId() + ": " + m_pcController->GetDebugMsg();
	DrawText(CVector3(0.0, 0.0, 0.3), message.c_str());
}

/****************************************/
/****************************************/

void TreeQtFunctions::KeyPressed(QKeyEvent* pc_event){
	std::stringstream name;
	name << "fb" << GetRandomInteger(11, 99, m_pcRNG);
	CEFootBotEntity* fb = new CEFootBotEntity(name.str(), "bcf", CVector3(GetRandomInteger(0, 100, m_pcRNG) / 100.0f, GetRandomInteger(0, 100, m_pcRNG) / 100.0f, 0), CQuaternion(0,0,0,0), 3, 1000);
	AddEntity(*fb);
}

/****************************************/
/****************************************/

void TreeQtFunctions::DrawOverlay(QPainter& c_painter){
/*
     QStyleOptionButton opt;
     opt.state = QStyle::State_Active | QStyle::State_Enabled;
     opt.rect = QRect(20, 20, 100, 25);
     textBox->setPlaceholderText("Placeholder Text");
     textBox->style()->drawControl(QStyle::CE_PushButton, &opt, &c_painter);
     */
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

int TreeQtFunctions::GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG){
	CRange < UInt32 > cRange(min, max);
	int random = pcRNG->Uniform(cRange);
	return random;
}

/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(TreeQtFunctions, "tree_loop_functions")
