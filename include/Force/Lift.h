#ifndef _LIFT_H_
#define _LIFT_H_

#include <Vector/Vector3D.h>
#include <Volume/Volume.h>
#include <Fluid/Fluid.h>

class Lift: public Vector3D
{
public:
	Lift(const Volume &v, const Fluid &f, const Vector3D &attitude, const Vector3D &speed);
};

#endif
