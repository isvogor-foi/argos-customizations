/**
 * @file <argos3/plugins/robots/foot-bot/simulator/efootbot_distance_scanner_rotzonly_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "efootbot_distance_scanner_rotzonly_sensor.h"
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real EFOOTBOT_RADIUS          = 0.085036758f;

   static const Real SHORT_RANGE_MIN_DISTANCE = 0.0f;
   static const Real SHORT_RANGE_RAY_START    = EFOOTBOT_RADIUS;
   static const Real SHORT_RANGE_RAY_END      = EFOOTBOT_RADIUS + 0.26f;

   static const Real LONG_RANGE_MIN_DISTANCE  = 0.12f;
   static const Real LONG_RANGE_RAY_START     = EFOOTBOT_RADIUS;
   //static const Real LONG_RANGE_RAY_END       = EFOOTBOT_RADIUS + 1.42f;
   static const Real LONG_RANGE_RAY_END       = EFOOTBOT_RADIUS + 4.92f; 	//5m range

   static const Real SENSOR_ELEVATION         = 0.123199866f;

   /****************************************/
   /****************************************/

   CEFootBotDistanceScannerRotZOnlySensor::CEFootBotDistanceScannerRotZOnlySensor() :
      m_pcRNG(NULL),
      m_bAddNoise(false),
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_bShowRays(false),
      m_lastRotation(0){}

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_EFootBotDistanceScannerSensor::Init(t_tree);
         /* Show rays? */
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
         /* Noise range */
         GetNodeAttributeOrDefault(t_tree, "noise_range", m_cNoiseRange, m_cNoiseRange);
         if(m_cNoiseRange.GetSpan() > 0.0f) {
            m_bAddNoise = true;
            m_pcRNG = CRandom::CreateRNG("argos");
         }
         m_lastRotation = m_ciRotationDirection;
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot distance scanner rot_z_only sensor.", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::SetRobot(CComposableEntity& c_entity) {
      m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
      m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
      m_pcDistScanEntity = &(c_entity.GetComponent<CEFootBotDistanceScannerEquippedEntity>("distance_scanner"));
      m_pcDistScanEntity->Enable();
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::Update() {
      /* Clear the maps */
      m_tReadingsMap.clear();
      m_tShortReadingsMap.clear();
      m_tLongReadingsMap.clear();

      /* Perform calculations only if the sensor is on */
      if(m_pcDistScanEntity->GetMode() != CEFootBotDistanceScannerEquippedEntity::MODE_OFF) {
         /* Update the readings wrt to device mode */
         if(m_pcDistScanEntity->GetMode() == CEFootBotDistanceScannerEquippedEntity::MODE_POSITION_CONTROL) {
            /* Sensor blocked in a position */
            /* Recalculate the rays */
            CalculateRaysNotRotating();
            /* Save the rotation for next time */
            m_cLastDistScanRotation = m_pcDistScanEntity->GetRotation();
            /* Update the values */
            UpdateNotRotating();
         }
         else {

            if(m_lastRotation != m_ciRotationDirection){
            	m_pcDistScanEntity->SetRotation(-m_cLastDistScanRotation);
            	m_cLastDistScanRotation = m_pcDistScanEntity->GetRotation();
            }

            /* Rotating sensor */
            /* Recalculate the rays */
            CalculateRaysRotating();
            /* Update the values */
            UpdateRotating();
            m_cLastDistScanRotation = m_pcDistScanEntity->GetRotation();

         }
      }
      m_currentAngle = m_pcDistScanEntity->GetRotation();

      //prevents one tilt
      if(m_lastRotation != m_ciRotationDirection){
    	  m_currentAngle = m_cLastDistScanRotation;
      }

      // remember what was the last rotation
      m_lastRotation = m_ciRotationDirection;
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::Reset() {
      /* Clear the maps */
      m_tReadingsMap.clear();
      m_tShortReadingsMap.clear();
      m_tLongReadingsMap.clear();
      /* Zero the last rotation */
      m_cLastDistScanRotation = CRadians::ZERO;
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::UpdateNotRotating() {
		CRadians cStartAngle = m_cLastDistScanRotation;

		if(m_ciRotationDirection == 0){
			cStartAngle = CRadians::TWO_PI - cStartAngle;
		}

		CRadians cAngle = cStartAngle;
		cAngle.UnsignedNormalize();

		// beam 1
		/*
		Real fReading = CalculateReadingForRay(m_cLongRangeRays1[0], LONG_RANGE_MIN_DISTANCE);
		m_tLongReadingsMap[cAngle] = fReading;
		m_tReadingsMap[cAngle] = fReading;

		// beam 2
		cAngle += (CRadians::PI * 2.0f / 3.0f);
		fReading = CalculateReadingForRay(m_cLongRangeRays5[0], LONG_RANGE_MIN_DISTANCE);
		m_tLongReadingsMap[cAngle] = fReading;
		m_tReadingsMap[cAngle] = fReading;

		// beam 3
		cAngle += (CRadians::PI * 2.0f / 3.0f);
		fReading = CalculateReadingForRay(m_cLongRangeRays3[0], LONG_RANGE_MIN_DISTANCE);
		m_tLongReadingsMap[cAngle] = fReading;
		m_tReadingsMap[cAngle] = fReading;
		*/
   }

   /****************************************/
   /****************************************/

#define ADD_READING(RAYS,MAP,INDEX,MINDIST)                 \
   cAngle += cInterSensorSpan;                              \
   cAngle.SignedNormalize();                                \
   fReading = CalculateReadingForRay(RAYS[INDEX],MINDIST);  \
   MAP[cAngle] = fReading;                                  \
   m_tReadingsMap[cAngle] = fReading;

#define ADD_READINGS(RAYS,MAP,MINDIST)          \
   ADD_READING(RAYS,MAP,1,MINDIST)              \
   ADD_READING(RAYS,MAP,2,MINDIST)              \
   ADD_READING(RAYS,MAP,3,MINDIST)              \
   ADD_READING(RAYS,MAP,4,MINDIST)              \
   ADD_READING(RAYS,MAP,5,MINDIST)

   void CEFootBotDistanceScannerRotZOnlySensor::UpdateRotating() {
      CRadians cInterSensorSpan = (m_pcDistScanEntity->GetRotation() - m_cLastDistScanRotation).UnsignedNormalize() / 6.0f;
      CRadians cStartAngle = m_cLastDistScanRotation;

      if(m_ciRotationDirection == 0){
    	  cStartAngle = CRadians::TWO_PI - cStartAngle;
      }

      CRadians cAngle = cStartAngle;
      cAngle.UnsignedNormalize();

      //cAngle.();
      Real fReading = CalculateReadingForRay(m_cLongRangeRays1[0], LONG_RANGE_MIN_DISTANCE);
      m_tLongReadingsMap[cAngle] = fReading;
      m_tReadingsMap[cAngle] = fReading;
      ADD_READINGS(m_cLongRangeRays1, m_tLongReadingsMap, LONG_RANGE_MIN_DISTANCE);

      // beam 2
      cAngle += (CRadians::PI * 2.0f / 3.0f);
	  fReading = CalculateReadingForRay(m_cLongRangeRays5[0], LONG_RANGE_MIN_DISTANCE);
	  m_tLongReadingsMap[cAngle] = fReading;
	  m_tReadingsMap[cAngle] = fReading;
	  ADD_READINGS(m_cLongRangeRays5, m_tLongReadingsMap, LONG_RANGE_MIN_DISTANCE);

	  // beam 3
	  cAngle += (CRadians::PI * 2.0f / 3.0f);
	  fReading = CalculateReadingForRay(m_cLongRangeRays3[0], LONG_RANGE_MIN_DISTANCE);
	  m_tLongReadingsMap[cAngle] = fReading;
	  m_tReadingsMap[cAngle] = fReading;
	  ADD_READINGS(m_cLongRangeRays3, m_tLongReadingsMap, LONG_RANGE_MIN_DISTANCE);

   }

   /****************************************/
   /****************************************/

   Real CEFootBotDistanceScannerRotZOnlySensor::CalculateReadingForRay(const CRay3& c_ray,
                                                                      Real f_min_distance) {
      /* Get the closest intersection */
      SEmbodiedEntityIntersectionItem sIntersection;
      if(GetClosestEmbodiedEntityIntersectedByRay(sIntersection,
                                                  c_ray,
                                                  *m_pcEmbodiedEntity)) {
         if(m_bShowRays) m_pcControllableEntity->AddIntersectionPoint(c_ray, sIntersection.TOnRay);
         /* There is an intersection! */
         Real fDistance = c_ray.GetDistance(sIntersection.TOnRay);
         if(fDistance > f_min_distance) {
            /* The distance is returned in meters, but the reading must be in cm */
            if(m_bShowRays) m_pcControllableEntity->AddCheckedRay(true, c_ray);
            return fDistance * 100.0f;
         }
         else {
            /* The detected intersection was too close */
            if(m_bShowRays) m_pcControllableEntity->AddCheckedRay(true, c_ray);
            return -1.0f;
         }
      }
      else {
         /* No intersection */
         if(m_bShowRays) m_pcControllableEntity->AddCheckedRay(false, c_ray);
         return -2.0f;
      }
   }

   /****************************************/
   /****************************************/

/* Highly reuse the vectors to speed up the computation */
#define CALCULATE_SHORT_RANGE_RAY(ANGLE,INDEX)              \
   m_cDirection.RotateZ(ANGLE);                             \
   m_cOriginRayStart = m_cDirection;                        \
   m_cOriginRayEnd = m_cDirection;                          \
   m_cOriginRayStart *= SHORT_RANGE_RAY_START;              \
   m_cOriginRayEnd *= SHORT_RANGE_RAY_END;                  \
   m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayStart += m_cOriginRayStart;                        \
   m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
   m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayEnd += m_cOriginRayEnd;                            \
   m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
   m_cShortRangeRays0[INDEX].Set(m_cRayStart, m_cRayEnd);   \
   m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayStart -= m_cOriginRayStart;                        \
   m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
   m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayEnd -= m_cOriginRayEnd;                            \
   m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
   m_cShortRangeRays2[INDEX].Set(m_cRayStart, m_cRayEnd);   \
                                                            \
// changing here changes visualization, not data reading?
/* Highly reuse the vectors to speed up the computation */
#define CALCULATE_LONG_RANGE_RAY(ANGLE,INDEX)               \
   m_cDirection.RotateZ(ANGLE);                             \
   m_cOriginRayStart = m_cDirection;                        \
   m_cOriginRayEnd = m_cDirection;                          \
   m_cOriginRayStart *= LONG_RANGE_RAY_START;               \
   m_cOriginRayEnd *= LONG_RANGE_RAY_END;                   \
   m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayStart += m_cOriginRayStart;                        \
   m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
   m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayEnd += m_cOriginRayEnd;                            \
   m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
   m_cLongRangeRays1[INDEX].Set(m_cRayStart, m_cRayEnd);    \
   m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayStart -= m_cOriginRayStart;                        \
   m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
   m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayEnd -= m_cOriginRayEnd;                            \
   m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
   m_cLongRangeRays3[INDEX].Set(m_cRayStart, m_cRayEnd);	\
   // changing here changes visualization, not data reading?
   /* Highly reuse the vectors to speed up the computation */
 #define CALCULATE_LONG_RANGE_RAY3(ANGLE,INDEX)               \
	m_cDirection.RotateZ(ANGLE);                             \
	m_cOriginRayStart = m_cDirection;                        \
	m_cOriginRayEnd = m_cDirection;                          \
	m_cOriginRayStart *= LONG_RANGE_RAY_START;               \
	m_cOriginRayEnd *= LONG_RANGE_RAY_END;                   \
	m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;;                        \
	m_cRayStart += m_cOriginRayStart; \
	m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
	m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
	m_cRayEnd += m_cOriginRayEnd;                \
	m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
	m_cLongRangeRays5[INDEX].Set(m_cRayStart, m_cRayEnd); \

#define CALCULATE_LONG_RANGE_RAY1(ANGLE,INDEX)               \
	m_cDirection.RotateZ(ANGLE);                             \
	m_cOriginRayStart = m_cDirection;                        \
	m_cOriginRayEnd = m_cDirection;                          \
	m_cOriginRayStart *= LONG_RANGE_RAY_START;               \
	m_cOriginRayEnd *= LONG_RANGE_RAY_END;                   \
	m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
	m_cRayStart += m_cOriginRayStart;                        \
	m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
	m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
	m_cRayEnd += m_cOriginRayEnd;                            \
	m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
	m_cLongRangeRays1[INDEX].Set(m_cRayStart, m_cRayEnd);    \

#define CALCULATE_LONG_RANGE_RAY2(ANGLE,INDEX)               \
   m_cDirection.RotateZ(ANGLE);                             \
   m_cOriginRayStart = m_cDirection;                        \
   m_cOriginRayEnd = m_cDirection;                          \
   m_cOriginRayStart *= LONG_RANGE_RAY_START;               \
   m_cOriginRayEnd *= LONG_RANGE_RAY_END;                   \
   m_cRayStart = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayStart += m_cOriginRayStart;                        \
   m_cRayStart.SetZ(m_cRayStart.GetZ() + SENSOR_ELEVATION); \
   m_cRayEnd = m_pcEmbodiedEntity->GetOriginAnchor().Position;  \
   m_cRayEnd += m_cOriginRayEnd;                            \
   m_cRayEnd.SetZ(m_cRayEnd.GetZ() + SENSOR_ELEVATION);     \
   m_cLongRangeRays3[INDEX].Set(m_cRayStart, m_cRayEnd);	\
   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::CalculateRaysNotRotating() {
      /* We make the assumption that the foot-bot is rotated only around Z */
      /* Get the foot-bot orientation */
      CRadians cTmp1, cTmp2, cOrientationZ;
      m_pcEmbodiedEntity->GetOriginAnchor().Orientation.ToEulerAngles(cOrientationZ, cTmp1, cTmp2);
      /* Sum the distance scanner orientation */
      cOrientationZ += m_pcDistScanEntity->GetRotation();
      /* Calculate the 2D vector representing this rotation */

      CVector2 cAbsoluteOrientation(1.0, cOrientationZ);
      /* The short range sensors are oriented along the foot-bot local X */
      //m_cDirection = CVector3::X;
      //CALCULATE_SHORT_RANGE_RAY(cAbsoluteOrientation, 0);
      /* The short range sensors are oriented along the foot-bot local Y */
      m_cDirection = CVector3::X;
      //m_cDirection.RotateZ(CRadians::TWO_PI / 3);
      CALCULATE_LONG_RANGE_RAY1(cAbsoluteOrientation, 0);
      m_cDirection = CVector3::X;
      m_cDirection.RotateZ(CRadians::TWO_PI / 3);
      CALCULATE_LONG_RANGE_RAY2(cAbsoluteOrientation, 0);
      m_cDirection = CVector3::X;
      m_cDirection.RotateZ((CRadians::TWO_PI / 3) * 2);
      CALCULATE_LONG_RANGE_RAY3(cAbsoluteOrientation, 0);
   }

   /****************************************/
   /****************************************/

   void CEFootBotDistanceScannerRotZOnlySensor::CalculateRaysRotating() {
      /* We make the assumption that the foot-bot is rotated only around Z */
      /* Get the foot-bot orientation */
      CRadians cTmp1, cTmp2, cOrientationZ;
      m_pcEmbodiedEntity->GetOriginAnchor().Orientation.ToEulerAngles(cOrientationZ, cTmp1, cTmp2);
      /* Sum the distance scanner orientation */
      /* Calculate the 2D vector representing this rotation */
      // 1 cw, 0 ccw
      //if(m_ciRotationDirection == 0){
      if(m_ciRotationDirection == 0){
          cOrientationZ += m_cLastDistScanRotation;
  	  	  //cInterSensorSpan = CVector2(1.0f, (m_pcDistScanEntity->GetRotation() - m_cLastDistScanRotation).UnsignedNormalize() / 6.0f);
      } else {
          cOrientationZ -= m_cLastDistScanRotation;
  	  	  //cInterSensorSpan = CVector2(1.0f, (m_pcDistScanEntity->GetRotation() - m_cLastDistScanRotation).UnsignedNormalize() / 6.0f);
      }

      //std::cout<< "Cur: " << m_currentAngle << " Last " << m_cLastDistScanRotation<<std::endl;

      CVector2 cAbsoluteOrientation;
      /* The sensor is rotating, so calculate the span between each successive ray */
      CVector2 cInterSensorSpan;

      cAbsoluteOrientation = CVector2(1.0, cOrientationZ);
  	  cInterSensorSpan = CVector2(1.0f, (m_pcDistScanEntity->GetRotation() - m_cLastDistScanRotation).UnsignedNormalize() / 6.0f);


      /* The short range sensors are oriented along the foot-bot local X */
      /*
      m_cDirection = CVector3::X;
      CALCULATE_SHORT_RANGE_RAY(cAbsoluteOrientation, 0);
      CALCULATE_SHORT_RANGE_RAY(cInterSensorSpan, 1);
      CALCULATE_SHORT_RANGE_RAY(cInterSensorSpan, 2);
      CALCULATE_SHORT_RANGE_RAY(cInterSensorSpan, 3);
      CALCULATE_SHORT_RANGE_RAY(cInterSensorSpan, 4);
      CALCULATE_SHORT_RANGE_RAY(cInterSensorSpan, 5);
      */
      /* The long range sensors are oriented along the foot-bot local Y */
      //m_cDirection = CVector3(0.5, 0.5, 0);
      // control number of rays (here we have 6)
      // influences visualization
      /* old -- working
      m_cDirection = CVector3::Y;
      CALCULATE_LONG_RANGE_RAY(cAbsoluteOrientation, 0);
      CALCULATE_LONG_RANGE_RAY(cInterSensorSpan, 1);
      CALCULATE_LONG_RANGE_RAY(cInterSensorSpan, 2);
      CALCULATE_LONG_RANGE_RAY(cInterSensorSpan, 3);
      CALCULATE_LONG_RANGE_RAY(cInterSensorSpan, 4);
      CALCULATE_LONG_RANGE_RAY(cInterSensorSpan, 5);
      */
      m_cDirection = CVector3::X;
      //m_cDirection.RotateZ(CRadians::TWO_PI / 3);
      CALCULATE_LONG_RANGE_RAY1(cAbsoluteOrientation, 0);
      CALCULATE_LONG_RANGE_RAY1(cInterSensorSpan, 1);
      CALCULATE_LONG_RANGE_RAY1(cInterSensorSpan, 2);
      CALCULATE_LONG_RANGE_RAY1(cInterSensorSpan, 3);
      CALCULATE_LONG_RANGE_RAY1(cInterSensorSpan, 4);
      CALCULATE_LONG_RANGE_RAY1(cInterSensorSpan, 5);
      m_cDirection = CVector3::X;

      m_cDirection.RotateZ(CRadians::TWO_PI / 3);
      CALCULATE_LONG_RANGE_RAY2(cAbsoluteOrientation, 0);
      CALCULATE_LONG_RANGE_RAY2(cInterSensorSpan, 1);
      CALCULATE_LONG_RANGE_RAY2(cInterSensorSpan, 2);
      CALCULATE_LONG_RANGE_RAY2(cInterSensorSpan, 3);
      CALCULATE_LONG_RANGE_RAY2(cInterSensorSpan, 4);
      CALCULATE_LONG_RANGE_RAY2(cInterSensorSpan, 5);
      m_cDirection = CVector3::X;
      m_cDirection.RotateZ((CRadians::TWO_PI / 3) * 2);
      CALCULATE_LONG_RANGE_RAY3(cAbsoluteOrientation, 0);

      CALCULATE_LONG_RANGE_RAY3(cInterSensorSpan, 1);
      CALCULATE_LONG_RANGE_RAY3(cInterSensorSpan, 2);
      CALCULATE_LONG_RANGE_RAY3(cInterSensorSpan, 3);
      CALCULATE_LONG_RANGE_RAY3(cInterSensorSpan, 4);
      CALCULATE_LONG_RANGE_RAY3(cInterSensorSpan, 5);
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CEFootBotDistanceScannerRotZOnlySensor,
                   "efootbot_distance_scanner", "rot_z_only",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The foot-bot distance scanner sensor (optimized for 2D).",
                   "This sensor accesses the foot-bot distance scanner sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n"
                   "In this implementation, the readings are calculated under the assumption that\n"
                   "the foot-bot is always parallel to the XY plane, i.e., it rotates only around\n"
                   "the Z axis. This implementation is faster than a 3D one and should be used\n"
                   "only when the assumption about the foot-bot rotation holds.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <efootbot_distance_scanner implementation=\"rot_z_only\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to draw the rays shot by the distance scanner in the OpenGL\n"
                   "visualization. This can be useful for sensor debugging but also to understand\n"
                   "what's wrong in your controller. In OpenGL, the rays are drawn in cyan when\n"
                   "they are not obstructed and in purple when they are. In case a ray is\n"
                   "obstructed, a black dot is drawn where the intersection occurred.\n"
                   "To turn this functionality on, add the attribute 'show_rays=\"true\"' in the\n"
                   "XML as in this example:\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <efootbot_distance_scanner implementation=\"rot_z_only\"\n"
                   "                                  show_rays=\"true\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Usable"
      );

}
