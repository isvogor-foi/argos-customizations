#include "battery_sensor_equipped_entity.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/composable_entity.h>

namespace argos {


	CBatterySensorEquippedEntity::CBatterySensorEquippedEntity(CComposableEntity* pc_parent) :
		CEntity(pc_parent) {
	}

	CBatterySensorEquippedEntity::CBatterySensorEquippedEntity(CComposableEntity* pc_parent, const std::string& str_id) :
		CEntity(pc_parent, str_id) {
	}

	//CBatterySensorEquippedEntity::~CBatterySensorEquippedEntity() {}

	void CBatterySensorEquippedEntity::Init(TConfigurationNode& t_tree) {
		try {
			CEntity::Init(t_tree);
		}
		catch(CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Initialization error in battery sensor equipped entity", ex);
		}
	}

	void CBatterySensorEquippedEntity::Reset() {}

	void CBatterySensorEquippedEntity::Update() {}


	REGISTER_STANDARD_SPACE_OPERATIONS_ON_ENTITY(CBatterySensorEquippedEntity);
}