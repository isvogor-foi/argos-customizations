#ifndef BATTERY_SENSOR_EQUIPPED_ENTITY_H
#define BATTERY_SENSOR_EQUIPPED_ENTITY_H

namespace argos {
	//class CBatterySensor;
	class CBatterySensorEquippedEntity;
}

#include <argos3/core/simulator/entity/entity.h>

namespace argos {
	class CBatterySensorEquippedEntity : public CEntity {

		public:

			ENABLE_VTABLE();

			CBatterySensorEquippedEntity(CComposableEntity* pc_parent);
      		CBatterySensorEquippedEntity(CComposableEntity* pc_parent, const std::string& str_id);


      		virtual void Reset();
      		virtual void Update();

			virtual void Init(TConfigurationNode& t_node);

			// getters

		    virtual std::string GetTypeDescription() const {
		    	return "battery";
		    }

		    virtual Real GetVoltage() const {
		    	return m_fVoltage / 36000; //
		    }

		    virtual Real GetIdleCurrent() const{
		    	return m_fIdleCurrent / 36000;
		    }

		    virtual Real GetDriveCurrent() const{
		    	return m_fDriveCurrent / 36000;
		    }

		    virtual Real GetProcessingCurrent() const{
		    	return m_fProcessingLoadCurrent / 36000;
		    }

		    Real m_fDriveCurrent;


		protected:
		    Real m_fVoltage;


		    Real m_fIdleCurrent;
		    Real m_fProcessingLoadCurrent;

	}; // end class
} // end namespace

#endif
