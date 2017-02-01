#include "battery_sensor.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include "battery_sensor_equipped_entity.h"

namespace argos {

	CBatterySensor::CBatterySensor() :
		m_pcRNG(NULL),
		m_pcBatteryEntity(NULL),
		//m_Readings(1.0f),
		m_cSpace(CSimulator::GetInstance().GetSpace())
	{ }

	void CBatterySensor::SetRobot(CComposableEntity& c_entity) {
		//m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
		m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity> ("controller"));
		m_pcBatteryEntity = &(c_entity.GetComponent<CBatterySensorEquippedEntity> ("battery"));
	}

	void CBatterySensor::Init(TConfigurationNode& t_tree) {
		try {
			CCI_BatterySensor::Init(t_tree);
			m_pcRNG = CRandom::CreateRNG("argos");
		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Initialization error in default battery sensor", ex);
		}
	}

	void CBatterySensor::Update() {
		CRange < UInt32 > cRange(0.5f, 12.0f);
		m_Readings = m_pcRNG->Uniform(cRange);
	}

	void CBatterySensor::Reset() { }

	REGISTER_SENSOR(CBatterySensor,
			"battery", "default",
			"Ivan Svogor",
			"0.1",
			"TODO",
			"TODO"
			"TODO",
			"Under development"
	)
	;

} // end namespace
