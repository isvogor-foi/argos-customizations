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

	class CCI_BatterySensor : public CCI_Sensor {
		public:	
			Real GetSoc() ;
			Real GetStartingSoc();

			void StartCharging();
			void StopCharging();

			void StartProcessing();
			void StopProcessing();

		#ifdef ARGOS_WITH_LUA
		      virtual void CreateLuaState(lua_State* pt_lua_state);
		      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
		#endif

		protected:
			Real m_fSOC;		// 0-1
			Real m_fStartingSoc;

			bool m_bChargingState;
			bool m_bProcessingState;

	};
}


#endif 
