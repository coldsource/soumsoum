#ifndef _GRAVITY_H_
#define _GRAVITY_H_

#include <Vector/Vector3D.h>
#include <Fluid/Volume.h>

class Gravity: public Vector3D
{
public:
	Gravity(double mass);
};

#endif
