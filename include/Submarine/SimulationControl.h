#ifndef _SIMULATIONCONTROL_H_
#define _SIMULATIONCONTROL_H_

#include <Simulation/SimulationStatus.h>
#include <Submarine/Component.h>

#include <string>

#include <nlohmann/json.hpp>

class SimulationControl:public Component, public SimulationStatus
{
	int time_compression_step = 0;
	int time_compression_steps[6] = {1, 2, 5, 10, 50, 100};

public:
	std::string GetName() const { return "simulation_control"; }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
