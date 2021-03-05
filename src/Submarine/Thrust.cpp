#include <Submarine/Thrust.h>
#include <Submarine/Submarine.h>

#include <math.h>

using json = nlohmann::json;
using namespace std;

constexpr double Thrust::max_force[2];
constexpr double Thrust::rate_second[2];

Thrust::Thrust()
{
}

double Thrust::GetForce(en_propulsion_type type) const
{
	if(type==CURRENT)
		type = this->type;
	
	return max_force[type] * rate[type];
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
	if(j["action"]=="ctrlMinus" || j["action"]=="ctrlPlus")
	{
		en_propulsion_type type = this->type;
		if(j["type"]=="ELECTRIC")
			type = ELECTRIC;
		else if(j["type"]=="MECHANICAL")
			type = MECHANICAL;
		
		if(j["action"]=="ctrlMinus")
		{
			rate_ctrl[type] -= 0.1;
			if(rate_ctrl[type]<0)
				rate_ctrl[type] = 0;
		}
		else if(j["action"]=="ctrlPlus")
	{
		rate_ctrl[type] += 0.1;
		if(rate_ctrl[type]>1)
			rate_ctrl[type] = 1;
	}
	}
	else if(j["action"]=="setType")
	{
		if(j["type"]=="ELECTRIC")
		{
			type = ELECTRIC;
			targeted_rate[MECHANICAL] = 0;
		}
		else if(j["type"]=="MECHANICAL")
		{
			type = MECHANICAL;
			targeted_rate[ELECTRIC] = 0;
		}
	}
	else if(j["action"]=="setSteam")
	{
		if(j["dst"]=="GENERATOR")
			steam = GENERATOR;
		else if(j["dst"]=="TURBINE")
			steam = TURBINE;
		else
			steam = NONE;
	}
}

void Thrust::StepTime(double dt)
{
	// Engine
	targeted_rate[ELECTRIC] = rate_ctrl[ELECTRIC];
	targeted_rate[MECHANICAL] = rate_ctrl[MECHANICAL];
	if(battery==0)
		targeted_rate[ELECTRIC] = 0;
	if(steam!=TURBINE)
		targeted_rate[MECHANICAL] = 0;
	
	variable_sim(&rate[ELECTRIC], targeted_rate[ELECTRIC], rate_second[ELECTRIC], dt);
	variable_sim(&rate[MECHANICAL], targeted_rate[MECHANICAL], rate_second[MECHANICAL], dt);
	
	// Battery
	battery_rate = 0;
	if(steam==GENERATOR)
		battery_rate += battery_charge;
	battery_rate += battery_discharge * rate[ELECTRIC];
	
	double battery_target = battery_rate<=0?0:1;
	variable_sim(&battery, battery_target, abs(battery_rate), dt);
}

json Thrust::ToJson() const
{
	json j;
	j["type"] = type==ELECTRIC?"ELECTRIC":"MECHANICAL";
	if(steam==GENERATOR)
		j["steam"] = "GENERATOR";
	else if(steam==TURBINE)
		j["steam"] = "TURBINE";
	else
		j["steam"] = "NONE";
	j["CURRENT"]["ctrl"] = rate_ctrl[type];
	j["CURRENT"]["rate"] = rate[type];
	j["CURRENT"]["targeted_rate"] = targeted_rate[type];
	j["ELECTRIC"]["ctrl"] = rate_ctrl[ELECTRIC];
	j["ELECTRIC"]["rate"] = rate[ELECTRIC];
	j["ELECTRIC"]["targeted_rate"] = targeted_rate[ELECTRIC];
	j["ELECTRIC"]["force"] = GetForce(ELECTRIC);
	j["ELECTRIC"]["battery"] = battery;
	j["ELECTRIC"]["battery_rate"] = battery_rate;
	j["MECHANICAL"]["ctrl"] = rate_ctrl[MECHANICAL];
	j["MECHANICAL"]["rate"] = rate[MECHANICAL];
	j["MECHANICAL"]["targeted_rate"] = targeted_rate[MECHANICAL];
	j["MECHANICAL"]["force"] = GetForce(MECHANICAL);
	
	return j;
}
