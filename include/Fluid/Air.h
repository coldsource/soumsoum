#ifndef _AIR_H_
#define _AIR_H_

#include <Fluid/Fluid.h>

#include <string>

class Air: public Fluid
{
public:
	std::string GetName() const { return "air"; }
	double GetDensity() const;
	bool IsCompressible() const { return true; }
	
	Air *clone() const { return new Air(); }
};

#endif
