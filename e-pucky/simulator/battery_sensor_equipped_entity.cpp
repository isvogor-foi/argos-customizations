#include "battery_sensor_equipped_entity.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/composable_entity.h>

namespace argos {


	CBatterySensorEquippedEntity::CBatterySensorEquippedEntity(CComposableEntity* pc_parent) :
		CEntity(pc_parent),
		m_fVoltage(9.0f),
		m_fIdleCurrent(0),
		m_fDriveCurrent(0),
		m_fProcessingLoadCurrent(0)
	{
		Enable();
	}

	CBatterySensorEquippedEntity::CBatterySensorEquippedEntity(CComposableEntity* pc_parent, const std::string& str_id) :
		CEntity(pc_parent, str_id),
		m_fVoltage(9.0f),
		m_fIdleCurrent(0),
		m_fDriveCurrent(0),
		m_fProcessingLoadCurrent(0)
	{
		Enable();
	}

	void CBatterySensorEquippedEntity::Init(TConfigurationNode& t_tree) {
		try {
			CEntity::Init(t_tree);
			//
			// TODO: this should really be moved to a robot, or other entities (e.g. processing entity, energy entity)
			//

			// get init values from XML
			GetNodeAttributeOrDefault(t_tree, "idle_i", m_fIdleCurrent, m_fIdleCurrent);
			GetNodeAttributeOrDefault(t_tree, "drive_i", m_fDriveCurrent, m_fDriveCurrent);
			GetNodeAttributeOrDefault(t_tree, "proc_i", m_fProcessingLoadCurrent, m_fProcessingLoadCurrent);

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
