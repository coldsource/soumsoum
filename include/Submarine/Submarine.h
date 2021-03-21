#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include <Fluid/Water.h>
#include <Fluid/Air.h>
#include <Dynamic/MovingBody.h>
#include <Dynamic/MovingBodyPart.h>
#include <Submarine/SubmarineBow.h>
#include <Submarine/SubmarinePart.h>
#include <Submarine/SubmarineStern.h>
#include <Submarine/DivingPlane.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Submarine/Component.h>
#include <Submarine/CompensatingTank.h>
#include <Submarine/Ballast.h>
#include <Submarine/Thrust.h>
#include <Submarine/Rudder.h>
#include <Submarine/AirController.h>
#include <Submarine/SimulationControl.h>
#include <Submarine/Crew.h>
#include <Submarine/Weighing.h>
#include <Volume/Cylinder.h>

#include <map>
#include <string>
#include <mutex>

#include <nlohmann/json.hpp>

class Submarine: public MovingBody
{
	SubmarineStern stern;
	SubmarinePart back;
	SubmarinePart center;
	DivingPlane diving_plane;
	SubmarinePart front;
	SubmarineBow bow;
	
	double radius = 4;
	double center_length = 81.1;
	double stern_length = 14;
	double stern_radius = 4;
	
	double base_mass = 4625 * 1000;
	double reference_mass;
	double reference_net_mass;
	
	Tank air_tank;
	
	Ballast ballast;
	
	CompensatingTank compensating_tank_center;
	CompensatingTank compensating_tank_front;
	CompensatingTank compensating_tank_back;
	
	AirController air_controller;
	
	Thrust thrust;
	Rudder rudder;
	
	Crew crew;
	
	Weighing weighing;
	
	SimulationControl simulation_control;
	double time_compression = 1;
	bool simulation_rate_limit = true;
	
	std::map<std::string, Component *> components;
	
	std::mutex mutex;
	
public:
	Submarine();
	~Submarine();
	
	double GetMomentOfInertia() const;
	
	double GetTimeCompression() const { return time_compression; }
	void SetTimeCompression(double time_compression) { this->time_compression = time_compression; }
	bool GetSimulationRateLimit() const { return simulation_rate_limit; }
	void SetSimulationRateLimit(bool simulation_rate_limit) { this->simulation_rate_limit = simulation_rate_limit; }
	
	const Ballast &GetBallast() const { return ballast; }
	double GetReferenceMass() const { return reference_mass; }
	double GetReferenceNetMass() const { return reference_net_mass; }
	double GetMassCentering() const;
	
	void AddComponent(Component *component);
	void HandleCommand(const nlohmann::json &json);
	
private:
	double get_immersed_volume(double depth) const;
};

#endif
