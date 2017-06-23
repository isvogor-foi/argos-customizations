#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <string>

namespace argos {
class CBatterySensor;
class CBatterySensorEquippedEntity;
class CWheeledEntity;
}

#include "battery_sensor_equipped_entity.h"
#include "../control_interface/ci_battery_sensor.h"
#include "spline.h"
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/space/space.h>

namespace argos {

class CBatterySensor: public CSimulatedSensor, public CCI_BatterySensor {

public:

	// nested classes for LED color transformation (HUE to RGB)

	/*
	 * POCO class for storing and comparing RGB colors
	 */
	class RGBColor{
	public:
		unsigned char red;
		unsigned char green;
		unsigned char blue;

		RGBColor(unsigned char red, unsigned char green, unsigned char blue){
			this->red = red;
			this->green = green;
			this->blue = blue;
		};

		bool Equals(RGBColor color){
			if( this->red == color.red && this->green == color.green && this->blue == color.blue){
				return true;
			} else {
				return false;
			}
		};
	};

	/*
	 * POCO class for storing and comparing HSV colors
	 */
	class HSVColor{
	public:
		double hue;
		double saturation;
		double value;

		HSVColor(double hue, double saturation, double value){
			this->hue = hue;
			this->saturation = saturation;
			this->value = value;
		}

		bool Equals(HSVColor color){
			if( this->hue == color.hue && this->saturation == color.saturation && this->value == color.value){
				return true;
			} else {
				return false;
			}
		};
	};

	CBatterySensor();

	// TODO: Fix destructors (i.e. implement them)
	//virtual ~CBatterySensor() {}

	virtual void SetRobot(CComposableEntity& c_entity);
	virtual void Init(TConfigurationNode& t_tree);

	virtual void Update();
	virtual void Reset();

	void InitCapacity();

	//TODO: this belongs to entity
	void Charging();
	void Discharging();
	void UpdateLEDs();


protected:
	CEmbodiedEntity* m_pcEmbodiedEntity; // to who am I associated?
	CBatterySensorEquippedEntity* m_pcBatteryEntity;
	CControllableEntity* m_pcControllableEntity;
	CWheeledEntity* m_pcWheels; // get wheels for velocity
	CLEDEquippedEntity* m_pcLEDs; // to set led depending on SOC

	HSVColor *hsv_color;

	CSpace& m_cSpace;

	Real fNominalCapacity;
	Real fStartingCapacity;
	Real fConsumedCapacity;

private:
	tk::spline dischargeSplineFunction;
	tk::spline chargeSplineFunction;
	std::string m_sDischargeType;
	bool m_bConvertDischarge;
	bool m_bConvertCharge;

	CBatterySensor::RGBColor HSVColorToRGB(HSVColor *color);
	CRandom::CRNG* pcRNG;
	int GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG); // function for generating randoms (to clean up code a bit)
	Real FindCapacity(Real capacity);
	float simulation_tick_factor;

}; // end CBatterySensor

} // end argos

#endif
