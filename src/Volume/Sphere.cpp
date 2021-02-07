#include <Volume/Sphere.h>

#include <math.h>

Sphere::Sphere(double radius)
{
	this->radius = radius;
}

double Sphere::GetVolume() const
{
	return 4.0/3.0 * M_PI * pow(radius,3);
}

double Sphere::GetImmersedVolume(double depth) const
{
	if(depth<0)
		depth = 0;
	
	if(depth>2*radius)
		depth = 2*radius;
	
	return (M_PI * pow(depth,2) * (3 * radius - depth)) / 3;
}

void Sphere::GetContactSurfaces(Vector3D *positive, Vector3D *negative) const
{
	negative->x = positive->x = M_PI * radius * radius;
	negative->y = positive->y = M_PI * radius * radius;
	negative->z = positive->z = M_PI * radius * radius;
}

void Sphere::GetCx(Vector3D *positive, Vector3D *negative) const
{
	negative->x = positive->x = 0.35;
	negative->y = positive->y = 0.35;
	negative->z = positive->z = 0.35;
}
