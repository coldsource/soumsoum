#ifndef _TANK_H_
#define _TANK_H_

#include <nlohmann/json.hpp>

#include <Fluid/Fluid.h>

#include <map>

class Tank
{
public:
	enum en_opening_type { TOP, BOTTOM, CLOSED };
	
private:
	en_opening_type opening_type;
	double capacity;
	
	struct st_content { Fluid *fluid; double volume; };
	std::map<std::string, st_content> content;
	
public:
	Tank(en_opening_type opening_type, double capacity);
	
	void SetOpening(en_opening_type opening_type) { this->opening_type = opening_type; }
	
	double Fill(const Fluid &fluid, double volume);
	double Empty(const Fluid &fluid, double volume);
	
	double GetMass() const;
	double GetCapacity() const { return capacity; };
	double GetVolume(const Fluid &fluid) const;
	
	nlohmann::json ToJson() const;
};

#endif
