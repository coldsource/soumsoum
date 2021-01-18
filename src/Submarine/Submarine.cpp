#include <Submarine/Submarine.h>
#include <Force/ArchimedesPrinciple.h>
#include <Force/Gravity.h>
#include <Force/Drag.h>

#include <math.h>

using namespace std;
using json = nlohmann::json;

Submarine::Submarine():
	air_tank(Tank::en_opening_type::CLOSED, 10),
	ballast(&air_tank),
	compensating_tank_center(16, 5),
	compensating_tank_front(10, 5),
	compensating_tank_back(10, 5)
{
	air_tank.Fill(air, 3000);
	compensating_tank_center.Fill(8);
	
	components.insert(pair<string, Component *>("ballast", &ballast));
	components.insert(pair<string, Component *>("compensating_tank_center", &compensating_tank_center));
	components.insert(pair<string, Component *>("compensating_tank_front", &compensating_tank_front));
	components.insert(pair<string, Component *>("compensating_tank_back", &compensating_tank_back));
}

double Submarine::GetVolume() const
{
	return get_immersed_volume(8.8);
}

double Submarine::GetImmersedVolume() const
{
	if(position.z>=0)
		return 0;
	
	return get_immersed_volume(-position.z);
}

double Submarine::get_immersed_volume(double depth) const
{
	if(depth>8.8)
		depth = 8.8;
	
	double bow = (M_PI * depth * depth * (3 * radius - depth)) / 6;
	double middle = center_length * (radius * radius * acos(1 - depth / radius) - (radius - depth) * sqrt(depth * (2 * radius - depth)));
	double stern = 1.0 / 3.0 * M_PI * (radius * radius + stern_radius * stern_radius + radius * stern_radius) * depth / (2 * radius);
	
	return bow + middle + stern;
}

double Submarine::GetMass() const
{
	return base_mass + ballast.GetMass();
}

double Submarine::GetMomentOfInertia() const
{
	return 63000000;
}

double Submarine::GetDragCoefficient() const
{
	return 0.5;
}

void Submarine::StepTime(double dt)
{
	double L = 49.75;
	Vector3D center_vector(0, 0, 0);
	Vector3D front_vector = Vector3D::FromNormAngle(L, attitude.x, attitude.z);
	Vector3D back_vector = Vector3D::FromNormAngle(L, attitude.x + M_PI, attitude.z);
	Vector3D linear_speed_front = Vector3D::FromNormAngle(angular_speed.x * L, attitude.x + M_PI/2, 0) + Vector3D::FromNormAngle(angular_speed.z * L, 0, attitude.x + M_PI/2);
	Vector3D linear_speed_back = Vector3D::FromNormAngle(angular_speed.x * L, attitude.x - M_PI/2, 0) + Vector3D::FromNormAngle(angular_speed.z * L, 0, attitude.x - M_PI/2);
	
	double center_mass = base_mass + ballast.GetMass() + compensating_tank_center.GetMass();
	double front_mass = compensating_tank_front.GetMass();
	double back_mass = compensating_tank_back.GetMass();
	
	
	forces["ap"] = { center_vector, ArchimedesPrinciple(*this, water)};
	forces["gravity"] = { center_vector, Gravity(center_mass)};
	forces["drag"] = { center_vector, Drag(*this, water, speed)};
	
	forces["fgravity"] = { front_vector, Gravity(front_mass)};
	forces["fdrag"] = { front_vector, Drag(*this, water, linear_speed_front)};
	
	forces["bgravity"] = { back_vector, Gravity(back_mass)};
	//forces["bdrag"] = { back_vector, Drag(*this, water, linear_speed_back)};
	
	forces["prop"] = { center_vector, Vector3D::FromNormAngle(8000000, attitude.x, attitude.z)};
	
	MovingBody::StepTime(dt);
}

void Submarine::HandleCommand(const nlohmann::json &json)
{
	auto it = components.find(json["component"]);
	if(it==components.end())
		return;
	
	it->second->HandleCommand(json);
}

json Submarine::ToJson() const
{
	json j = MovingBody::ToJson();
	j["ballast"] = ballast.ToJson();
	j["air_tank"] = air_tank.ToJson();
	
	json j_components;
	for(auto it = components.begin(); it!=components.end(); ++it)
		j_components[it->first] = it->second->ToJson();
	j["components"] = j_components;
	
	return j;
}
