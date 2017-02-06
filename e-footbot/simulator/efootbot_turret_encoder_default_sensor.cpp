/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_turret_encoder_default_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "efootbot_turret_encoder_default_sensor.h"
#include <argos3/core/simulator/entity/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CEFootBotTurretEncoderDefaultSensor::CEFootBotTurretEncoderDefaultSensor() :
      m_pcTurretEntity(NULL) {}

   /****************************************/
   /****************************************/

   void CEFootBotTurretEncoderDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      m_pcTurretEntity = &(c_entity.GetComponent<CEFootBotTurretEntity>("turret"));
      m_pcTurretEntity->Enable();
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretEncoderDefaultSensor::Update() {
      m_cRotation = m_pcTurretEntity->GetRotation();
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretEncoderDefaultSensor::Reset() {
      m_cRotation = CRadians::ZERO;
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEFootBotTurretEncoderDefaultSensor,
                   "efootbot_turret_encoder", "default",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The foot-bot turret encoder sensor.",
                   "This sensor accesses the foot-bot turret encoder. For a complete\n"
                   "description of its usage, refer to the ci_efootbot_turret_encoder_sensor\n"
                   "file.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <efootbot_turret implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Usable"
      );

}
