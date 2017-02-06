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
		    	return m_fVoltage; //
		    }

		    virtual Real GetIdleCurrent() const{
		    	return m_fIdleCurrent;
		    }

		    virtual Real GetDriveCurrent() const{
		    	return m_fDriveCurrent;
		    }

		    virtual Real GetProcessingCurrent() const{
		    	return m_fProcessingLoadCurrent;
		    }

		    virtual Real GetNominalCapacity() const {
		    	return m_fNominalCapacity;
		    }

		protected:
		    // battery data
		    Real m_fVoltage;
		    Real m_fNominalCapacity;
		    Real m_fCRate;

		    // battery consumption data, should be moved to a robot
		    Real m_fIdleCurrent;
		    Real m_fProcessingLoadCurrent;
		    Real m_fDriveCurrent;

		    // TODO: add C rating



	}; // end class

} // end namespace

#endif
