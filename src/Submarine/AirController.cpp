#include <Submarine/AirController.h>
#include <Submarine/Submarine.h>

using json = nlohmann::json;

AirController::AirController(Tank *air_tank):
	surface_fill(air, 2, 0, air_tank)
{
	this->air_tank = air_tank;
}

void AirController::StepTime(double dt)
{
	if(submarine->GetPosition().z<-8)
		surface_fill.Off();
}

void AirController::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="surfaceFillOn")
	{
		if(submarine->GetPosition().z>-8)
			surface_fill.On();
	}
	else if(j["action"]=="surfaceFillOff")
		surface_fill.Off();
	
}

json AirController::ToJson() const
{
	json j;
	
	j["main_tank"] = air_tank->ToJson();
	j["surface_fill"] = surface_fill.IsOn()?"on":"off";
	
	return j;
}
