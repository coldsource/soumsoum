#include <Submarine/Thrust.h>

#include <math.h>

using json = nlohmann::json;

Thrust::Thrust()
{
}

void Thrust::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="angle_x_neutral")
	{
		angle_x = 0;
	}
	else if(j["action"]=="angle_x_minus")
	{
		angle_x = -M_PI/12.0;
	}
	else if(j["action"]=="angle_x_plus")
	{
		angle_x = M_PI/12.0;
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
		rate -= 0.1;
		if(rate<0)
			rate = 0;
	}
	else if(j["action"]=="rate_plus")
	{
		rate += 0.1;
		if(rate>1)
			rate = 1;
	}
}

json Thrust::ToJson() const
{
	json j;
	j["angle_x"] = angle_x;
	j["angle_z"] = angle_z;
	j["rate"] = rate;
	return j;
}
