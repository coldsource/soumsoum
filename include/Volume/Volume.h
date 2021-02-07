#ifndef _VOLUME_H_
#define _VOLUME_H_

#include <Vector/Vector3D.h>

class Volume
{
public:
	virtual double GetVolume() const = 0;
	virtual double GetImmersedVolume(double depth) const = 0;
	virtual void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const = 0;
	virtual void GetCx(Vector3D *positive, Vector3D *negative) const = 0;
};

#endif
