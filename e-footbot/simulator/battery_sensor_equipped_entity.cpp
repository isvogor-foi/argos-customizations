#include "battery_sensor_equipped_entity.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/composable_entity.h>

namespace argos {


	CBatterySensorEquippedEntity::CBatterySensorEquippedEntity(CComposableEntity* pc_parent) :
		CEntity(pc_parent),
		m_fVoltage(4.2f),
		m_fEmptyVoltage(2.7f),
		m_fIdleCurrent(0),
		m_fDriveCurrent(0),
		m_fJitterPercentageMin(0),
		m_fJitterPercentageMax(0),
		m_fProcessingLoadCurrent(0)
	{
		Enable();
	}

	CBatterySensorEquippedEntity::CBatterySensorEquippedEntity(CComposableEntity* pc_parent, const std::string& str_id) :
		CEntity(pc_parent, str_id),
		m_fVoltage(4.2f),
		m_fEmptyVoltage(2.7f),
		m_fIdleCurrent(0),
		m_fDriveCurrent(0),
		m_fProcessingLoadCurrent(0)
	{
		Enable();
	}

	void CBatterySensorEquippedEntity::Init(TConfigurationNode& t_tree) {
		try {
			CEntity::Init(t_tree);

			// get battery info
			GetNodeAttributeOrDefault(t_tree, "nominal_capacity", m_fNominalCapacity, m_fNominalCapacity);
			GetNodeAttributeOrDefault(t_tree, "nominal_voltage", m_fVoltage, m_fVoltage);
			GetNodeAttributeOrDefault(t_tree, "empty_voltage", m_fEmptyVoltage, m_fEmptyVoltage);

			// get power consumption info (this should be moved to a robot)
			GetNodeAttributeOrDefault(t_tree, "idle_i", m_fIdleCurrent, m_fIdleCurrent);
			GetNodeAttributeOrDefault(t_tree, "drive_i", m_fDriveCurrent, m_fDriveCurrent);
			GetNodeAttributeOrDefault(t_tree, "proc_i", m_fProcessingLoadCurrent, m_fProcessingLoadCurrent);
			GetNodeAttributeOrDefault(t_tree, "c_rating", m_fCRate, m_fCRate);
			GetNodeAttributeOrDefault(t_tree, "randomize_soc", m_bRandomizeInitialSOC, m_bRandomizeInitialSOC);
			GetNodeAttributeOrDefault(t_tree, "jitter_percentage_min", m_fJitterPercentageMin, m_fJitterPercentageMin);
			GetNodeAttributeOrDefault(t_tree, "jitter_percentage_max", m_fJitterPercentageMax, m_fJitterPercentageMax);

		}
		catch(CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Initialization error in battery sensor equipped entity", ex);
		}
	}

	void CBatterySensorEquippedEntity::Reset() {}

	void CBatterySensorEquippedEntity::Update() {
	}


	REGISTER_STANDARD_SPACE_OPERATIONS_ON_ENTITY(CBatterySensorEquippedEntity);
}
