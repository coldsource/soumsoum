#include <Submarine/Crew.h>
#include <Exception/GameOver.h>

using json = nlohmann::json;

constexpr int Crew::members;

Crew::Crew():
	o2_tank(Tank::en_opening_type::CLOSED, 1, 230),
	co2_tank(Tank::en_opening_type::CLOSED, 1, 230),
	regeneration(dioxygen, 0.01, 0, &o2_tank)
{
	o2_tank.Fill(dioxygen, 200);
	
	update_resolution = 10;
}

void Crew::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="empty_waste")
		waste = 0;
	else if(j["action"]=="empty_co2")
		co2_tank.Empty(carbon_dioxide);
	else if(j["action"]=="regeneration_on")
		regeneration.On();
	else if(j["action"]=="regeneration_off")
		regeneration.Off();
	
	Invalidate();
}

void Crew::StepTime(double dt)
{
	o2_tank.Empty(dioxygen, breath_rate * members * dt);
	co2_tank.Fill(carbon_dioxide, breath_rate * members * dt);
	
	supplies -= eat_rate * members * dt;
	waste += waste_rate * members * dt;
	
	if(supplies<=0)
		throw GameOver(0, "You ran out of supplies for your crew");
	
	if(waste>500)
		throw GameOver(0, "Your crew was overrun by waste");
	
	if(o2_tank.GetVolume(dioxygen)==0)
		throw GameOver(0, "No more dioxygen available, your crew died");
}

nlohmann::json Crew::ToJson() const
{
	json j;
	
	j["crew"] = members;
	j["o2_tank"] = o2_tank.ToJson();
	j["regeneration"] = regeneration.IsOn()?"on":"off";
	j["co2_tank"] = co2_tank.ToJson();
	j["supplies"] = supplies;
	j["supplies_autonomy"] = supplies / eat_rate / 86400 / members;
	j["waste"] = waste;
	
	return j;
}
