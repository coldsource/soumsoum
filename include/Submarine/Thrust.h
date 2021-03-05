#ifndef _THRUST_H_
#define _THRUST_H_

#include <Submarine/Component.h>
#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Dynamic/MovingBodyComponent.h>

#include <nlohmann/json.hpp>

class Thrust: public Component, public SimulationObject, public SimulationStatus, public MovingBodyComponent
{
	enum en_propulsion_type { ELECTRIC, MECHANICAL, CURRENT };
	enum en_steam_dst { GENERATOR, TURBINE, NONE };
	
	en_propulsion_type type = ELECTRIC;
	en_steam_dst steam = GENERATOR;
	
	double rate_ctrl[2] = {0, 0};
	double rate[2] = {0, 0};
	double targeted_rate[2] = {0, 0};
	static constexpr double rate_second[2] = {0.2, 0.03};
	static constexpr double max_force[2] = {700000, 1500000};
	
	double battery = 1;
	double battery_rate = 0;
	static constexpr double battery_charge = 0.0002;
	static constexpr double battery_discharge = -0.0001;
	
public:
	Thrust();
	
	std::string GetName() const { return "thrust"; }
	
	double GetMass() const { return 0; }
	double GetForce(en_propulsion_type type = en_propulsion_type::CURRENT) const;
	
	virtual std::map<std::string, Vector3D> GetForces() const;
	
	void HandleCommand(const nlohmann::json &j);
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
