/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_proximity_default_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>

#include "efootbot_proximity_default_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   class CProximitySensorImpl : public CProximityDefaultSensor {

   public:

      virtual Real CalculateReading(Real f_distance) {
         if(f_distance < 0.009889556) {
            return 1.0;
         }
         else {
            return 0.0100527 / (f_distance + 0.000163144);
         }
      }

   };

   /****************************************/
   /****************************************/

   CEFootBotProximityDefaultSensor::CEFootBotProximityDefaultSensor() :
      m_pcProximityImpl(new CProximitySensorImpl()) {}

   /****************************************/
   /****************************************/

   CEFootBotProximityDefaultSensor::~CEFootBotProximityDefaultSensor() {
      delete m_pcProximityImpl;
   }

   /****************************************/
   /****************************************/

   void CEFootBotProximityDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      try {
         m_pcProximityImpl->SetRobot(c_entity);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the foot-bot proximity default sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEFootBotProximityDefaultSensor::Init(TConfigurationNode& t_tree) {
      m_pcProximityImpl->Init(t_tree);
   }

   /****************************************/
   /****************************************/

   void CEFootBotProximityDefaultSensor::Update() {
      m_pcProximityImpl->Update();
      for(size_t i = 0; i < 24; ++i) {
         m_tReadings[i].Value = m_pcProximityImpl->GetReadings()[i];
      }
   }

   /****************************************/
   /****************************************/

   void CEFootBotProximityDefaultSensor::Reset() {
      m_pcProximityImpl->Reset();
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEFootBotProximityDefaultSensor,
                   "efootbot_proximity", "default",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The foot-bot proximity sensor.",
                   "This sensor accesses the foot-bot proximity sensor. For a complete description\n"
                   "of its usage, refer to the ci_efootbot_proximity_sensor.h interface. For the XML\n"
                   "configuration, refer to the default proximity sensor.\n",
                   "Usable"
		  );

}
