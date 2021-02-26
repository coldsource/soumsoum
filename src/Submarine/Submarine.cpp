#include <Submarine/Submarine.h>

#include <math.h>

using namespace std;
using json = nlohmann::json;

std::mutex Submarine::g_mutex;

Submarine::Submarine():
	stern("stern", Vector3D(0, -49, 0)),
	back("back", Vector3D(0, -30, 0)),
	center("center", Vector3D(0, -0, 0)),
	diving_plane("diving_plane", Vector3D(0, 0, 0)),
	front("front", Vector3D(0, 30, 0)),
	bow("bow", Vector3D(0, 49, 0)),
	air_tank(Tank::en_opening_type::CLOSED, 10),
	ballast(&air_tank, &water),
	compensating_tank_center(16, 0.5, "compensating_tank_center"),
	compensating_tank_front(10, 0.8, "compensating_tank_front"),
	compensating_tank_back(10, 0.8, "compensating_tank_back"),
	air_controller(&air_tank),
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
	
	air_tank.Fill(Air(), 3000);
	compensating_tank_back.Fill(5);
	compensating_tank_front.Fill(5);
	compensating_tank_center.Fill(8);
	
	AddComponent(&ballast);
	AddComponent(&compensating_tank_center);
	AddComponent(&compensating_tank_front);
	AddComponent(&compensating_tank_back);
	AddComponent(&thrust);
	AddComponent(&rudder);
	AddComponent(&diving_plane);
	AddComponent(&map);
	AddComponent(&air_controller);
	AddComponent(&simulation_control);
	
	compensating_tank_front.SetTwinCompensatingTank(&compensating_tank_back);
	compensating_tank_back.SetTwinCompensatingTank(&compensating_tank_front);
	
	// Submarine auto weighing
	double diving_mass = GetMass() + ballast.GetMassMax();
	double volume = GetVolume();
	double delta = volume * water.GetDensity() - diving_mass;
	back.SetMass(delta / 3);
	center.SetMass(delta / 3);
	front.SetMass(delta / 3);
	
	latitude = 48.308898557355235;
	longitude = -4.506347834823013;
	
	position.z = -6;
	water.SetPressure(1.6);
	ballast.FillAir();
}

Submarine::~Submarine()
{
}

double Submarine::GetMomentOfInertia() const
{
	return 90000000;
}

void Submarine::AddComponent(Component *component)
{
	component->submarine = this;
	components.insert(pair<string, Component *>(component->GetName(), component));
}

void Submarine::HandleCommand(const nlohmann::json &json)
{
	g_mutex.lock();
	
	auto it = components.find(json["component"]);
	if(it==components.end())
		return;
	
	it->second->HandleCommand(json);
	
	g_mutex.unlock();
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
