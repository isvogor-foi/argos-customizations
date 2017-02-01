#include "battery_sensor.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include "battery_sensor_equipped_entity.h"

namespace argos {

	CBatterySensor::CBatterySensor() :
		m_pcBatteryEntity(NULL),
    m_capacity(1.0f),
    m_cSpace(CSimulator::GetInstance().GetSpace()) 
	{ }

	void CBatterySensor::SetRobot(CComposableEntity& c_entity) { 
    //m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
    m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
    m_pcBatteryEntity = &(c_entity.GetComponent<CBatterySensorEquippedEntity>("battery"));
  }

	void CBatterySensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_BatterySensor::Init(t_tree);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in default battery sensor", ex);
      }
	}

	void CBatterySensor::Update() {
	   m_capacity = 0.0f;
	}

	void CBatterySensor::Reset() {
		  m_capacity = 100.0f;
	}

  REGISTER_SENSOR(CBatterySensor,
               "battery", "default",
               "Ivan",
               "1.0",
               "The foot-bot turret encoder sensor.",
               "This sensor accesses the foot-bot turret encoder. For a complete\n"
               "None for the time being.\n",
               "Under development"
  );

} // end namespace