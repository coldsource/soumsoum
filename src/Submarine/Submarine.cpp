#include <Submarine/Submarine.h>

#include <math.h>

using namespace std;
using json = nlohmann::json;

Submarine::Submarine():
	stern("stern", Vector3D(0, -49, 0)),
	back("back", Vector3D(0, -30, 0)),
	center("center", Vector3D(0, -0, 0)),
	diving_plane("diving_plane", Vector3D(0, 0, 0)),
	front("front", Vector3D(0, 30, 0)),
	bow("bow", Vector3D(0, 49, 0)),
	air_tank(Tank::en_opening_type::CLOSED, 10),
	ballast(&air_tank),
	compensating_tank_center(16, 5, "compensating_tank_center"),
	compensating_tank_front(10, 5, "compensating_tank_front"),
	compensating_tank_back(10, 5, "compensating_tank_back"),
	thrust(),
	rudder()
{
	AddPart(&stern);
	AddPart(&back);
	AddPart(&center);
	AddPart(&diving_plane);
	AddPart(&front);
	AddPart(&bow);
	
	stern.AddComponent(&compensating_tank_back);
	stern.AddComponent(&thrust);
	stern.AddComponent(&rudder);
	center.AddComponent(&ballast);
	center.AddComponent(&compensating_tank_center);
	bow.AddComponent(&compensating_tank_front);
	
	air_tank.Fill(air, 3000);
	compensating_tank_center.Fill(8);
	
	AddComponent(&ballast);
	AddComponent(&compensating_tank_center);
	AddComponent(&compensating_tank_front);
	AddComponent(&compensating_tank_back);
	AddComponent(&thrust);
	AddComponent(&rudder);
	AddComponent(&diving_plane);
	AddComponent(&map);
	
	latitude = 48.308898557355235;
	longitude = -4.506347834823013;
	
	//attitude.z = M_PI;
}

double Submarine::GetMomentOfInertia() const
{
	return 90000000;
}

void Submarine::AddComponent(Component *component)
{
	components.insert(pair<string, Component *>(component->GetName(), component));
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
