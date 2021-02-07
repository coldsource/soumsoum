#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include <Volume/Volume.h>

class Cylinder:virtual public Volume
{
	double radius;
	double length;
	
public:
	Cylinder(double radius, double length);
	
	double GetVolume() const;
	double GetImmersedVolume(double depth) const;
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const;
	void GetCx(Vector3D *positive, Vector3D *negative) const;
};

#endif
