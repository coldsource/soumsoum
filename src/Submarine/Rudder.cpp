#include <Submarine/Rudder.h>
#include <Submarine/Submarine.h>

#include <math.h>

using json = nlohmann::json;
using namespace std;

Rudder::Rudder()
{
}

map<string, Vector3D> Rudder::GetForces() const
{
	map<string, Vector3D> forces;
	
	const Vector3D attitude = moving_body->GetAttitude();
	
	Vector3D rel_speed = moving_body->GetSpeed();
	rel_speed.ToRG(moving_body->GetAttitude());
	
	Vector3D rudder(angle_z * force * rel_speed.y, 0, angle_x * force * rel_speed.y);
	rudder.FromRG(moving_body->GetAttitude());
	
	forces["rudder"] = rudder;
	
	return forces;
}

void Rudder::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="angle_x_neutral")
		targeted_angle_x = 0;
	else if(j["action"]=="angle_x_minus")
		targeted_angle_x = M_PI/12.0;
	else if(j["action"]=="angle_x_plus")
		targeted_angle_x = -M_PI/12.0;
	else if(j["action"]=="angle_z_neutral")
		targeted_angle_z = 0;
	else if(j["action"]=="angle_z_minus")
		targeted_angle_z = -M_PI/12.0;
	else if(j["action"]=="angle_z_plus")
		targeted_angle_z = M_PI/12.0;
}

void Rudder::StepTime(double dt)
{
	variable_sim(&angle_x, targeted_angle_x, angle_rate, dt);
	variable_sim(&angle_z, targeted_angle_z, angle_rate, dt);
}

json Rudder::ToJson() const
{
	json j;
	j["angle_x"] = angle_x / M_PI * 180;
	j["angle_z"] = angle_z / M_PI * 180;
	
	return j;
}
