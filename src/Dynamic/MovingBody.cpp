#include <Dynamic/MovingBody.h>

using namespace std;
using json = nlohmann::json;

void MovingBody::StepTime(double dt)
{
	Vector3D resulting_force;
	Vector3D resulting_torque;
	
	printf("***\n");
	printf("Angular speed : %f\n",angular_speed.x);
	for(auto it = forces.begin();it!=forces.end(); ++it)
	{
		resulting_force += it->second.force;
		resulting_torque += it->second.position * it->second.force;
		
		printf("%s %f\n",it->first.c_str(), it->second.force.z);
	}
	
	acceleration = resulting_force / GetMass();
	speed += acceleration * dt;
	position += speed * dt;
	
	angular_acceleration = resulting_torque / GetMomentOfInertia() * -1;
	angular_speed += angular_acceleration * dt;
	attitude += angular_speed * dt;
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
