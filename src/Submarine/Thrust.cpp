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
	
	forces["thrust"] = { Vector3D::FromSpherical(GetForce(), attitude.x + GetAngleX(), attitude.z + GetAngleZ())};
	
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
	j["angle_x"] = angle_x;
	j["angle_z"] = angle_z;
	j["rate"] = rate;
	j["targeted_rate"] = targeted_rate;
	return j;
}
