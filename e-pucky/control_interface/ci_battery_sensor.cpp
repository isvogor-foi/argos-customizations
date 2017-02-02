#include "ci_battery_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif


namespace argos{

	Real CCI_BatterySensor::GetSoc() {
		return m_SOC;
	}

	Real CCI_BatterySensor::GetStartingSoc(){
		return fStartingSoc;
	}


	// lua stuff

	#ifdef ARGOS_WITH_LUA
	   void CCI_BatterySensor::CreateLuaState(lua_State* pt_lua_state) {
	      CLuaUtility::OpenRobotStateTable(pt_lua_state, "battery");
	      CLuaUtility::CloseRobotStateTable(pt_lua_state);
	   }

	   void CCI_BatterySensor::ReadingsToLuaState(lua_State* pt_lua_state) {
	      
	   }
	#endif

}
