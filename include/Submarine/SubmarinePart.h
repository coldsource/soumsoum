#ifndef _SUBMARINEPART_H_
#define _SUBMARINEPART_H_

#include <Volume/Cylinder.h>

class SubmarinePart:public MovingBodyPart, public Cylinder
{
public:
	SubmarinePart(const std::string name, const Vector3D &position):MovingBodyPart(name, position, 1323580.25224 ), Cylinder(4, 30) {};
	void GetCx(Vector3D *positive, Vector3D *negative) const
	{
		Cylinder::GetCx(positive, negative);
		negative->y = positive->y = 0;
	}
};

#endif
