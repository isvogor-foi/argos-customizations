#include "tree_qt_loops.h"

 
TreeQtFunctions::TreeQtFunctions() {
   RegisterUserFunction<TreeQtFunctions,CEFootBotEntity>(&TreeQtFunctions::Draw);
   RegisterUserFunction<TreeQtFunctions,CEBaseStationEntity>(&TreeQtFunctions::Draw);

   m_pcBaseStation = dynamic_cast<CEBaseStationEntity*>(&CSimulator::GetInstance().GetSpace().GetEntity("fb100"));
   m_pcController = &dynamic_cast<CBuzzControllerBaseStation&>(m_pcBaseStation->GetControllableEntity().GetController());

}
 
/****************************************/
/****************************************/
 
void TreeQtFunctions::Draw(CEFootBotEntity& c_entity) {
	std::string message = c_entity.GetId() + ": " + m_pcController->GetDebugMsg();
	DrawText(CVector3(0.0, 0.0, 0.3), message.c_str());

	std::string current_id = c_entity.GetId().substr(2, c_entity.GetId().length());
	CVector3 currentEntityPosition = c_entity.GetEmbodiedEntity().GetOriginAnchor().Position;
	CQuaternion currentEntityOrientation = c_entity.GetEmbodiedEntity().GetOriginAnchor().Orientation.Inverse();
	DrawTree(currentEntityPosition, currentEntityOrientation, current_id);
}

/****************************************/
/****************************************/

void TreeQtFunctions::Draw(CEBaseStationEntity& c_entity) {
	std::string current_id = c_entity.GetId().substr(2, c_entity.GetId().length());
	CVector3 currentEntityPosition = c_entity.GetEmbodiedEntity().GetOriginAnchor().Position;
	CQuaternion currentEntityOrientation = c_entity.GetEmbodiedEntity().GetOriginAnchor().Orientation.Inverse();
	DrawTree(currentEntityPosition, currentEntityOrientation, current_id);
}

/****************************************/
/****************************************/

void TreeQtFunctions::DrawTree(CVector3 currentEntityPosition, CQuaternion currentEntityOrientation, std::string current_id){

	if(m_pcController->m_GeneratedTree != ""){
		std::vector<std::string> result = Split(m_pcController->m_GeneratedTree,';');
		for(int i = 0; i < result.size(); i++){
			std::vector<std::string> current = Split(result[i],'-');
			if(!strcmp(current[0].c_str(), current_id.c_str())){
				std::stringstream sstm;
				sstm << "fb" << current[1];

				CEntity *e = &CSimulator::GetInstance().GetSpace().GetEntity(sstm.str());
				CVector3 pos;

				if(std::atoi(current[1].c_str()) < 100){
					pos = (dynamic_cast<CEFootBotEntity*>(e))->GetEmbodiedEntity().GetOriginAnchor().Position;
				} else {
					pos = (dynamic_cast<CEBaseStationEntity*>(e))->GetEmbodiedEntity().GetOriginAnchor().Position;
				}

				pos -= currentEntityPosition;
				pos.Rotate(currentEntityOrientation);
				pos.SetZ(0.1);

				DrawRay(CRay3(CVector3(0,0,0.1), pos), CColor::BLUE, 4);
			}
		}
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
