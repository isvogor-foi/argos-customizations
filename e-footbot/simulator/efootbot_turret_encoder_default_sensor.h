/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_turret_encoder_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef EFOOTBOT_TURRET_ENCODER_DEFAULT_SENSOR_H
#define EFOOTBOT_TURRET_ENCODER_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEFootBotTurretEncoderDefaultSensor;
}

#include "../control_interface/ci_efootbot_turret_encoder_sensor.h"
#include "efootbot_turret_encoder_default_sensor.h"
#include "efootbot_turret_entity.h"
#include <argos3/core/simulator/sensor.h>

namespace argos {

   class CEFootBotTurretEncoderDefaultSensor : public CCI_EFootBotTurretEncoderSensor,
                                              public CSimulatedSensor {

   public:

      CEFootBotTurretEncoderDefaultSensor();

      virtual ~CEFootBotTurretEncoderDefaultSensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Update();

      virtual void Reset();

   private:

      CEFootBotTurretEntity* m_pcTurretEntity;

   };

}

#endif
