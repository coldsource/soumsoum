#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <Volume/Volume.h>

class Sphere:virtual public Volume
{
	double radius;
	
public:
	Sphere(double radius);
	
	double GetVolume() const;
	double GetImmersedVolume(double depth) const;
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const;
	void GetCx(Vector3D *positive, Vector3D *negative) const;
};

#endif
