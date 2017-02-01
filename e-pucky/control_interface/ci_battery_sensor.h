/**
 * Sensor control interface (CI) is used to access sensor reading from the Controller.
 */

#ifndef CCI_BATTERY_SENSOR_H
#define CCI_BATTERY_SENSOR_H

namespace argos {
	class CCI_BatterySensor;
}

// generic control interface
#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/rng.h>

namespace argos {

	class CCI_BatterySensor : public CCI_Sensor{
		public:	
			//virtual ~CCI_BatterySensor() {}

			Real GetReadings() ;

		#ifdef ARGOS_WITH_LUA
		      virtual void CreateLuaState(lua_State* pt_lua_state);
		      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
		#endif

		protected:
			Real m_Readings;

	};
}


#endif 
