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
#include <Volume/Cylinder.h>

#include <map>
#include <string>

#include <nlohmann/json.hpp>

class Submarine: public MovingBody
{
	Water water;
	Air air;
	
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
	
	Tank air_tank;
	
	Ballast ballast;
	
	CompensatingTank compensating_tank_center;
	CompensatingTank compensating_tank_front;
	CompensatingTank compensating_tank_back;
	
	Thrust thrust;
	
	std::map<std::string, Component *> components;
	
public:
	Submarine();
	
	double GetMomentOfInertia() const;
	
	void HandleCommand(const nlohmann::json &json);
	
	nlohmann::json ToJson() const;
	
private:
	double get_immersed_volume(double depth) const;
};

#endif
