#ifndef _THRUST_H_
#define _THRUST_H_

#include <Submarine/Component.h>
#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Dynamic/MovingBodyComponent.h>

#include <nlohmann/json.hpp>

class Thrust: public Component, public SimulationObject, public SimulationStatus, public MovingBodyComponent
{
	double rate = 0;
	double targeted_rate = 0;
	double rate_second = 0.05;
	
public:
	Thrust();
	
	std::string GetName() const { return "thrust"; }
	
	double GetMass() const { return 0; }
	double GetForce() const { return 1500000 * rate; }
	
	virtual std::map<std::string, Vector3D> GetForces() const;
	
	void HandleCommand(const nlohmann::json &j);
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
