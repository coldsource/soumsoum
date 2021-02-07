#ifndef _SUBMARINESTERN_H_
#define _SUBMARINESTERN_H_

#include <Volume/Sphere.h>

class SubmarineStern:public MovingBodyPart, public Sphere
{
public:
	SubmarineStern(const std::string name, const Vector3D &position):MovingBodyPart(name, position, 137392.318717), Sphere(4) {};
	
	double GetVolume() const { return Sphere::GetVolume() / 2.0; }
	double GetImmersedVolume(double depth) const { return Sphere::GetImmersedVolume(depth) / 2.0; }
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const
	{
		Sphere::GetContactSurfaces(positive, negative);
		positive->x = negative->x = positive->x / 2;
		positive->z = negative->z = positive->z / 2;
	}
	void GetCx(Vector3D *positive, Vector3D *negative) const
	{
		Sphere::GetCx(positive, negative);
		positive->y = 0;
	}
};

#endif
