#include <Dynamic/MovingBody.h>
#include <Dynamic/MovingBodyPart.h>
#include <Force/ArchimedesPrinciple.h>
#include <Force/Gravity.h>
#include <Force/Drag.h>
#include <Force/Lift.h>

#include <math.h>

using namespace std;
using json = nlohmann::json;

MovingBody::MovingBody(): map(this)
{
	double a = 6378137, f = 1/298.257223563; /* WGS84 */ 
	geod_init(&geod, a, f);
}

void MovingBody::AddPart(MovingBodyPart *part)
{
	part->moving_body = this;
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
		
		// Compute relative position in submarine
		Vector3D rel_position = part->GetRelativePosition();
		Vector3D abs_position = part->GetAbsolutePosition();
		
		// Compute relative and absolute speed (submarine speed + rotating linear speed)
		Vector3D rel_speed = rel_position ^ angular_speed;
		Vector3D abs_speed = speed + rel_speed * -1;
		
		// Automatic forces
		forces[part->name+"_ap"] = { rel_position, ArchimedesPrinciple(*part, water, -abs_position.z)};
		forces[part->name+"_gravity"] = { rel_position, Gravity(part->GetMass())};
		forces[part->name+"_drag"] = { rel_position, Drag(*part, water, attitude, abs_speed)};
		forces[part->name+"_lift"] = { rel_position, Lift(*part, water, attitude, abs_speed)};
		
		// Component forces
		auto component_forces = part->GetForces();
		for(auto it = component_forces.begin(); it!=component_forces.end(); ++it)
			forces[part->name+"_"+it->first] = {rel_position, it->second};
	}
	
	for(auto it = forces.begin();it!=forces.end(); ++it)
	{
		resulting_force += it->second.force;
		
		if(it->second.position.IsNull())
			continue; // Ignore forces applied to gravity center for torque
		
		resulting_torque += it->second.position ^ it->second.force;
	}
	
	Vector3D deltapos;
	
	acceleration = resulting_force / GetMass();
	speed += acceleration * dt;
	position += (deltapos = speed * dt);
	
	angular_acceleration = resulting_torque / GetMomentOfInertia();
	angular_speed += angular_acceleration * dt;
	
	Vector3D vattitude(0, 1, 0);
	vattitude.FromRG(attitude);
	vattitude.Rotate(angular_speed * dt);
	//vattitude.Printf("vattitude");
	
	vattitude.ToSpherical(0, &attitude.x, &attitude.z);
	
	//attitude += angular_speed * dt;
	
	double azimuth = 180/M_PI * atan2(deltapos.x, deltapos.y);
	double distance = sqrt(deltapos.x*deltapos.x + deltapos.y*deltapos.y);
	geod_direct(&geod, latitude, longitude, azimuth, distance, &latitude, &longitude, &azimuth);
}

double MovingBody::GetMass() const
{
	double mass = 0;
	
	for(auto it = parts.begin(); it!=parts.end(); ++it)
		mass += (*it)->GetMass();
	
	return mass;
}

double MovingBody::GetVolume() const
{
	double volume = 0;
	
	for(auto it = parts.begin(); it!=parts.end(); ++it)
		volume += (*it)->GetVolume();
	
	return volume;
}

json MovingBody::ToJson() const
{
	json j;
	
	j["acceleration"] = acceleration.ToJson();
	j["angular_acceleration"] = angular_acceleration.ToJson();
	j["angular_speed"] = angular_speed.ToJson();
	j["attitude"] = attitude.ToJson();
	
	j["compass"] = fmod((attitude.z/M_PI*180)+360, 360);
	j["speed"]["vertical"] = speed.z;
	j["speed"]["horizontal"] = sqrt(pow(speed.x, 2)+pow(speed.y, 2));
	
	json jforces;
	for(auto it = forces.begin(); it!=forces.end(); ++it)
		jforces[it->first] = it->second.force.ToJson(it->second.position);
	j["forces"] = jforces;
	
	return j;
}
