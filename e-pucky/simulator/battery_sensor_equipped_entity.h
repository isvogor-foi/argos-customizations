#ifndef BATTERY_SENSOR_EQUIPPED_ENTITY_H
#define BATTERY_SENSOR_EQUIPPED_ENTITY_H

namespace argos {
	//class CBatterySensor;
	class CBatterySensorEquippedEntity;
}

#include <argos3/core/simulator/entity/entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>

namespace argos {
	class CBatterySensorEquippedEntity : public CEntity {

		public:

			ENABLE_VTABLE();

			CBatterySensorEquippedEntity(CComposableEntity* pc_parent);
      		CBatterySensorEquippedEntity(CComposableEntity* pc_parent, const std::string& str_id);

      		virtual void Reset();
      		virtual void Update();

			virtual void Init(TConfigurationNode& t_node);
		    virtual std::string GetTypeDescription() const {
		    	return "battery";
		    }

		public:
		    Real m_fVoltage;
		    Real m_fCurrent;


	}; // end class
} // end namespace

#endif
