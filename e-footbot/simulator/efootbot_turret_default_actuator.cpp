/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_turret_default_actuator.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "efootbot_turret_default_actuator.h"

namespace argos {

	 const Real RPM_TO_RADIANS_PER_SEC = ARGOS_PI / 30.0f;

   /****************************************/
   /****************************************/

   CEFootBotTurretDefaultActuator::CEFootBotTurretDefaultActuator() :
      m_pcTurretEntity(NULL),
      m_unDesiredMode(CEFootBotTurretEntity::MODE_OFF) {}

   /****************************************/
   /****************************************/

   void CEFootBotTurretDefaultActuator::SetRobot(CComposableEntity& c_entity) {
      m_pcTurretEntity = &(c_entity.GetComponent<CEFootBotTurretEntity>("turret"));
      m_pcTurretEntity->Enable();
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretDefaultActuator::SetRotation(const CRadians& c_angle) {
      m_pcTurretEntity->SetDesiredRotation(c_angle);
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretDefaultActuator::SetRotationSpeed(SInt32 n_speed_pulses) {
      m_pcTurretEntity->SetDesiredRotationSpeed(RPM_TO_RADIANS_PER_SEC * n_speed_pulses);
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretDefaultActuator::SetMode(ETurretModes e_mode) {
      m_unDesiredMode = e_mode;
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretDefaultActuator::Update() {
      m_pcTurretEntity->SetMode(m_unDesiredMode);
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretDefaultActuator::Reset() {
      m_unDesiredMode = CEFootBotTurretEntity::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CEFootBotTurretDefaultActuator,
                     "efootbot_turret", "default",
                     "Carlo Pinciroli [ilpincy@gmail.com]",
                     "1.0",
                     "The foot-bot turret actuator.",
                     "This actuator controls the foot-bot turret. For a complete\n"
                     "description of its usage, refer to the ci_efootbot_turret_actuator\n"
                     "file.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <efootbot_turret implementation=\"default\" />\n"
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
