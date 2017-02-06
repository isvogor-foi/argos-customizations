/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_proximity_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef EFOOTBOT_PROXIMITY_DEFAULT_SENSOR_H
#define EFOOTBOT_PROXIMITY_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEFootBotProximityDefaultSensor;
}

#include "../control_interface/ci_efootbot_proximity_sensor.h"
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class CEFootBotProximityDefaultSensor : public CCI_EFootBotProximitySensor,
                                          public CSimulatedSensor {

   public:

      CEFootBotProximityDefaultSensor();

      virtual ~CEFootBotProximityDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:

      CProximityDefaultSensor* m_pcProximityImpl;

   };

}

#endif
