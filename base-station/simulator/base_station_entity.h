/**
 * @file <argos3/plugins/robots/e-puck/simulator/base_station_entity.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef BASE_STATION_ENTITY_H
#define BASE_STATION_ENTITY_H

namespace argos {
   class CControllableEntity;
   class CEmbodiedEntity;
   class CEBaseStationEntity;
   class CGroundSensorEquippedEntity;
   class CLEDEquippedEntity;
   class CLightSensorEquippedEntity;
   class CProximitySensorEquippedEntity;
   class CRABEquippedEntity;
}

#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>

namespace argos {

   class CEBaseStationEntity : public CComposableEntity {

   public:

      ENABLE_VTABLE();

   public:

      CEBaseStationEntity();

      CEBaseStationEntity(const std::string& str_id,
                   const std::string& str_controller_id,
                   const CVector3& c_position = CVector3(),
                   const CQuaternion& c_orientation = CQuaternion(),
                   Real f_rab_range = 0.8f,
                   size_t un_rab_data_size = 2);
      
      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void UpdateComponents();
      
      inline CControllableEntity& GetControllableEntity() {
         return *m_pcControllableEntity;
      }

      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CGroundSensorEquippedEntity& GetGroundSensorEquippedEntity() {
         return *m_pcGroundSensorEquippedEntity;
      }

      inline CLEDEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline CLightSensorEquippedEntity& GetLightSensorEquippedEntity() {
         return *m_pcLightSensorEquippedEntity;
      }

      inline CProximitySensorEquippedEntity& GetProximitySensorEquippedEntity() {
         return *m_pcProximitySensorEquippedEntity;
      }

      inline CRABEquippedEntity& GetRABEquippedEntity() {
         return *m_pcRABEquippedEntity;
      }

      inline CWheeledEntity& GetWheeledEntity() {
         return *m_pcWheeledEntity;
      }

      virtual std::string GetTypeDescription() const {
         return "base-station";
      }

   private:

      void SetLEDPosition();

   private:

      CControllableEntity*                   m_pcControllableEntity;
      CEmbodiedEntity*                       m_pcEmbodiedEntity;
      CGroundSensorEquippedEntity*           m_pcGroundSensorEquippedEntity;
      CLEDEquippedEntity*                    m_pcLEDEquippedEntity;
      CLightSensorEquippedEntity*            m_pcLightSensorEquippedEntity;
      CProximitySensorEquippedEntity*        m_pcProximitySensorEquippedEntity;
      CRABEquippedEntity*                    m_pcRABEquippedEntity;
      CWheeledEntity*                        m_pcWheeledEntity;
   };

}

#endif
