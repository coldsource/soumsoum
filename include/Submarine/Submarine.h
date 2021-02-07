#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include <Fluid/Water.h>
#include <Fluid/Air.h>
#include <Dynamic/MovingBody.h>
#include <Dynamic/MovingBodyPart.h>
#include <Simulation/SimulationObject.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Submarine/Component.h>
#include <Submarine/CompensatingTank.h>
#include <Submarine/Ballast.h>
#include <Submarine/Thrust.h>
#include <Volume/Sphere.h>
#include <Volume/Cylinder.h>

#include <map>
#include <string>

#include <nlohmann/json.hpp>

class SubmarineBow:public MovingBodyPart, public Sphere
{
public:
	SubmarineBow(const std::string name, double distance):MovingBodyPart(name, distance, 137392.318717), Sphere(4) {};
	
	double GetVolume() const { return Sphere::GetVolume() / 2.0; }
	double GetImmersedVolume(double depth) const { return Sphere::GetImmersedVolume(depth) / 2.0; }
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const
	{
		Sphere::GetContactSurfaces(positive, negative);
		positive->x = negative->x = positive->x / 2;
		positive->z = negative->z = positive->z / 2;
	}
	void GetCx(Vector3D *positive, Vector3D *negative) const
	{
		Sphere::GetCx(positive, negative);
		negative->y = 0;
	}
};

class SubmarineStern:public MovingBodyPart, public Sphere
{
public:
	SubmarineStern(const std::string name, double distance):MovingBodyPart(name, distance, 137392.318717), Sphere(4) {};
	
	double GetVolume() const { return Sphere::GetVolume() / 2.0; }
	double GetImmersedVolume(double depth) const { return Sphere::GetImmersedVolume(depth) / 2.0; }
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const
	{
		Sphere::GetContactSurfaces(positive, negative);
		positive->x = negative->x = positive->x / 2;
		positive->z = negative->z = positive->z / 2;
	}
	void GetCx(Vector3D *positive, Vector3D *negative) const
	{
		Sphere::GetCx(positive, negative);
		positive->y = 0;
	}
};

class SubmarinePart:public MovingBodyPart, public Cylinder
{
public:
	SubmarinePart(const std::string name, double distance):MovingBodyPart(name, distance, 1323580.25224 ), Cylinder(4, 30) {};
	void GetCx(Vector3D *positive, Vector3D *negative) const
	{
		Cylinder::GetCx(positive, negative);
		negative->y = positive->y = 0;
	}
};

class Submarine: public MovingBody, public SimulationObject
{
	Water water;
	Air air;
	
	SubmarineStern stern;
	SubmarinePart back;
	SubmarinePart center;
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
	
	void StepTime(double dt);
	
	void HandleCommand(const nlohmann::json &json);
	
	nlohmann::json ToJson() const;
	
private:
	double get_immersed_volume(double depth) const;
};

#endif
