/*
 * ci_id_sensor.h
 *
 *  Created on: 2017-04-02
 *      Author: ivan
 */

#ifndef CI_TRILASER_SENSOR_H_
#include "ci_efootbot_distance_scanner_sensor.h"
#include "ci_efootbot_distance_scanner_actuator.h"
#include <argos3/core/utility/math/angles.h>
#define CI_TRILASER_SENSOR_H_

#endif /* CI_TRILASER_SENSOR_H_ */

namespace argos {

class CCI_TriLaserSensor {
public:
	#ifdef ARGOS_WITH_LUA
		  virtual void CreateLuaState(lua_State* pt_lua_state);
		  virtual void ReadingsToLuaState(lua_State* pt_lua_state);
	#endif
public:
    CCI_TriLaserSensor(CCI_EFootBotDistanceScannerActuator* actuator, CCI_EFootBotDistanceScannerSensor* sensor);
    bool SetAngle(CRadians angle, int clockwise);
private:

    CCI_EFootBotDistanceScannerActuator* m_Actuator;
    CCI_EFootBotDistanceScannerSensor* m_Sensor;

};

}
