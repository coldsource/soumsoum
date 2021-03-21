#ifndef _DIOXYGEN_H_
#define _DIOXYGEN_H_

#include <Fluid/Fluid.h>

#include <string>

class Dioxygen: public Fluid
{
public:
	std::string GetName() const { return "dioxygen"; }
	double GetDensity() const;
	bool IsCompressible() const { return true; }
	
	Dioxygen *clone() const { return new Dioxygen(); }
};

#endif
