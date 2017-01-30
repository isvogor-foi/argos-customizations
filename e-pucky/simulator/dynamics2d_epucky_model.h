/**
 * @file <argos3/plugins/robots/e-pucky/simulator/dynamics2d_epucky_model.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef DYNAMICS2D_EPUCK_MODEL_H
#define DYNAMICS2D_EPUCK_MODEL_H

namespace argos {
   class CDynamics2DDifferentialSteeringControl;
   class CDynamics2DGripper;
   class CDynamics2DGrippable;
   class CDynamics2DEPuckyModel;
}

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_single_body_object_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_differentialsteering_control.h>
#include "epucky_entity.h"

namespace argos {

   class CDynamics2DEPuckyModel : public CDynamics2DSingleBodyObjectModel {

   public:

      CDynamics2DEPuckyModel(CDynamics2DEngine& c_engine,
                              CEPuckyEntity& c_entity);
      virtual ~CDynamics2DEPuckyModel();

      virtual void Reset();

      virtual void UpdateFromEntityStatus();
      
   private:

      CEPuckyEntity& m_cEPuckyEntity;
      CWheeledEntity& m_cWheeledEntity;

      CDynamics2DDifferentialSteeringControl m_cDiffSteering;

      const Real* m_fCurrentWheelVelocity;

   };

}

#endif
