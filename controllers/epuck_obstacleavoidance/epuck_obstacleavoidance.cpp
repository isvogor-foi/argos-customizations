  /* Include the controller definition */
  #include "epuck_obstacleavoidance.h"
  /* Function definitions for XML parsing */
  #include <argos3/core/utility/configuration/argos_configuration.h>
  #include <argos3/core/utility/logging/argos_log.h>
  #include <argos3/core/simulator/space/space.h>


  /****************************************/
  /****************************************/

  CEPuckObstacleAvoidance::CEPuckObstacleAvoidance() :
     m_pcWheels(NULL),
     m_pcProximity(NULL),
     m_batterySensor(NULL),
     m_fWheelVelocity(15.5f) {}

  /****************************************/
  /****************************************/

  /**************** Battery test ****************/
  
  Real current_left_velocity, current_right_velocity;

/*
  void CEPuckObstacleAvoidance::InitializeBattery(){
    batteryCapacity = 100.0f;
  }
*/
/*
  void CEPuckObstacleAvoidance::ConsumeBattery(){

    float current_consumption = 0.0;

    if(current_right_velocity > 0){
      current_consumption += 0.1f;
    }
    if(current_left_velocity > 0){
      current_consumption += 0.1f;
    }

    // discharge
    batteryCapacity -= current_consumption;

    if(batteryCapacity <= 30.0f){
      // stop me if battery is empty
      m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
    }

    //GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
    //RLOG << "Battery at: " << batteryCapacity << " current: " << current_left_velocity << ", " << current_right_velocity << std::endl;

    // RLOG << "m_pcWheels->m_fCurrentVelocity;" << std::endl;
    
  }
  */

  /******************************************/

  void CEPuckObstacleAvoidance::Init(TConfigurationNode& t_node) {
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
      * file at the <controllers><epuck_obstacleavoidance><actuators> and
      * <controllers><epuck_obstacleavoidance><sensors> sections. If you forgot to
      * list a device in the XML and then you request it here, an error
      * occurs.
      */
    // get actuator -- e-differential-steering 
     m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
     m_pcProximity = GetSensor  <CCI_ProximitySensor             >("proximity"    );
     m_batterySensor = GetSensor<CCI_BatterySensor               >("battery");
     /*
      * Parse the configuration file
      *
      * The user defines this part. Here, the algorithm accepts three
      * parameters and it's nice to put them in the config file so we don't
      * have to recompile if we want to try other settings.
      */
     GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
     
     //m_fWheelVelocity = (float) (GetRandomInteger(10, 100, pcRNG) / 10.0f);

     //InitializeBattery();

  }

  /****************************************/
  /****************************************/

  void CEPuckObstacleAvoidance::ControlStep() {
     /* Get the highest reading in front of the robot, which corresponds to the closest object */
     Real fMaxReadVal = m_pcProximity->GetReadings()[0];
     UInt32 unMaxReadIdx = 0;
     if(fMaxReadVal < m_pcProximity->GetReadings()[1]) {
        fMaxReadVal = m_pcProximity->GetReadings()[1];
        unMaxReadIdx = 1;
     }
     if(fMaxReadVal < m_pcProximity->GetReadings()[7]) {
        fMaxReadVal = m_pcProximity->GetReadings()[7];
        unMaxReadIdx = 7;
     }
     if(fMaxReadVal < m_pcProximity->GetReadings()[6]) {
        fMaxReadVal = m_pcProximity->GetReadings()[6];
        unMaxReadIdx = 6;
     }

     /* Do we have an obstacle in front? */
     if(fMaxReadVal > 0.0f) {
       /* Yes, we do: avoid it */
       if(unMaxReadIdx == 0 || unMaxReadIdx == 1) {
         /* The obstacle is on the left, turn right */
          
        current_left_velocity = m_fWheelVelocity;
        current_right_velocity = 0.0f;

        //m_pcWheels->SetLinearVelocity(m_fWheelVelocity, 0.0f);
       }
       else {
         /* The obstacle is on the left, turn right */
          //m_pcWheels->SetLinearVelocity(0.0f, m_fWheelVelocity);
          current_left_velocity = 0.0f;
          current_right_velocity = m_fWheelVelocity;
       }
     }
     else {
       /* No, we don't: go straight */
          current_left_velocity = m_fWheelVelocity;
          current_right_velocity = m_fWheelVelocity;
          //m_pcWheels->SetLinearVelocity(m_fWheelVelocity, m_fWheelVelocity);
      }

    // change the whell velocity according to previous conditions

      m_pcWheels->SetLinearVelocity(current_left_velocity, current_right_velocity);

      //RLOG << "Battery reading: " << m_batterySensor->GetReadings() << std::endl;
      	RLOG << "SSOC: " << m_batterySensor->GetStartingSoc() << ", " << m_batterySensor->GetSoc() << std::endl;
      //ConsumeBattery();

  }

/*
int CEPuckObstacleAvoidance::GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG){
  CRange < UInt32 > cRange(min, max);
  int random = pcRNG->Uniform(cRange);
  return random;
}
*/

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
  REGISTER_CONTROLLER(CEPuckObstacleAvoidance, "epuck_obstacleavoidance_controller")
