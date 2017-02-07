/* Include the controller definition */
#include "efootbot_diffusion.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
 #include <argos3/core/utility/logging/argos_log.h>

using namespace std;

/****************************************/
/****************************************/

CEFootBotDiffusion::CEFootBotDiffusion() :
		m_pcWheels(NULL), 
		m_batterySensor(NULL),
		m_pcProximity(NULL), 
		m_cAlpha(10.0f), 
		m_fDelta(0.01f), 
		m_fWheelVelocity(2.5f), 
		m_cGoStraightAngleRange(-ToRadians(m_cAlpha), ToRadians(m_cAlpha)) { }

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
	m_pcWheels = GetActuator < CCI_DifferentialSteeringActuator
			> ("differential_steering");
	m_pcProximity = GetSensor < CCI_EFootBotProximitySensor
			> ("efootbot_proximity");
     m_batterySensor = GetSensor<CCI_BatterySensor               >("battery");

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

	/***********************************/
	/******* New stuff -- Ivan *********/
	/***********************************/
	
	m_RotatingSteps = 0;	// how many steps to randomly rotate after faced with obstacle
	m_ForwardSteps = 0;		// after how many forward moving steps randomly change direction
	
	// default ranges for randoms
	m_MinAngle = 15;	m_MaxAngle = 60; // determines how straight or zig-zaggy are robots paths
	m_MinVelocity = 4;	m_MaxVelocity = 8;
	m_MinDistance = 50;	m_MaxDistance = 170;

	m_RandomForwardSteps = GetRandomInteger(m_MinDistance, m_MaxDistance, pcRNG);	// random number of forward steps 
	m_RandomAngle = GetRandomInteger(m_MinAngle, m_MaxAngle, pcRNG);			// random number of rotating steps
	
	m_DefaultFwdVelocity = 5.0;	// default forward velocity (intintionaly did not mess with constructor parameters)
	m_DefaultRotationSpeed = 2.0;
	
	m_RoundProximity = 0.01;	// how close can an object be to stop
	m_FwdProximity = 0.02; 		// how "far" object needs to be to stop rotating
}

/****************************************/
void CEFootBotDiffusion::ControlStep() {
	// Get readings from proximity sensor
	const CCI_EFootBotProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
	// Sum them together 
	CVector2 cAccumulator;		// 360 sensing
	CVector2 cFwdAccumulator;	// only forward sensing
	
	for (size_t i = 0; i < tProxReads.size(); ++i) {
		cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
		// data 0-2 and 21-23 in array are forward facing beams
		if ((i >= 0 && i <= 2) || (i >= 21 && i <= 23)) 
		{
			cFwdAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
		}
	}
	
	// if obstacle detected, and obstacle is in front, or time to perform random rotation (after N random steps forward)
	if ((cAccumulator.Length() >= m_RoundProximity && cFwdAccumulator.Length() > m_FwdProximity) || m_ForwardSteps > m_RandomForwardSteps) {
		// if here becouse it is time to perform rotation randomly
		if (m_ForwardSteps > m_RandomForwardSteps) {
			m_RotatingSteps++;
			
			// when enough steps of rotation, proceed forward
			if (m_RotatingSteps > m_RandomAngle) {
				m_ForwardSteps = 0;
				m_RotatingSteps = 0;

				// generate new random angle for next rotation
				m_RandomAngle = GetRandomInteger(m_MinAngle, m_MaxAngle, pcRNG);
			}
		}
		m_pcWheels->SetLinearVelocity(m_DefaultRotationSpeed, -m_DefaultRotationSpeed);
	} else {
		// if going forward more than 5 steps, change direction of next turn (5, i.e. >1, to avoid getting stuck)
		if (m_ForwardSteps == 5) {
			m_DefaultRotationSpeed *= (-1.0);
			
			// generate new random for forward steps
			m_RandomForwardSteps = GetRandomInteger(m_MinDistance, m_MaxDistance, pcRNG);
			
			// change velocity, (this can be left out)
			m_DefaultFwdVelocity = GetRandomInteger(m_MinVelocity, m_MaxVelocity, pcRNG);
		}
		m_ForwardSteps++;
		m_pcWheels->SetLinearVelocity(m_DefaultFwdVelocity, m_DefaultFwdVelocity);
	}
      	RLOG << "SOC: " << m_batterySensor->GetSoc() << "  " << "t: " << std::endl;


}

int CEFootBotDiffusion::GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG){
	CRange < UInt32 > cRange(min, max);
	int random = pcRNG->Uniform(cRange);
	return random;
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
