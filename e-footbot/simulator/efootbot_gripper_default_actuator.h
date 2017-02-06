/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_gripper_default_actuator.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef EFOOTBOT_GRIPPER_DEFAULT_ACTUATOR_H
#define EFOOTBOT_GRIPPER_DEFAULT_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEFootBotGripperDefaultActuator;
}

#include "../control_interface/ci_efootbot_gripper_actuator.h"
#include <argos3/plugins/simulator/entities/gripper_equipped_entity.h>
#include <argos3/core/simulator/actuator.h>

namespace argos {

   class CEFootBotGripperDefaultActuator : public CSimulatedActuator,
                                          public CCI_EFootBotGripperActuator {

   public:

      CEFootBotGripperDefaultActuator();

      virtual ~CEFootBotGripperDefaultActuator() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Update();
      virtual void Reset();

      virtual void EnableCheckForObjectGrippedRoutine() {}
      virtual void DisableCheckForObjectGrippedRoutine() {}

   private:

      CGripperEquippedEntity* m_pcGripperEquippedEntity;

   };

}

#endif
