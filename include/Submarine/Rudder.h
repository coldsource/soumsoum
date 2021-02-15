#ifndef _RUDDER_H_
#define _RUDDER_H_

#include <Submarine/Component.h>
#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Dynamic/MovingBodyComponent.h>

#include <nlohmann/json.hpp>

class Rudder: public Component, public SimulationObject, public SimulationStatus, public MovingBodyComponent
{
	double angle_rate = 0.5;
	double targeted_angle_x = 0;
	double angle_x = 0;
	double targeted_angle_z = 0;
	double angle_z = 0;
	
	const double force = 300000;
	
public:
	Rudder();
	
	double GetMass() const { return 0; }
	
	virtual std::map<std::string, Vector3D> GetForces() const;
	
	void HandleCommand(const nlohmann::json &j);
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
