/*
 * AUTHOR: Carlo Pinciroli <cpinciro@ulb.ac.be>
 *
 * An example diffusion controller for the foot-bot.
 *
 * This controller makes the robots behave as gas particles. The robots
 * go straight until they get close enough to another robot, in which
 * case they turn, loosely simulating an elastic collision. The net effect
 * is that over time the robots diffuse in the environment.
 *
 * The controller uses the proximity sensor to detect obstacles and the
 * wheels to move the robot around.
 *
 * This controller is meant to be used with the XML files:
 *    experiments/diffusion_1.argos
 *    experiments/diffusion_10.argos
 */

#ifndef EFOOTBOT_DIFFUSION_H
#define EFOOTBOT_DIFFUSION_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the differential steering actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
/* Definition of the foot-bot proximity sensor */
#include <argos3/core/utility/math/rng.h>
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-footbot/control_interface/ci_efootbot_proximity_sensor.h"
#include "/home/ivan/dev/argos-custom/argos3/plugins/robots/e-pucky/control_interface/ci_battery_sensor.h"
/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;

/*
 * A controller is simply an implementation of the CCI_Controller class.
 */
class CEFootBotDiffusion: public CCI_Controller {

public:

	/* Class constructor. */
	CEFootBotDiffusion();

	/* Class destructor. */
	virtual ~CEFootBotDiffusion() {
	}

	/*
	 * This function initializes the controller.
	 * The 't_node' variable points to the <parameters> section in the XML
	 * file in the <controllers><footbot_diffusion_controller> section.
	 */
	virtual void Init(TConfigurationNode& t_node);

	/*
	 * This function is called once every time step.
	 * The length of the time step is set in the XML file.
	 */
	virtual void ControlStep();

	/*
	 * This function resets the controller to its state right after the
	 * Init().
	 * It is called when you press the reset button in the GUI.
	 * In this example controller there is no need for resetting anything,
	 * so the function could have been omitted. It's here just for
	 * completeness.
	 */
	virtual void Reset() {
	}

	/*
	 * Called to cleanup what done by Init() when the experiment finishes.
	 * In this example controller there is no need for clean anything up,
	 * so the function could have been omitted. It's here just for
	 * completeness.
	 */
	virtual void Destroy() {
	}

private:

	/* Pointer to the differential steering actuator */
	CCI_DifferentialSteeringActuator* m_pcWheels;
	/* Pointer to the foot-bot proximity sensor */
	CCI_EFootBotProximitySensor* m_pcProximity;

	/*
	 * The following variables are used as parameters for the
	 * algorithm. You can set their value in the <parameters> section
	 * of the XML configuration file, under the
	 * <controllers><footbot_diffusion_controller> section.
	 */

	/* Maximum tolerance for the angle between
	 * the robot heading direction and
	 * the closest obstacle detected. */
	CDegrees m_cAlpha;
	/* Maximum tolerance for the proximity reading between
	 * the robot and the closest obstacle.
	 * The proximity reading is 0 when nothing is detected
	 * and grows exponentially to 1 when the obstacle is
	 * touching the robot.
	 */
	Real m_fDelta;
	/* Wheel speed. */
	Real m_fWheelVelocity;
	/* Angle tolerance range to go straight.
	 * It is set to [-alpha,alpha]. */
	CRange<CRadians> m_cGoStraightAngleRange;

   	CCI_BatterySensor* m_batterySensor;


	/***********************************/
	/******* New stuff -- Ivan *********/
	/***********************************/
	int m_RotatingSteps;	// how much did I rotate
	int m_ForwardSteps;		// how far did I go forward 
		
	int m_RandomAngle;		// how much to rotate
	int m_RandomForwardSteps;	// how far to go forward

	float m_RoundProximity;	// when to stop if there is an obstacle
	float m_FwdProximity;	// whan to stop rotating if obstacle detected
	
	float m_DefaultRotationSpeed;	// how fast to rotate
	float m_DefaultFwdVelocity;		// how fast to go forward by default
	
	int m_MinAngle, m_MaxAngle;		// between which angles are random rotations
	int m_MinVelocity, m_MaxVelocity;	// between which velocites is my default velocity
	int m_MinDistance, m_MaxDistance;	// between which distances do I stop and change direction
	
	CRandom::CRNG* pcRNG = CRandom::CreateRNG("argos"); // default random instance
	virtual int GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG); // function for generating randoms (to clean up code a bit)

};

#endif
