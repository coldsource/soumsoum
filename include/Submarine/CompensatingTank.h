#ifndef _COMPENSATINGTANK_H_
#define _COMPENSATINGTANK_H_

#include <Submarine/Component.h>
#include <Submarine/Tank.h>
#include <Submarine/Pump.h>
#include <Fluid/Water.h>

class CompensatingTank: public Component
{
	Water water;
	
	Tank tank;
	Pump fill_pump;
	Pump empty_pump;
	
public:
	CompensatingTank(double capacity, double flow);
	
	double GetMass() const { return tank.GetMass(); }
	double Fill(double volume) { return tank.Fill(water, volume); }
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
