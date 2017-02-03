#include "battery_sensor.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>

namespace argos {

	CBatterySensor::CBatterySensor() :
		//m_pcRNG(NULL),
		m_pcBatteryEntity(NULL),
		m_pcEmbodiedEntity(NULL),
        fStartingSoc(0),
        fNominalSoc(0),
		m_cSpace(CSimulator::GetInstance().GetSpace())
	{ }

	void CBatterySensor::SetRobot(CComposableEntity& c_entity) {
	  try {
		m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
		m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity> ("controller"));
		m_pcBatteryEntity = &(c_entity.GetComponent<CBatterySensorEquippedEntity>("battery"));
		m_pcWheels = &(c_entity.GetComponent<CWheeledEntity>("wheels"));
	   }
	  catch(CARGoSException& ex) {
		 THROW_ARGOSEXCEPTION_NESTED("Error setting differential steering actuator to entity \"" << c_entity.GetId() << "\"", ex);
	  }

        //
	}

	void CBatterySensor::Init(TConfigurationNode& t_tree) {
		try {
			CCI_BatterySensor::Init(t_tree);
			//m_pcRNG = CRandom::CreateRNG("argos");
			m_SOC = 0;
			// read XML attributes
	         GetNodeAttributeOrDefault(t_tree, "starting_soc", fStartingSoc, fStartingSoc);
	         GetNodeAttributeOrDefault(t_tree, "nominal_soc", fNominalSoc, fNominalSoc);

		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Initialization error in default battery sensor", ex);
		}
	}

	void CBatterySensor::Update() {
		//if(m_)
		//CRange < UInt32 > cRange(0.5f, 12.0f);
		//m_Readings = m_pcRNG->Uniform(cRange);
		//m_Readings = m_pcWheeledEntity->GetWheelVelocity(0);
		//fStartingSoc += CPhysicsEngine::GetSimulationClockTick();
		//m_pcBatteryEntity->Update();

		m_SOC = m_SOC + ( (m_pcBatteryEntity->GetIdleCurrent()) / fNominalSoc) * CPhysicsEngine::GetSimulationClockTick();
		m_SOC = m_pcWheels->GetWheelVelocity(0); // you must have a reference to _entities.so in the CMake file
		//m_SOC = m_pcBatteryEntity->GetCurrent();
		//m_SOC = 5.0f;
		//m_pcBatteryEntity->Update()
	}

	void CBatterySensor::Reset() { }

	REGISTER_SENSOR(CBatterySensor,
			"battery", "default",
			"Ivan Svogor",
			"0.1",
			"An early version of a battery sensor.",
			"TODO"
			"TODO",
			"Under development"
	);

} // end namespace
