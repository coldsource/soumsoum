#ifndef _BALLAST_H_
#define _BALLAST_H_

#include <Submarine/Component.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Fluid/Water.h>
#include <Fluid/Air.h>
#include <Dynamic/MovingBodyComponent.h>

class Ballast: public Component, public MovingBodyComponent
{
	Water water;
	Air air;
	
	Tank tank;
	Pump fill_pump;
	Pump empty_pump;
	
public:
	Ballast(Tank *air_source);
	
	double GetMass() const { return tank.GetMass(); }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
