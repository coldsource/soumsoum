#ifndef _WEIGHING_H_
#define _WEIGHING_H_

#include <Simulation/SimulationStatus.h>
#include <Submarine/Component.h>

#include <string>

#include <nlohmann/json.hpp>

class Weighing:public Component, public SimulationStatus
{
public:
	Weighing();
	
	std::string GetName() const { return "weighing"; }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
