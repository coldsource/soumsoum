#include <Submarine/Ballast.h>

using json = nlohmann::json;

Ballast::Ballast(Tank *air_source, const Fluid *water_source):
	tank(Tank::en_opening_type::BOTTOM, volume, 0, water_source),
	fill_pump(water, 15, 0, &tank),
	empty_pump(air, 20, air_source, &tank)
{
}

void Ballast::FillAir()
{
	tank.Fill(air, volume * 2);
}

void Ballast::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="open")
	{
		tank.SetOpening(Tank::en_opening_type::TOP);
		empty_pump.Off();
		fill_pump.Transfer(volume);
	}
	else if(j["action"]=="close")
	{
		tank.SetOpening(Tank::en_opening_type::BOTTOM);
		fill_pump.Off();
	}
	else if(j["action"]=="air_pump_on")
	{
		empty_pump.On();
	}
	else if(j["action"]=="air_pump_off")
	{
		empty_pump.Off();
	}
}

json Ballast::ToJson() const
{
	json j;
	j["fill"] = tank.GetVolume(water) / tank.GetCapacity();
	j["pressure"] = tank.GetPressure();
	j["air_pump"] = empty_pump.IsOn()?"on":"off";
	j["opened"] = tank.GetOpening()==Tank::en_opening_type::TOP?true:false;
	return j;
}
