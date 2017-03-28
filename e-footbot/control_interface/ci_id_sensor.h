/*
 * ci_id_sensor.h
 *
 *  Created on: 2017-03-27
 *      Author: ivan
 */

#ifndef CI_ID_SENSOR_H_
#define CI_ID_SENSOR_H_

#include<argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>
#include<argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_actuator.h>

#endif /* CI_ID_SENSOR_H_ */

namespace argos {

class CCI_IdSensor {
public:
	#ifdef ARGOS_WITH_LUA
		  virtual void CreateLuaState(lua_State* pt_lua_state);
		  virtual void ReadingsToLuaState(lua_State* pt_lua_state);
	#endif

public:
	CCI_IdSensor(CCI_RangeAndBearingSensor* sensor, CCI_RangeAndBearingActuator* actuator, Real id);
	std::vector<Real> GetData();
private:
	CCI_RangeAndBearingSensor* mRABS;
	CCI_RangeAndBearingActuator* mRABA;
	Real m_id;
	std::vector<Real> readings;
};

}
