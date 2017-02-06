/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_distance_scanner_default_actuator.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef EFOOTBOT_DISTANCE_SCANNER_DEFAULT_ACTUATOR_H
#define EFOOTBOT_DISTANCE_SCANNER_DEFAULT_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CEFootBotDistanceScannerDefaultActuator;
}

#include "../control_interface/ci_efootbot_distance_scanner_actuator.h"
#include "efootbot_entity.h"
#include "efootbot_distance_scanner_equipped_entity.h"
#include <argos3/core/simulator/actuator.h>

namespace argos {

   class CEFootBotDistanceScannerDefaultActuator : public CSimulatedActuator,
                                                  public CCI_EFootBotDistanceScannerActuator {

   public:

  	  static const Real RPM_TO_RADIANS_PER_SEC;

      CEFootBotDistanceScannerDefaultActuator();
      virtual ~CEFootBotDistanceScannerDefaultActuator() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void SetAngle(const CRadians& c_angle);
      virtual void SetRPM(Real f_rpm);

      virtual void Enable();
      virtual void Disable();

      virtual void Update();
      virtual void Reset();

   private:

      CEFootBotDistanceScannerEquippedEntity* m_pcDistanceScannerEquippedEntity;

      CRadians m_cDesiredRotation;
      Real     m_fDesiredRotationSpeed;
      UInt8    m_unDesiredMode;

   };

}

#endif
