#ifndef _COMPENSATINGTANK_H_
#define _COMPENSATINGTANK_H_

#include <Simulation/SimulationStatus.h>
#include <Submarine/Component.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Fluid/Water.h>
#include <Dynamic/MovingBodyComponent.h>

class CompensatingTank: public Component, public MovingBodyComponent, public SimulationStatus
{
	Water water;
	
	double flow;
	Tank tank;
	Pump fill_pump;
	Pump empty_pump;
	
	std::string name;
	
public:
	CompensatingTank(double capacity, double flow, const std::string &name);
	
	void SetTwinCompensatingTank(CompensatingTank *twin_tank);
	
	std::string GetName() const { return name; }
	
	double GetMass() const { return tank.GetMass(); }
	double Fill(double volume) { return tank.Fill(water, volume); }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
