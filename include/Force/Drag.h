#ifndef _DRAG_H_
#define _DRAG_H_

#include <Vector/Vector3D.h>
#include <Volume/Volume.h>
#include <Fluid/Fluid.h>

class Drag: public Vector3D
{
public:
	Drag(const Volume &v, const Fluid &f, const Vector3D &attitude, const Vector3D &speed);
};

#endif
