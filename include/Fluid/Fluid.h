#ifndef _FLUID_H_
#define _FLUID_H_

#include <string>

class Fluid
{
public:
	virtual ~Fluid() {};
	
	virtual std::string GetName() const = 0;
	virtual double GetDensity() const = 0;
	virtual bool IsCompressible() const = 0;
	
	virtual Fluid *clone() const = 0;
};

#endif
