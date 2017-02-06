/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_distance_scanner_default_actuator.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "efootbot_distance_scanner_default_actuator.h"

namespace argos {

	 const Real CEFootBotDistanceScannerDefaultActuator::RPM_TO_RADIANS_PER_SEC = ARGOS_PI / 30.0f;

   /****************************************/
   /****************************************/

   CEFootBotDistanceScannerDefaultActuator::CEFootBotDistanceScannerDefaultActuator() :
      m_fDesiredRotationSpeed(0.0f),
      m_unDesiredMode(CEFootBotDistanceScannerEquippedEntity::MODE_OFF) {}

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::SetRobot(CComposableEntity& c_entity) {
      m_pcDistanceScannerEquippedEntity = &(c_entity.GetComponent<CEFootBotDistanceScannerEquippedEntity>("distance_scanner"));
      m_pcDistanceScannerEquippedEntity->Enable();
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::SetAngle(const CRadians& c_angle) {
      m_unDesiredMode = CEFootBotDistanceScannerEquippedEntity::MODE_POSITION_CONTROL;
      m_cDesiredRotation = c_angle;
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::SetRPM(Real f_rpm) {
      m_unDesiredMode = CEFootBotDistanceScannerEquippedEntity::MODE_SPEED_CONTROL;
      m_fDesiredRotationSpeed = f_rpm * RPM_TO_RADIANS_PER_SEC;
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::Enable() {
      m_unDesiredMode = CEFootBotDistanceScannerEquippedEntity::MODE_POSITION_CONTROL;
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::Disable() {
      m_unDesiredMode = CEFootBotDistanceScannerEquippedEntity::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::Update() {
      m_pcDistanceScannerEquippedEntity->SetMode(m_unDesiredMode);
      if(m_unDesiredMode == CEFootBotDistanceScannerEquippedEntity::MODE_POSITION_CONTROL) {
         m_pcDistanceScannerEquippedEntity->SetRotation(m_cDesiredRotation);
      }
      else if(m_unDesiredMode == CEFootBotDistanceScannerEquippedEntity::MODE_SPEED_CONTROL) {
         m_pcDistanceScannerEquippedEntity->SetRotationSpeed(m_fDesiredRotationSpeed);
      }
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerDefaultActuator::Reset() {
      m_cDesiredRotation = CRadians::ZERO;
      m_fDesiredRotationSpeed = 0.0f;
      m_unDesiredMode = CEFootBotDistanceScannerEquippedEntity::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CEFootBotDistanceScannerDefaultActuator,
                     "efootbot_distance_scanner", "default",
                     "Carlo Pinciroli [ilpincy@gmail.com]",
                     "1.0",
                     "The foot-bot distance scanner actuator.",
                     "This actuator controls the foot-bot distance scanner. For a complete\n"
                     "description of its usage, refer to the ci_efootbot_distance_scanner_actuator\n"
                     "file.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <efootbot_distance_scanner implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "None for the time being.\n",
                     "Usable"
      );

}
