/**
 * @file <argos3/plugins/robots/foot-bot/control_interface/ci_efootbot_base_ground_sensor.h>
 *
 * @brief This file provides the interface of the efootbot base ground sensor.
 *
 * On the robot, there are two kinds of ground sensors.
 *
 * The BASE ground sensors are located on the main PCB, intertwined with the
 * proximity sensors and evenly spaced. They are 8 and are useful for detecting
 * holes.
 *
 * The MOTOR ground sensors are built on the motor PCB and located close to the
 * motors. They are 4 and useful to detect changes in color on the ground (i.e.,
 * for line following).
 *
 * This sensor provides access to the base sensors. The readings are in the following
 * order (seeing the robot from TOP, battery socket is the BACK):
 *
 *      front
 *
 *        0      r
 * l    1   7    i
 * e  2       6  g
 * f    3   5    h
 * t      4      t
 *
 *       back
 *
 * @author Carlo Pinciroli <ilpincy@gmail.com>
 */

#ifndef CCI_EFOOTBOT_BASE_GROUND_SENSOR_H
#define CCI_EFOOTBOT_BASE_GROUND_SENSOR_H

namespace argos {
   class CCI_EFootBotBaseGroundSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/datatypes/color.h>
#include <vector>

namespace argos {

   class CCI_EFootBotBaseGroundSensor : virtual public CCI_Sensor {

   public:

      struct SReading {
         Real Value;
         CVector2 Offset;
	 
         SReading() :
            Value(0.0f) {}
	 
         SReading(Real f_value,
                  const CVector2& c_offset) :
            Value(f_value),
            Offset(c_offset) {}
      };

      typedef std::vector<SReading> TReadings;

   public:

      CCI_EFootBotBaseGroundSensor();

      virtual ~CCI_EFootBotBaseGroundSensor() {}
      
      const TReadings& GetReadings() const;
      
      const CColor GetFloorColor() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      TReadings m_tReadings;

      CColor m_floorColor;

   };

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EFootBotBaseGroundSensor::SReading& s_reading);

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_EFootBotBaseGroundSensor::TReadings& t_readings);

}

#endif
