#include <Dynamic/MovingBody.h>
#include <Dynamic/MovingBodyPart.h>

#include <Force/ArchimedesPrinciple.h>
#include <Force/Gravity.h>
#include <Force/Drag.h>
#include <Force/Lift.h>

#include <math.h>

using namespace std;
using json = nlohmann::json;

void MovingBody::AddPart(MovingBodyPart *part)
{
	parts.push_back(part);
}

void MovingBody::StepTime(double dt)
{
	Vector3D resulting_force;
	Vector3D resulting_torque;
	
	// Compute Archimede's and Gravity forces
	for(auto it = parts.begin(); it!=parts.end(); ++it)
	{
		MovingBodyPart *part = *it;
		
		Vector3D rel_position;
		if(part->distance>=0)
			rel_position = Vector3D::FromSpherical(part->distance, attitude.x, attitude.z);
		else
			rel_position = Vector3D::FromSpherical(-part->distance, attitude.x + M_PI, attitude.z);
		
		Vector3D abs_position = position + rel_position;
		
		Vector3D rel_speed = rel_position * angular_speed;
		Vector3D abs_speed = speed + rel_speed * -1;
		
		forces[part->name+"_ap"] = { rel_position, ArchimedesPrinciple(*part, water, -abs_position.z)};
		forces[part->name+"_gravity"] = { rel_position, Gravity(part->GetMass())};
		forces[part->name+"_drag"] = { rel_position, Drag(*part, water, attitude, abs_speed)};
		forces[part->name+"_lift"] = { rel_position, Lift(*part, water, attitude, abs_speed)};
	}
	
	for(auto it = forces.begin();it!=forces.end(); ++it)
	{
		resulting_force += it->second.force;
		resulting_torque += it->second.position * it->second.force;
	}
	
	acceleration = resulting_force / GetMass();
	speed += acceleration * dt;
	position += speed * dt;
	
	angular_acceleration = resulting_torque / GetMomentOfInertia();
	angular_speed += angular_acceleration * dt;
	attitude += angular_speed * dt;
}

double MovingBody::GetMass() const
{
	double mass = 0;
	
	for(auto it = parts.begin(); it!=parts.end(); ++it)
		mass += (*it)->GetMass();
	
	return mass;
}

json MovingBody::ToJson() const
{
	json j;
	
	j["acceleration"] = acceleration.ToJson();
	j["speed"] = speed.ToJson();
	j["position"] = position.ToJson();
	j["attitude"] = attitude.ToJson();
	
	json jforces;
	for(auto it = forces.begin(); it!=forces.end(); ++it)
		jforces[it->first] = it->second.force.ToJson(it->second.position);
	j["forces"] = jforces;
	
	return j;
}
