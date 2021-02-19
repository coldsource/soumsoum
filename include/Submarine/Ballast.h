#ifndef _BALLAST_H_
#define _BALLAST_H_

#include <Simulation/SimulationStatus.h>
#include <Submarine/Component.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Fluid/Water.h>
#include <Fluid/Air.h>
#include <Dynamic/MovingBodyComponent.h>

class Ballast: public Component, public MovingBodyComponent, public SimulationStatus
{
	Water water;
	Air air;
	
	Tank tank;
	Pump fill_pump;
	Pump empty_pump;
	
	static const double constexpr volume = 650;
	
public:
	Ballast(Tank *air_source);
	
	std::string GetName() const { return "ballast"; }
	
	double GetMass() const { return tank.GetMass(); }
	double GetMassMax() const { return volume * water.GetDensity(); }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
