#ifndef _MOVINGBODYCOMPONENT_H_
#define _MOVINGBODYCOMPONENT_H_

#include <Vector/Vector3D.h>

#include <string>
#include <map>

class MovingBodyComponent
{
public:
	virtual double GetMass() const = 0;
	virtual std::map<std::string, Vector3D> GetForces() const { return std::map<std::string, Vector3D>(); }
};

#endif
