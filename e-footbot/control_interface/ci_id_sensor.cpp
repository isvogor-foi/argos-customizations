#include "ci_id_sensor.h"
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#include <stdio.h>
#include <math.h>

#endif


namespace argos{

	CCI_IdSensor::CCI_IdSensor(CCI_RangeAndBearingSensor* sensor, CCI_RangeAndBearingActuator* actuator, Real id){
		mRABS = sensor;
		mRABA = actuator;
		m_id = id;
	}

	// todo: reading frequency
	std::vector<Real> CCI_IdSensor::GetData(){
		// send your ID to other robots in 0-th position of a data package
		mRABA->ClearData();
	    mRABA->SetData(0, m_id);
	    double gap = 2.5f; // gap in degrees

	    // initialize empty array; -1 = empty
	    std::vector<Real> sensor_array(12, -1);
		CCI_RangeAndBearingSensor::TReadings data = mRABS->GetReadings();
		for(int i = 0; i < data.size(); i++){
			// values are -180 ~ +180, we need 0-360
			double angle = data[i].HorizontalBearing.GetValue() * CRadians::RADIANS_TO_DEGREES;
			if(angle < 0){
				angle = 360 + angle;
			}
			int pos = fmod(round(angle / 30), 12.0f);
			int sensor_angle = pos * 30;
			// std::cout << m_id << " I see: " << data[i].Data[0] << " at: " << angle << " --> " << pos << ", " << sensor_angle <<std::endl;
			// if robot is not in the gap, add it to array; todo: currently one robot per sensor?
			if(sensor_angle - 15 + gap < angle && angle < sensor_angle + 15 - gap){
				sensor_array[pos] = data[i].Data[0];
			}
		}
		return sensor_array;
	}

	// lua stuff
	#ifdef ARGOS_WITH_LUA
	   void CCI_IdSensor::CreateLuaState(lua_State* pt_lua_state) {
	      CLuaUtility::OpenRobotStateTable(pt_lua_state, "id_sensor");
	      CLuaUtility::CloseRobotStateTable(pt_lua_state);
	   }

	   void CCI_IdSensor::ReadingsToLuaState(lua_State* pt_lua_state) {

	   }
	#endif
}
