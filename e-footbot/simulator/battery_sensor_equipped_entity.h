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

		    virtual Real SetIdleCurrent(Real current) {
		    	m_fIdleCurrent = current;
		    }

		    virtual Real GetDriveCurrent() const{
		    	return m_fDriveCurrent;
		    }

		    virtual Real SetDriveCurrent(Real current){
		    	m_fDriveCurrent = current;
		    }

		    virtual Real GetProcessingCurrent() const{
		    	return m_fProcessingLoadCurrent;
		    }

		    virtual Real SetProcessingCurrent(Real current){
		    	m_fProcessingLoadCurrent = current;
		    }

		    virtual Real GetNominalCapacity() const {
		    	return m_fNominalCapacity;
		    }

		    virtual Real GetChargingRate() const {
		    	return m_fChargingRate;
		    }

		    virtual Real GetChargingCurrent() const {
		    	return m_fChargingCurrent;
		    }

		    virtual Real GetEmptyVoltage() const {
		    	return m_fEmptyVoltage;
		    }

		    virtual bool GetRandomizeInitialSOC() const {
		    	return m_bRandomizeInitialSOC;
		    }

		    virtual Real GetJitterPercentageMin() const {
		    	return m_fJitterPercentageMin;
		    }

		    virtual Real GetJitterPercentageMax() const {
		    	return m_fJitterPercentageMax;
		    }

		    virtual Real GetStartingCapacityJitterMin() const {
		    	return m_fJitterStartingCapacityMin;
		    }

		    virtual Real GetStartingCapacityJitterMax() const {
		    	return m_fJitterStartingCapacityMax;
		    }

		    virtual Real GetStartingCapacity() const {
		    	return m_fStartingCapacity;
		    }

		protected:
		    // battery data
		    Real m_fVoltage;			// in V
		    Real m_fEmptyVoltage;		// in V
		    Real m_fNominalCapacity; 	// in Ah
		    Real m_fChargingCurrent;
		    Real m_fChargingRate;		//

		    // battery consumption data, should be moved to a robot
		    Real m_fIdleCurrent;
		    Real m_fProcessingLoadCurrent;
		    Real m_fDriveCurrent;
		    bool m_bRandomizeInitialSOC;
		    Real m_fJitterPercentageMin;
		    Real m_fJitterPercentageMax;
		    Real m_fJitterStartingCapacityMin;
		    Real m_fJitterStartingCapacityMax;
		    Real m_fStartingCapacity;
	}; // end class

} // end namespace

#endif
