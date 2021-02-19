#ifndef _AIRCONTROLLER_H_
#define _AIRCONTROLLER_H_

#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Submarine/Component.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Fluid/Water.h>
#include <Fluid/Air.h>
#include <Dynamic/MovingBodyComponent.h>

class AirController: public Component, public SimulationObject, public SimulationStatus
{
	Water water;
	Air air;
	
	Tank *air_tank;
	Pump surface_fill;
	
public:
	AirController(Tank *air_tank);
	
	std::string GetName() const { return "air_controller"; }
	
	void StepTime(double dt);
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
