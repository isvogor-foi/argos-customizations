/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_light_rotzonly_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef EFOOTBOT_LIGHT_ROTZONLY_SENSOR_H
#define EFOOTBOT_LIGHT_ROTZONLY_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CEFootBotLightRotZOnlySensor;
   class CLightSensorEquippedEntity;
}

#include "../control_interface/ci_efootbot_light_sensor.h"
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>

namespace argos {

   class CEFootBotLightRotZOnlySensor : public CSimulatedSensor,
                                      public CCI_EFootBotLightSensor {

   public:

      CEFootBotLightRotZOnlySensor();

      virtual ~CEFootBotLightRotZOnlySensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   protected:

      /** Reference to embodied entity associated to this sensor */
      CEmbodiedEntity* m_pcEmbodiedEntity;

      /** Reference to light sensor equipped entity associated to this sensor */
      CLightSensorEquippedEntity* m_pcLightEntity;

      /** Reference to controllable entity associated to this sensor */
      CControllableEntity* m_pcControllableEntity;

      /** Flag to show rays in the simulator */
      bool m_bShowRays;

      /** Random number generator */
      CRandom::CRNG* m_pcRNG;

      /** Whether to add noise or not */
      bool m_bAddNoise;

      /** Noise range */
      CRange<Real> m_cNoiseRange;

      /** Reference to the space */
      CSpace& m_cSpace;
   };

}

#endif