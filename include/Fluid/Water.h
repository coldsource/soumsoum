#ifndef _WATER_H_
#define _WATER_H_

#include <Fluid/Fluid.h>

#include <string>

class Water: public Fluid
{
public:
	std::string GetName() const { return "water"; }
	double GetDensity() const;
	bool IsCompressible() const { return false; }
	
	Water *clone() const { return new Water(); }
};

#endif
