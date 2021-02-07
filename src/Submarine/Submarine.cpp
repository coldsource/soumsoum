#include <Submarine/Submarine.h>

#include <math.h>

using namespace std;
using json = nlohmann::json;

Submarine::Submarine():
	stern("stern", Vector3D(0, -49, 0)),
	back("back", Vector3D(0, -30, 0)),
	center("center", Vector3D(0, -0, 0)),
	diving_plane("diving_plane", Vector3D(0, 0, 3)),
	front("front", Vector3D(0, 30, 0)),
	bow("bow", Vector3D(0, 49, 0)),
	air_tank(Tank::en_opening_type::CLOSED, 10),
	ballast(&air_tank),
	compensating_tank_center(16, 5),
	compensating_tank_front(10, 5),
	compensating_tank_back(10, 5)
{
	AddPart(&stern);
	AddPart(&back);
	AddPart(&center);
	AddPart(&diving_plane);
	AddPart(&front);
	AddPart(&bow);
	
	stern.AddComponent(&compensating_tank_back);
	center.AddComponent(&ballast);
	center.AddComponent(&compensating_tank_center);
	bow.AddComponent(&compensating_tank_front);
	
	air_tank.Fill(air, 3000);
	compensating_tank_center.Fill(8);
	
	components.insert(pair<string, Component *>("ballast", &ballast));
	components.insert(pair<string, Component *>("compensating_tank_center", &compensating_tank_center));
	components.insert(pair<string, Component *>("compensating_tank_front", &compensating_tank_front));
	components.insert(pair<string, Component *>("compensating_tank_back", &compensating_tank_back));
	components.insert(pair<string, Component *>("thrust", &thrust));
	components.insert(pair<string, Component *>("diving_plane", &diving_plane));
}

double Submarine::GetMomentOfInertia() const
{
	return 90000000;
}

void Submarine::StepTime(double dt)
{
	double L = 49.75;
	
	Vector3D back_vector = Vector3D::FromSpherical(L, attitude.x - M_PI, attitude.z);
	forces["thrust"] = { back_vector, Vector3D::FromSpherical(thrust.GetForce(), attitude.x + thrust.GetAngleX(), attitude.z + thrust.GetAngleZ())};
	
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
	
	j["air_tank"] = air_tank.ToJson();
	
	json j_components;
	for(auto it = components.begin(); it!=components.end(); ++it)
		j_components[it->first] = it->second->ToJson();
	
	j["components"] = j_components;
	
	return j;
}
