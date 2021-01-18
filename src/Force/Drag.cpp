#include <Force/Drag.h>

#include <math.h>

Drag::Drag(const MovingBody &mb, const Fluid &f, const Vector3D &speed)
{
	double surface = 8.8 * 99.5;
	x = ((speed.x>=0)?-1:1) * 0.5 * f.GetDensity() * surface * mb.GetDragCoefficient() * speed.x * speed.x;
	y = ((speed.y>=0)?-1:1) * 0.5 * f.GetDensity() * surface * mb.GetDragCoefficient() * speed.y * speed.y;
	z = ((speed.z>=0)?-1:1) * 0.5 * f.GetDensity() * surface * mb.GetDragCoefficient() * speed.z * speed.z;
}
