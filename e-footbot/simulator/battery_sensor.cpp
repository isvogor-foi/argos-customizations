#include "battery_sensor.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>


namespace argos {

	CBatterySensor::CBatterySensor() :
		//m_pcRNG(NULL),
		m_sDischargeType("non-linear"),
		m_pcBatteryEntity(NULL),
		m_pcEmbodiedEntity(NULL),
		m_pcLEDs(NULL),
        fStartingCapacity(0),
		m_cSpace(CSimulator::GetInstance().GetSpace())
	{ }

	void CBatterySensor::SetRobot(CComposableEntity& c_entity) {
	  try {
		m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
		m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity> ("controller"));
		m_pcBatteryEntity = &(c_entity.GetComponent<CBatterySensorEquippedEntity>("battery"));
		m_pcWheels = &(c_entity.GetComponent<CWheeledEntity>("wheels"));
		m_pcLEDs = &(c_entity.GetComponent<CLEDEquippedEntity>("leds"));
	   }
	  catch(CARGoSException& ex) {
		 THROW_ARGOSEXCEPTION_NESTED("Error setting differential steering actuator to entity \"" << c_entity.GetId() << "\"", ex);
	  }
	}

	void CBatterySensor::InitCapacity()
    {
        m_bChargingState = false;
        m_bProcessingState = false;
        pcRNG = CRandom::CreateRNG("argos"); // default random instance
        float simulation_thick_factor = 1000 * 60 * 60 * CPhysicsEngine::GetSimulationClockTick();
        m_fSOC = 100;
        fNominalCapacity = m_pcBatteryEntity->GetNominalCapacity() * simulation_thick_factor;
        fStartingCapacity = fNominalCapacity;
        fConsumedCapacity = 0;
        if(m_pcBatteryEntity->GetRandomizeInitialSOC()){
            float random = (float)(GetRandomInteger(50, 100, pcRNG)) / 100.0f;
            fStartingCapacity = (m_pcBatteryEntity->GetNominalCapacity() * random) * simulation_thick_factor;
            fConsumedCapacity = fNominalCapacity - fStartingCapacity;
        }
    }

    void CBatterySensor::Init(TConfigurationNode & t_tree)
    {
        try {
			CCI_BatterySensor::Init(t_tree);
			m_pcBatteryEntity->Init(t_tree);

			CBatterySensor::InitCapacity();

			// read XML attributes
			GetNodeAttributeOrDefault(t_tree, "discharge_type", m_sDischargeType, m_sDischargeType);

			m_bConvertCharge = false;
			m_bConvertDischarge = false;

			if(m_sDischargeType.compare("non-linear") == 0){
				m_bConvertCharge = true;
			}

			std::vector<double> Xd(4), Yd(4);
			// normalize Ah to [0,1] range
			Xd[0]= 0.0 * fNominalCapacity;	Yd[0]=4.2;
			Xd[1]= 0.1 * fNominalCapacity;	Yd[1]=3.75;
			Xd[2]= 0.8 * fNominalCapacity;	Yd[2]=3.0;
			Xd[3]= 1.0 * fNominalCapacity;	Yd[3]=2.7;
			dischargeSplineFunction.set_points(Xd, Yd);

		   std::vector<double> Xc(4), Yc(4);
			Xc[0]= 0.0 * fNominalCapacity;	Yc[0]=4.2;
			Xc[1]= 0.05 * fNominalCapacity;	Yc[1]=4.1;
			Xc[2]= 0.5 * fNominalCapacity;	Yc[2]=2.5;
			Xc[3]= 1.0 * fNominalCapacity;	Yc[3]=2.2;
		   chargeSplineFunction.set_points(Xc,Yc);

		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Initialization error in default battery sensor", ex);
		}
    }

    void CBatterySensor::Update()
    {
        if(m_bChargingState){
            Charging();
        }else{
            Discharging();
        }
        CBatterySensor::UpdateLEDs();
    }

    /*
	 * Update LED Colors
	 * The beacon color will is automatically updated to color between red and green gradient (from 0 to 100 respectively).
	 * Depending on the robot actions, the surrounding LEDs will glow:
	 * - WHITE default
	 * - BLUE if robot is processing (regardless of it driving or not)
	 * - YELLOW if robot is charging
	 */
    void CBatterySensor::UpdateLEDs()
    {
        if(m_bProcessingState){
            m_pcLEDs->SetAllLEDsColors(CColor::BLUE);
        }else
            if(m_bChargingState){
                m_pcLEDs->SetAllLEDsColors(CColor::YELLOW);
            }else{
                m_pcLEDs->SetAllLEDsColors(CColor::WHITE);
            }

        int accent_parameter = 0;
        if(m_fSOC >= 80){
            accent_parameter = 20;
        }else
            if(m_fSOC <= 40){
                accent_parameter = -15;
            }

        if(m_fSOC - 15 <= 0){
            hsv_color = new HSVColor(0, 1.0f, 0.3f);
        }else{
            hsv_color = new HSVColor(m_fSOC + accent_parameter, 1.0f, 0.3f);
        }

        RGBColor rgb_color = HSVColorToRGB(hsv_color);
        const CColor *color = new CColor((UInt8)(rgb_color.red), (UInt8)(rgb_color.green), (UInt8)(rgb_color.blue));
        m_pcLEDs->GetLED(12).SetColor(*color);
    }

    void CBatterySensor::Charging()
    {
        float charging_current = m_pcBatteryEntity->GetNominalCapacity() * m_pcBatteryEntity->GetCRate();
        if(m_sDischargeType.compare("linear") == 0){
            fConsumedCapacity -= charging_current * 1000 / 60 / 60 / CPhysicsEngine::GetInverseSimulationClockTick();
            m_fSOC = (1 - fConsumedCapacity / fStartingCapacity) * 100;
        }else{
            // starting capacity based on non-linear discharge, for linear charging
            // do this only in the first pass
            fConsumedCapacity -= charging_current * 1000 / 60 / 60 / CPhysicsEngine::GetInverseSimulationClockTick();

            if(m_bConvertCharge){
            	fConsumedCapacity = CBatterySensor::FindCapacity(fConsumedCapacity);
            	m_bConvertCharge = false;
            	m_bConvertDischarge = true;
            }
            m_fSOC = (chargeSplineFunction(fConsumedCapacity) - m_pcBatteryEntity->GetEmptyVoltage()) /
            		 (m_pcBatteryEntity->GetVoltage() - m_pcBatteryEntity->GetEmptyVoltage()) * 100;
        }
        if(m_fSOC > 100){
            m_fSOC = 100;
        }

    }

    Real CBatterySensor::FindCapacity(Real capacity){
    	float TOLERANCE = 0.01;
    	for(float i = 0.0; i <= fNominalCapacity; i+= 0.1){
    		float diff = 0;
    		if(m_bConvertCharge){
    			diff = dischargeSplineFunction(capacity) - chargeSplineFunction(i);
    		} else {
    			diff = chargeSplineFunction(capacity) - dischargeSplineFunction(i);
    		}
    		if(diff < TOLERANCE && -diff < TOLERANCE){
    			return i;
    		}
    	}
    	return 0;
    }

    void CBatterySensor::Discharging()
    {
        float totalCurrent = 0;
        Real driveCurrent = m_pcBatteryEntity->GetDriveCurrent();
        // if wheels are spinning, add driving current consumption
        if(m_pcWheels->GetWheelVelocity(0) == 0 || m_pcWheels->GetWheelVelocity(1) == 0){
            driveCurrent = driveCurrent / 2.0f;
        }else
            if(m_pcWheels->GetWheelVelocity(0) == 0 && m_pcWheels->GetWheelVelocity(1) == 0){
                driveCurrent = 0.0f;
            }

        // check if processing, add processing current consumption
        if(m_bProcessingState){
            totalCurrent = driveCurrent + m_pcBatteryEntity->GetIdleCurrent() + m_pcBatteryEntity->GetProcessingCurrent();
        }else{
            totalCurrent = driveCurrent + m_pcBatteryEntity->GetIdleCurrent();
        }
        // calculate SOC based on one of two methods available (linear / non-linear)
        // this should be reprogrammed to use voltage only
        if(m_fSOC > 0){
            fConsumedCapacity += totalCurrent * 1000 / 60 / 60 / CPhysicsEngine::GetInverseSimulationClockTick();
            if(m_sDischargeType.compare("linear") == 0){
                m_fSOC = (1 - fConsumedCapacity / fStartingCapacity) * 100;
            }else{
                if(m_bConvertDischarge){
                	fConsumedCapacity = CBatterySensor::FindCapacity(fConsumedCapacity);
                	m_bConvertDischarge = false;
                	m_bConvertCharge = true;
                }
                m_fSOC = (dischargeSplineFunction(fConsumedCapacity) - m_pcBatteryEntity->GetEmptyVoltage()) / (m_pcBatteryEntity->GetVoltage() - m_pcBatteryEntity->GetEmptyVoltage()) * 100;
            }
        }
        else{
            m_fSOC = 0;
        }

    }

    CBatterySensor::RGBColor CBatterySensor::HSVColorToRGB(CBatterySensor::HSVColor *color)
    {
        double red = 0;
        double green = 0;
        double blue = 0;
        if(color->saturation == 0){
            red = color->value;
            green = color->value;
            blue = color->value;
        }else{
            int hue_truncated = 0;
            double f, p, q, t;
            // get quarter in which the color is
            if(color->hue == 360){
                color->hue = 0;
            }else{
                color->hue /= 60;
            }
            hue_truncated = (int)(trunc(color->hue));
            f = color->hue - hue_truncated;
            p = color->value * (1.0 - color->saturation);
            q = color->value * (1.0 - (color->saturation * f));
            t = color->value * (1.0 - (color->saturation * (1.0 - f)));
            switch (hue_truncated){
                case 0:
                    red = color->value;
                    green = t;
                    blue = p;
                    break;
                case 1:
                    red = q;
                    green = color->value;
                    blue = p;
                    break;
                case 2:
                    red = p;
                    green = color->value;
                    blue = t;
                    break;
                case 3:
                    red = p;
                    green = q;
                    blue = color->value;
                    break;
                case 4:
                    red = t;
                    green = p;
                    blue = color->value;
                    break;
                default:
                    red = color->value;
                    green = p;
                    blue = q;
                    break;
            }
        }

        return CBatterySensor::RGBColor((unsigned char)((red * 255)), (unsigned char)((green * 255)), (unsigned char)((blue * 255)));
	};

	int CBatterySensor::GetRandomInteger(int min, int max, CRandom::CRNG* pcRNG){
		CRange < UInt32 > cRange(min, max);
		int random = pcRNG->Uniform(cRange);
		return random;
	}

	void CBatterySensor::Reset() { }

	REGISTER_SENSOR(CBatterySensor,
			"battery", "default",
			"Ivan Svogor",
			"0.2",
			"Battery sensor for e-footbot (footbot copy with battery extensions)",
			"Currently some concerns are not separated, e.g. sensor enables setting state of charge and processing."
			"TODO: discharge and charge concerns should be moved to a customized entity, which sensor only reads",
			"Under development"
	);

} // end namespace
