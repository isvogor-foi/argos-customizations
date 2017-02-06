#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <string>


namespace argos {
	class CBatterySensor;
	class CBatterySensorEquippedEntity;
	class CWheeledEntity;
}

#include "../control_interface/ci_battery_sensor.h"
#include "spline.h"
#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/space/space.h>
#include "battery_sensor_equipped_entity.h"


namespace argos {

	class CBatterySensor : public CSimulatedSensor,
						   public CCI_BatterySensor {

	public:

	  CBatterySensor();	

	  // TODO: Fix destructors (i.e. implement them)
      //virtual ~CBatterySensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);
      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();
      virtual void Reset();

    protected:
		CEmbodiedEntity* m_pcEmbodiedEntity; 			// to who am I associated?
		CBatterySensorEquippedEntity* m_pcBatteryEntity;
	    CControllableEntity* m_pcControllableEntity;
		CWheeledEntity* m_pcWheels;						// get wheels for velocity
		CSpace& m_cSpace;

        Real fStartingSoc;
        Real fConsumedCapacity;

    private:
        tk::spline splineFunction;
        std::string m_sDischargeType;

	}; // end CBatterySensor

} // end argos

#endif
