/* Include the controller definition */
#include "efootbot_diffusion.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

CEFootBotDiffusion::CEFootBotDiffusion() :
   m_pcWheels(NULL),
   m_pcProximity(NULL),
   m_batterySensor(NULL),
   m_pcLEDs(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f),
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void CEFootBotDiffusion::Init(TConfigurationNode& t_node) {
   /*
    * Get sensor/actuator handles
    *
    * The passed string (ex. "differential_steering") corresponds to the
    * XML tag of the device whose handle we want to have. For a list of
    * allowed values, type at the command prompt:
    *
    * $ argos3 -q actuators
    *
    * to have a list of all the possible actuators, or
    *
    * $ argos3 -q sensors
    *
    * to have a list of all the possible sensors.
    *
    * NOTE: ARGoS creates and initializes actuators and sensors
    * internally, on the basis of the lists provided the configuration
    * file at the <controllers><footbot_diffusion><actuators> and
    * <controllers><footbot_diffusion><sensors> sections. If you forgot to
    * list a device in the XML and then you request it here, an error
    * occurs.
    */
   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator >("differential_steering");
   m_pcProximity = GetSensor  <CCI_EFootBotProximitySensor      >("efootbot_proximity"    );
   m_batterySensor = GetSensor<CCI_BatterySensor                >("battery");
   m_pcLEDs        = GetActuator <CCI_LEDsActuator              >("leds");


   /*
    * Parse the configuration file
    *
    * The user defines this part. Here, the algorithm accepts three
    * parameters and it's nice to put them in the config file so we don't
    * have to recompile if we want to try other settings.
    */
   GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
   m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
   GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
   GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);


}

/****************************************/
/****************************************/

void CEFootBotDiffusion::ControlStep() {
    int intensityCompensation = 0;
    if(m_batterySensor->GetSoc() > 80)
      intensityCompensation = 20;
    if(m_batterySensor->GetSoc() <= 45)
      intensityCompensation = -15;


    CEFootBotDiffusion::HSV data = CEFootBotDiffusion::HSV(m_batterySensor->GetSoc() + intensityCompensation, 1.0, 0.3);
    CEFootBotDiffusion::RGB value = HSVToRGB(data);

    //const CColor *color = new CColor((UInt8) value.R, (UInt8) value.G, (UInt8) value.B, (UInt8) 255);
    //m_pcLEDs->SetAllColors(CColor::WHITE);
    //m_pcLEDs->SetSingleColor(12, *color);


   /* Get readings from proximity sensor */
   const CCI_EFootBotProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
   /* Sum them together */
   CVector2 cAccumulator;
   for(size_t i = 0; i < tProxReads.size(); ++i) {
      cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
   }
   cAccumulator /= tProxReads.size();
   /* If the angle of the vector is small enough and the closest obstacle
    * is far enough, continue going straight, otherwise curve a little
    */
   CRadians cAngle = cAccumulator.Angle();
   if(m_cGoStraightAngleRange.WithinMinBoundIncludedMaxBoundIncluded(cAngle) &&
      cAccumulator.Length() < m_fDelta ) {
      /* Go straight */
      m_pcWheels->SetLinearVelocity(m_fWheelVelocity, m_fWheelVelocity);
   }
   else {
      /* Turn, depending on the sign of the angle */
      if(cAngle.GetValue() > 0.0f) {
         m_pcWheels->SetLinearVelocity(m_fWheelVelocity, 0.0f);
      }
      else {
         m_pcWheels->SetLinearVelocity(0.0f, m_fWheelVelocity);
      }
   }
   RLOG << "SOC: " << m_batterySensor->GetSoc() << "  " << "t: " << value.R <<":"<< value.G <<":"<< value.B << std::endl;

}


  CEFootBotDiffusion::RGB CEFootBotDiffusion::HSVToRGB(CEFootBotDiffusion::HSV hsv) {
  double r = 0, g = 0, b = 0;

  if (hsv.S == 0)
  {
    r = hsv.V;
    g = hsv.V;
    b = hsv.V;
  }
  else
  {
    int i;
    double f, p, q, t;

    if (hsv.H == 360)
      hsv.H = 0;
    else
      hsv.H = hsv.H / 60;

    i = (int)trunc(hsv.H);
    f = hsv.H - i;

    p = hsv.V * (1.0 - hsv.S);
    q = hsv.V * (1.0 - (hsv.S * f));
    t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

    switch (i)
    {
    case 0:
      r = hsv.V;
      g = t;
      b = p;
      break;

    case 1:
      r = q;
      g = hsv.V;
      b = p;
      break;

    case 2:
      r = p;
      g = hsv.V;
      b = t;
      break;

    case 3:
      r = p;
      g = q;
      b = hsv.V;
      break;

    case 4:
      r = t;
      g = p;
      b = hsv.V;
      break;

    default:
      r = hsv.V;
      g = p;
      b = q;
      break;
    }

  }

  return CEFootBotDiffusion::RGB((unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255));
}

/****************************************/
/****************************************/

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the configuration file to refer to this
 * controller.
 * When ARGoS reads that string in the configuration file, it knows which
 * controller class to instantiate.
 * See also the configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CEFootBotDiffusion, "efootbot_diffusion_controller")
