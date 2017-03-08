/**
 * @file <argos3/plugins/robots/e-puck/simulator/dynamics2d_base_station_model.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "dynamics2d_base_station_model.h"
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real EPUCK_MASS                = 0.000001f;

   static const Real EPUCK_PERSONAL_SPACE 	   = 0.0f; // if this is different from EPUCK_RADIUS, robots will overlap
   static const Real EPUCK_RADIUS              = 0.035f;
   static const Real EPUCK_INTERWHEEL_DISTANCE = 0.053f;
   static const Real EPUCK_HEIGHT              = 0.0f;

   static const Real EPUCK_MAX_FORCE           = 1.5f;
   static const Real EPUCK_MAX_TORQUE          = 1.5f;

   enum EPUCK_WHEELS {
      EPUCK_LEFT_WHEEL = 0,
      EPUCK_RIGHT_WHEEL = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DBaseStationModel::CDynamics2DBaseStationModel(CDynamics2DEngine& c_engine,
                                                CEBaseStationEntity& c_entity) :
      CDynamics2DSingleBodyObjectModel(c_engine, c_entity),
      m_cEPuckEntity(c_entity),
      m_cWheeledEntity(m_cEPuckEntity.GetWheeledEntity()),
      m_cDiffSteering(c_engine,
                      EPUCK_MAX_FORCE,
                      EPUCK_MAX_TORQUE,
                      EPUCK_INTERWHEEL_DISTANCE),
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()) {
      /* Create the body with initial position and orientation */
      cpBody* ptBody =
         cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                        cpBodyNew(EPUCK_MASS,
                                  cpMomentForCircle(EPUCK_MASS,
                                                    0.0f,
                                                    EPUCK_RADIUS + EPUCK_RADIUS,
                                                    cpvzero)));
      const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
      ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(ptBody, cZAngle.GetValue());
      /* Create the body shape */
      cpShape* ptShape =
         cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                         cpCircleShapeNew(ptBody,
                        		 	 	  EPUCK_PERSONAL_SPACE,
                                          cpvzero));
      ptShape->e = 0.0; // No elasticity
      ptShape->u = 0.0001f; // Lots of friction
      /* Constrain the actual base body to follow the diff steering control */
      m_cDiffSteering.AttachTo(ptBody);
      /* Set the body so that the default methods work as expected */
      SetBody(ptBody, EPUCK_HEIGHT);
   }

   /****************************************/
   /****************************************/

   CDynamics2DBaseStationModel::~CDynamics2DBaseStationModel() {
      m_cDiffSteering.Detach();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DBaseStationModel::Reset() {
      CDynamics2DSingleBodyObjectModel::Reset();
      m_cDiffSteering.Reset();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DBaseStationModel::UpdateFromEntityStatus() {
      /* Do we want to move? */
      if((m_fCurrentWheelVelocity[EPUCK_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocity[EPUCK_RIGHT_WHEEL] != 0.0f)) {
         m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[EPUCK_LEFT_WHEEL],
                                          m_fCurrentWheelVelocity[EPUCK_RIGHT_WHEEL]);
      }
      else {
         /* No, we don't want to move - zero all speeds */
         m_cDiffSteering.Reset();
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CEBaseStationEntity, CDynamics2DBaseStationModel);

   /****************************************/
   /****************************************/

}
