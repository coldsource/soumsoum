#ifndef _CREW_H_
#define _CREW_H_

#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Dynamic/MovingBodyComponent.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Submarine/Component.h>
#include <Fluid/Dioxygen.h>
#include <Fluid/CarbonDioxide.h>

class Crew: public SimulationObject, public SimulationStatus, public MovingBodyComponent, public Component
{
	static constexpr int members = 65;
	static constexpr double member_weight = 80;
	static constexpr double breath_rate = 0.006 / 1000;
	static constexpr double breath_delta = 0.000003096;
	static constexpr double eat_rate = 1.2 / 86400;
	static constexpr double waste_rate = eat_rate - breath_delta;
	
	Dioxygen dioxygen;
	CarbonDioxide carbon_dioxide;
	
	Tank o2_tank;
	Tank co2_tank;
	Pump regeneration;
	
	double supplies = 5000;
	double waste = 0;
	
public:
	Crew();
	
	std::string GetName() const { return "crew"; }
	double GetMass() const { return o2_tank.GetMass() + co2_tank.GetMass() + supplies + waste; }
	
	void HandleCommand(const nlohmann::json &j);
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
