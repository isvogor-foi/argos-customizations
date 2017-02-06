/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_turret_default_actuator.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef EFOOTBOT_TURRET_DEFAULT_ACTUATOR_H
#define EFOOTBOT_TURRET_DEFAULT_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEFootBotTurretDefaultActuator;
}

#include "../control_interface/ci_efootbot_turret_actuator.h"
#include "efootbot_entity.h"
#include "efootbot_turret_entity.h"
#include <argos3/core/simulator/actuator.h>

namespace argos {

   class CEFootBotTurretDefaultActuator : public CSimulatedActuator,
                                         public CCI_EFootBotTurretActuator {

   public:

      CEFootBotTurretDefaultActuator();
      virtual ~CEFootBotTurretDefaultActuator() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void SetRotation(const CRadians& c_angle);
      virtual void SetRotationSpeed(SInt32 n_speed_pulses);
      virtual void SetMode(ETurretModes e_mode);

      virtual void Update();
      virtual void Reset();

   private:

      CEFootBotTurretEntity* m_pcTurretEntity;
      UInt32 m_unDesiredMode;

   };

}

#endif
