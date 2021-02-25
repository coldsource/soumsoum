#ifndef _FLUID_H_
#define _FLUID_H_

#include <string>

class Fluid
{
protected:
	double pressure = 1;
	
public:
	virtual ~Fluid() {};
	
	virtual std::string GetName() const = 0;
	virtual double GetDensity() const = 0;
	virtual bool IsCompressible() const = 0;
	
	void SetPressure(double pressure) { this->pressure = pressure; }
	double GetPressure() const { return pressure; }
	
	virtual Fluid *clone() const = 0;
};

#endif
