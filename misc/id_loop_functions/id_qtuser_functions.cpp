#include "id_qtuser_functions.h"

/****************************************/
/****************************************/

CIDQTUserFunctions::CIDQTUserFunctions() {
   RegisterUserFunction<CIDQTUserFunctions,CEFootBotEntity>(&CIDQTUserFunctions::Draw);
}

/****************************************/
/****************************************/

void CIDQTUserFunctions::Draw(CEFootBotEntity& c_entity) {
   DrawText(CVector3(0.0, 0.0, 0.3),   // position
            c_entity.GetId().c_str()); // text
}
/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(CIDQTUserFunctions, "id_qtuser_functions2")
