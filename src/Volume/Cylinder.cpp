#include <Volume/Cylinder.h>

#include <math.h>

Cylinder::Cylinder(double radius, double length)
{
	this->radius = radius;
	this->length = length;
}
	
double Cylinder::GetVolume() const
{
	return M_PI * pow(radius, 2) * length;
}

double Cylinder::GetImmersedVolume(double depth) const
{
	if(depth<0)
		depth = 0;
	
	if(depth>2*radius)
		depth = 2*radius;
	
	return length * (pow(radius,2) * acos(1 - depth / radius) - (radius - depth) * sqrt(depth * (2 * radius - depth)));
}

void Cylinder::GetContactSurfaces(Vector3D *positive, Vector3D *negative) const
{
	negative->x = positive->x =  2 * radius * length;
	negative->y = positive->y = M_PI * radius * radius;
	negative->z = positive->z =  2 * radius * length;
}

void Cylinder::GetCx(Vector3D *positive, Vector3D *negative) const
{
	negative->x = positive->x = 0.5;
	negative->y = positive->y = 1;
	negative->z = positive->z = 0.5;
}
