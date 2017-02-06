/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_turret_entity.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "efootbot_turret_entity.h"
#include <argos3/core/utility/math/angles.h>
#include <argos3/core/simulator/physics_engine/physics_engine.h>
#include <argos3/core/simulator/space/space.h>

namespace argos {

   /****************************************/
   /****************************************/

   CEFootBotTurretEntity::CEFootBotTurretEntity(CComposableEntity* pc_parent) :
      CEntity(pc_parent),
      m_psAnchor(NULL) {
      Reset();
      Disable();
   }
   
   /****************************************/
   /****************************************/

   CEFootBotTurretEntity::CEFootBotTurretEntity(CComposableEntity* pc_parent,
                                              const std::string& str_id,
                                              SAnchor& s_anchor) :
      CEntity(pc_parent, str_id),
      m_psAnchor(&s_anchor) {
      Reset();
      Disable();
   }
   
   /****************************************/
   /****************************************/

   void CEFootBotTurretEntity::Init(TConfigurationNode& t_tree) {
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretEntity::Reset() {
      m_unMode = MODE_OFF;
      m_cDesRot = CRadians::ZERO;
      m_cOldRot = CRadians::ZERO;
      m_fDesRotSpeed = 0.0;
      m_fCurRotSpeed = 0.0;
      m_psAnchor->OffsetOrientation = CQuaternion();
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretEntity::Update() {
      /* Calculate rotation speed */
      CRadians cZAngle, cYAngle, cXAngle;
      m_psAnchor->OffsetOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      m_fCurRotSpeed =
         NormalizedDifference(cZAngle, m_cOldRot).GetValue() *
         CPhysicsEngine::GetInverseSimulationClockTick();
      /* Save rotation for next time */
      m_cOldRot = cZAngle;
   }

   /****************************************/
   /****************************************/

   CRadians CEFootBotTurretEntity::GetRotation() const {
      CRadians cZAngle, cYAngle, cXAngle;
      m_psAnchor->OffsetOrientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      return cZAngle;
   }

   /****************************************/
   /****************************************/

   Real CEFootBotTurretEntity::GetRotationSpeed() const {
      return m_fCurRotSpeed;
   }

   /****************************************/
   /****************************************/

   const CRadians& CEFootBotTurretEntity::GetDesiredRotation() const {
      return m_cDesRot;
   }

   /****************************************/
   /****************************************/

   Real CEFootBotTurretEntity::GetDesiredRotationSpeed() const {
      return m_fDesRotSpeed;
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretEntity::SetDesiredRotation(const CRadians& c_rotation) {
      m_cDesRot = c_rotation;
      m_cDesRot.SignedNormalize();
   }

   /****************************************/
   /****************************************/

   void CEFootBotTurretEntity::SetDesiredRotationSpeed(Real f_speed) {
      m_fDesRotSpeed = f_speed;
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_ENTITY(CEFootBotTurretEntity);

   /****************************************/
   /****************************************/

}
