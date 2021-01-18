#ifndef _DRAG_H_
#define _DRAG_H_

#include <Vector/Vector3D.h>
#include <Dynamic/MovingBody.h>
#include <Fluid/Fluid.h>

class Drag: public Vector3D
{
public:
	Drag(const MovingBody &mb, const Fluid &f, const Vector3D &speed);
};

#endif
