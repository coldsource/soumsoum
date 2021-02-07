#ifndef _MOVINGBODYPART_H_
#define _MOVINGBODYPART_H_

#include <Vector/Vector3D.h>
#include <Volume/Volume.h>

#include <vector>
#include <string>

class MovingBodyComponent;
class MovingBody;

class MovingBodyPart: virtual public Volume
{
	friend class MovingBody;

protected:
	std::string name;
	Vector3D position;
	double mass;
	
	std::vector<MovingBodyComponent *> components;
	
public:
	MovingBodyPart(const std::string &name, const Vector3D &position, double mass);
	
	void AddComponent(MovingBodyComponent *component);
	
	double GetMass() const;
};

#endif
