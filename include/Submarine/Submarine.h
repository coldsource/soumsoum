#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include <Fluid/Water.h>
#include <Fluid/Air.h>
#include <Dynamic/MovingBody.h>
#include <Simulation/SimulationObject.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Submarine/Component.h>
#include <Submarine/CompensatingTank.h>
#include <Submarine/Ballast.h>

#include <map>
#include <string>

#include <nlohmann/json.hpp>

class Submarine: public MovingBody, public SimulationObject
{
	Water water;
	Air air;
	
	double radius = 4.4;
	double center_length = 81.1;
	double stern_length = 14;
	double stern_radius = 4;
	
	double base_mass = 4625 * 1000;
	
	Tank air_tank;
	
	Ballast ballast;
	
	CompensatingTank compensating_tank_center;
	CompensatingTank compensating_tank_front;
	CompensatingTank compensating_tank_back;
	
	std::map<std::string, Component *> components;
	
public:
	Submarine();
	
	double GetVolume() const;
	double GetImmersedVolume() const;
	double GetMass() const;
	double GetMomentOfInertia() const;
	double GetDragCoefficient() const;
	
	void StepTime(double dt);
	
	void HandleCommand(const nlohmann::json &json);
	
	nlohmann::json ToJson() const;
	
private:
	double get_immersed_volume(double depth) const;
};

#endif
