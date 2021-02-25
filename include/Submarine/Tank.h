#ifndef _TANK_H_
#define _TANK_H_

#include <nlohmann/json.hpp>

#include <Simulation/SimulationObject.h>
#include <Fluid/Fluid.h>

#include <map>

class Tank: public SimulationObject
{
public:
	enum en_opening_type { TOP, BOTTOM, CLOSED };
	
private:
	en_opening_type opening_type;
	const Fluid *external_fluid;
	
	double capacity;
	
	struct st_content { Fluid *fluid; double volume; };
	std::map<std::string, st_content> content;
	
	void balance();
	
public:
	Tank(en_opening_type opening_type, double capacity, const Fluid *external_fluid = 0);
	
	void SetOpening(en_opening_type opening_type);
	
	double Fill(const Fluid &fluid, double volume);
	double Empty(const Fluid &fluid, double volume);
	
	double GetMass() const;
	double GetCapacity() const { return capacity; };
	double GetVolume(const Fluid &fluid) const;
	double GetPressure() const;
	en_opening_type GetOpening() const { return opening_type; }
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
