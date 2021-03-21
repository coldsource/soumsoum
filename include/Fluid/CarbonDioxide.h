#ifndef _CARBONDIOXIDE_H_
#define _CARBONDIOXIDE_H_

#include <Fluid/Fluid.h>

#include <string>

class CarbonDioxide: public Fluid
{
public:
	std::string GetName() const { return "carbon_dioxide"; }
	double GetDensity() const;
	bool IsCompressible() const { return true; }
	
	CarbonDioxide *clone() const { return new CarbonDioxide(); }
};

#endif
