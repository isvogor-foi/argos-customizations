#include "ci_trilaser_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#include <stdio.h>
#include <math.h>
#endif


namespace argos{

	CCI_TriLaserSensor::CCI_TriLaserSensor(CCI_EFootBotDistanceScannerActuator* actuator, CCI_EFootBotDistanceScannerSensor* sensor){
		m_Actuator = actuator;
		m_Sensor = sensor;
	}

	void CCI_TriLaserSensor::SetAngle(CRadians angle, int clockwise){
	    float dif = 2; // tolerance
	    double targetAngle = angle.GetValue() * CRadians::RADIANS_TO_DEGREES;
	    double currentAngle = m_Sensor->GetAngle().GetValue() * CRadians::RADIANS_TO_DEGREES;
	    m_Sensor->SetRotationDirection(clockwise);

	    std::cout <<"c: " << currentAngle << ", t: " << targetAngle << std::endl;

	    if(currentAngle - dif < targetAngle && targetAngle < currentAngle + dif){
	    	m_Actuator->SetRPM(0);
	    } else {
	    	m_Actuator->SetRPM(5);
	    }
	}

	// lua stuff
	#ifdef ARGOS_WITH_LUA
	   void CCI_TriLaserSensor::CreateLuaState(lua_State* pt_lua_state) {
	      CLuaUtility::OpenRobotStateTable(pt_lua_state, "trilaser_sensor");
	      CLuaUtility::CloseRobotStateTable(pt_lua_state);
	   }

	   void CCI_TriLaserSensor::ReadingsToLuaState(lua_State* pt_lua_state) {

	   }
	#endif
}
