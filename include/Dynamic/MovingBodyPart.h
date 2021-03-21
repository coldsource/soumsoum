#ifndef _MOVINGBODYPART_H_
#define _MOVINGBODYPART_H_

#include <Vector/Vector3D.h>
#include <Volume/Volume.h>

#include <map>
#include <string>

class MovingBodyComponent;
class MovingBody;

class MovingBodyPart: virtual public Volume
{
	friend class MovingBody;

protected:
	MovingBody *moving_body = 0;
	std::string name;
	Vector3D position;
	double mass;
	
	std::vector<MovingBodyComponent *> components;
	
public:
	MovingBodyPart(const std::string &name, const Vector3D &position, double mass);
	
	Vector3D GetAbsolutePosition() const;
	Vector3D GetRelativePosition() const;
	const Vector3D &GetPosition() const { return position; }
	
	void AddComponent(MovingBodyComponent *component);
	
	double GetMass() const;
	void SetMass(double mass) { this->mass = mass; }
	
	std::map<std::string, Vector3D> GetForces() const;
};

#endif
