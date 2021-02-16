#include <Submarine/Thrust.h>
#include <Submarine/Submarine.h>

#include <math.h>

using json = nlohmann::json;
using namespace std;

Thrust::Thrust()
{
}

map<string, Vector3D> Thrust::GetForces() const
{
	map<string, Vector3D> forces;
	
	const Vector3D attitude = moving_body->GetAttitude();
	
	Vector3D thrust(0, GetForce(), 0);
	thrust.FromRG(attitude);
	
	forces["thrust"] = thrust;
	
	return forces;
}

void Thrust::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="rate_minus")
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
	variable_sim(&rate, targeted_rate, rate_second, dt);
}

json Thrust::ToJson() const
{
	json j;
	j["rate"] = rate;
	j["targeted_rate"] = targeted_rate;
	
	return j;
}
