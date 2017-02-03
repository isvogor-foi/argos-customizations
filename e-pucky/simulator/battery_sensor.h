#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <string>


namespace argos {
	class CBatterySensor;
	class CBatterySensorEquippedEntity;
	class CWheeledEntity;
}

#include "../control_interface/ci_battery_sensor.h"
#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/space/space.h>
#include "battery_sensor_equipped_entity.h"


namespace argos {

	class CBatterySensor : public CSimulatedSensor,
						   public CCI_BatterySensor {

	public:

	  CBatterySensor();	

      //virtual ~CBatterySensor() {}
      virtual void SetRobot(CComposableEntity& c_entity);
      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();
      virtual void Reset();

    protected:
		CEmbodiedEntity* m_pcEmbodiedEntity; // to who am I associated?
		CBatterySensorEquippedEntity* m_pcBatteryEntity;
	    CControllableEntity* m_pcControllableEntity;
		CSpace& m_cSpace;
		CWheeledEntity* m_pcWheels;

        Real fStartingSoc;
        Real fNominalSoc;

	}; // end CBatterySensor

} // end argos

#endif
