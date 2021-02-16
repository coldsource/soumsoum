#include <Submarine/CompensatingTank.h>

using json = nlohmann::json;
using namespace std;

CompensatingTank::CompensatingTank(double capacity, double flow, const string &name):
	tank(Tank::en_opening_type::CLOSED, capacity),
	fill_pump(water, flow, 0, &tank),
	empty_pump(water, flow, &tank, 0)
{
	this->name = name;
}

void CompensatingTank::HandleCommand(const json &j)
{
	if(j["action"]=="pumpRateChange")
	{
		fill_pump.SetRate(j["rate"]);
		empty_pump.SetRate(j["rate"]);
	}
	else if(j["action"]=="emptyPumpOn")
		empty_pump.On();
	else if(j["action"]=="emptyPumpOff")
		empty_pump.Off();
	else if(j["action"]=="fillPumpOn")
		fill_pump.On();
	else if(j["action"]=="fillPumpOff")
		fill_pump.Off();
}

json CompensatingTank::ToJson() const
{
	json j;
	j["rate"] = fill_pump.GetRate();
	j["capacity"] = tank.GetCapacity();
	j["volume"] = tank.GetMass() / water.GetDensity();
	
	return j;
}
