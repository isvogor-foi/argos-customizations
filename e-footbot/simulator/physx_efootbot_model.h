/**
 * @file <argos3/plugins/robots/foot-bot/simulator/physx_efootbot_model.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef PHYSX_EFOOTBOT_MODEL_H
#define PHYSX_EFOOTBOT_MODEL_H

namespace argos {
   class CPhysXEngine;
   class CPhysXEFootBotModel;
   class CEFootBotEntity;
}

#include <argos3/plugins/simulator/physics_engines/physx/physx_single_body_object_model.h>

namespace argos {

   class CPhysXEFootBotModel : public CPhysXSingleBodyObjectModel {

   public:

      CPhysXEFootBotModel(CPhysXEngine& c_engine,
                         CEFootBotEntity& c_entity);

      virtual void UpdateFromEntityStatus();

   private:

      CEFootBotEntity& m_cEFootBotEntity;
   };

}

#endif
