#include <Submarine/CompensatingTank.h>

using json = nlohmann::json;
using namespace std;

CompensatingTank::CompensatingTank(double capacity, double flow, const string &name):
	tank(Tank::en_opening_type::CLOSED, capacity, 0),
	fill_pump(water, flow, 0, &tank),
	empty_pump(water, flow, &tank, 0)
{
	this->name = name;
	this->flow = flow;
}

void CompensatingTank::SetTwinCompensatingTank(CompensatingTank *twin_tank)
{
	fill_pump = Pump(water, flow, &twin_tank->tank, &tank);
	empty_pump = Pump(water, flow, &tank, &twin_tank->tank);
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
	j["volume"] = tank.GetVolume(water);
	j["flow"] = flow * fill_pump.GetRate();
	
	return j;
}
