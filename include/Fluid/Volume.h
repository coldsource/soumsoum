#ifndef _VOLUME_H_
#define _VOLUME_H_

class Volume
{
public:
	virtual double GetVolume() const = 0;
	virtual double GetImmersedVolume() const = 0;
	virtual double GetMass() const = 0;
	virtual double GetMomentOfInertia() const = 0;
	virtual double GetDragCoefficient() const = 0;
};

#endif
