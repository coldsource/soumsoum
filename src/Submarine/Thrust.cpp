#include <Submarine/Thrust.h>
#include <Submarine/Submarine.h>

#include <math.h>

using json = nlohmann::json;
using namespace std;

Thrust::Thrust()
{
	this->submarine = submarine;
}

map<string, Vector3D> Thrust::GetForces() const
{
	map<string, Vector3D> forces;
	
	const Vector3D attitude = moving_body->GetAttitude();
	
	Vector3D thrust(0, GetForce(), 0);
	thrust.RotateX(angle_x);
	thrust.RotateZ(angle_z);
	thrust.FromRG(attitude);
	
	forces["thrust"] = thrust;
	
	return forces;
}

void Thrust::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="angle_x_neutral")
	{
		angle_x = 0;
	}
	else if(j["action"]=="angle_x_minus")
	{
		angle_x = M_PI/12.0;
	}
	else if(j["action"]=="angle_x_plus")
	{
		angle_x = -M_PI/12.0;
	}
	else if(j["action"]=="angle_z_neutral")
	{
		angle_z = 0;
	}
	else if(j["action"]=="angle_z_minus")
	{
		angle_z = -M_PI/12.0;
	}
	else if(j["action"]=="angle_z_plus")
	{
		angle_z = M_PI/12.0;
	}
	else if(j["action"]=="rate_minus")
	{
		targeted_rate -= 0.1;
		if(targeted_rate<0)
			targeted_rate = 0;
	}
	else if(j["action"]=="rate_plus")
	{
		targeted_rate += 0.1;
		if(targeted_rate>1)
			targeted_rate = 1;
	}
}

void Thrust::StepTime(double dt)
{
	if(targeted_rate==rate)
		return;
	
	if(rate<targeted_rate)
	{
		rate += rate_second * dt;
		if(rate>targeted_rate)
			rate = targeted_rate;
	}
	
	if(rate>targeted_rate)
	{
		rate -= rate_second * dt;
		if(rate<targeted_rate)
			rate = targeted_rate;
	}
}

json Thrust::ToJson() const
{
	json j;
	j["thrust"]["angle_x"] = angle_x;
	j["thrust"]["angle_z"] = angle_z;
	j["thrust"]["rate"] = rate;
	j["thrust"]["targeted_rate"] = targeted_rate;
	
	return j;
}
