#ifndef _THRUST_H_
#define _THRUST_H_

#include <Submarine/Component.h>

#include <nlohmann/json.hpp>

class Thrust: public Component
{
	double angle_x = 0;
	double angle_z = 0;
	double rate = 0;
	
public:
	Thrust();
	
	double GetMass() const { return 0; }
	double GetAngleX() const { return angle_x; }
	double GetAngleZ() const { return angle_z; }
	double GetForce() const { return 3000000 * rate; }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
