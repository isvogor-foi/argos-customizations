/**
 * @file <argos3/plugins/robots/e-puck/simulator/dynamics2d_base_station_model.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef DYNAMICS2D_BASE_STATION_MODEL_H
#define DYNAMICS2D_BASE_STATION_MODEL_H

namespace argos {
   class CDynamics2DDifferentialSteeringControl;
   class CDynamics2DGripper;
   class CDynamics2DGrippable;
   class CDynamics2DBaseStationModel;
}

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_single_body_object_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_differentialsteering_control.h>
#include "base_station_entity.h"

namespace argos {

   class CDynamics2DBaseStationModel : public CDynamics2DSingleBodyObjectModel {

   public:

      CDynamics2DBaseStationModel(CDynamics2DEngine& c_engine,
                              CEBaseStationEntity& c_entity);
      virtual ~CDynamics2DBaseStationModel();

      virtual void Reset();

      virtual void UpdateFromEntityStatus();
      
   private:

      CEBaseStationEntity& m_cEPuckEntity;
      CWheeledEntity& m_cWheeledEntity;

      CDynamics2DDifferentialSteeringControl m_cDiffSteering;

      const Real* m_fCurrentWheelVelocity;

   };

}

#endif
