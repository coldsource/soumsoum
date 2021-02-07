#include <Submarine/Ballast.h>

using json = nlohmann::json;

Ballast::Ballast(Tank *air_source):
	tank(Tank::en_opening_type::BOTTOM, 650),
	fill_pump(water, 150, 0, &tank),
	empty_pump(air, 200, air_source, &tank)
{
	tank.Fill(air, 650);
}

void Ballast::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="fill")
	{
		tank.SetOpening(Tank::en_opening_type::TOP);
		empty_pump.Off();
		fill_pump.Transfer(650);
	}
	else if(j["action"]=="empty")
	{
		tank.SetOpening(Tank::en_opening_type::BOTTOM);
		fill_pump.Off();
		empty_pump.Transfer(650);
	}
}

json Ballast::ToJson() const
{
	json j;
	j["fill"] = tank.GetVolume(water) / tank.GetCapacity();
	return j;
}
