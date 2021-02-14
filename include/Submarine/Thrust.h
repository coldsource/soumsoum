#ifndef _THRUST_H_
#define _THRUST_H_

#include <Submarine/Component.h>
#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Dynamic/MovingBodyComponent.h>

#include <nlohmann/json.hpp>

class Submarine;

class Thrust: public Component, public SimulationObject, public SimulationStatus, public MovingBodyComponent
{
	Submarine *submarine;
	
	double angle_x = 0;
	double angle_z = 0;
	
	double rate = 0;
	double targeted_rate = 0;
	double rate_second = 0.05;
	
public:
	Thrust();
	
	double GetMass() const { return 0; }
	double GetAngleX() const { return angle_x; }
	double GetAngleZ() const { return angle_z; }
	double GetForce() const { return 3000000 * rate; }
	
	virtual std::map<std::string, Vector3D> GetForces() const;
	
	void HandleCommand(const nlohmann::json &j);
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
