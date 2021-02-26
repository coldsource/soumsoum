#include <Submarine/SimulationControl.h>
#include <Submarine/Submarine.h>

using nlohmann::json;

void SimulationControl::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="compressTime")
	{
		time_compression_step++;
		if(time_compression_step>=sizeof(time_compression_steps)/sizeof(int))
			time_compression_step = sizeof(time_compression_steps)/sizeof(int) - 1;
		
		submarine->SetTimeCompression(time_compression_steps[time_compression_step]);
	}
	else if(j["action"]=="uncompressTime")
	{
		time_compression_step--;
		if(time_compression_step<0)
			time_compression_step = 0;
		
		submarine->SetTimeCompression(time_compression_steps[time_compression_step]);
	}
	else if(j["action"]=="simulationRateLimitOn")
		submarine->SetSimulationRateLimit(true);
	else if(j["action"]=="simulationRateLimitOff")
		submarine->SetSimulationRateLimit(false);
}

json SimulationControl::ToJson() const
{
	json j;
	
	j["time_compression"] = time_compression_steps[time_compression_step];
	j["rate_limit"] = submarine->GetSimulationRateLimit();
		
	return j;
}
