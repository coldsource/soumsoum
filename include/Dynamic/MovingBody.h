#ifndef _MOVINGBODY_H_
#define _MOVINGBODY_H_

#include <Vector/Vector3D.h>
#include <Volume/Volume.h>
#include <Force/Force.h>
#include <Fluid/Water.h>

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class MovingBodyPart;

class MovingBody
{
protected:
	Water water;
	
	Vector3D acceleration;
	Vector3D speed;
	Vector3D position;
	
	Vector3D angular_acceleration;
	Vector3D angular_speed;
	Vector3D attitude;
	
	std::vector<MovingBodyPart *> parts;
	
	struct st_force
	{
		Vector3D position;
		Vector3D force;
	};
	
	std::map <std::string, st_force> forces;
	
public:
	void AddPart(MovingBodyPart *part);
	
	void StepTime(double dt);
	
	double GetMass() const;
	
	virtual double GetMomentOfInertia() const = 0;
	
	const Vector3D &GetPosition() const { return position; }
	const Vector3D &GetSpeed() const { return speed; }
	const Vector3D &GetAcceleration() const { return acceleration; }
	const Vector3D &GetAttitude() const { return attitude; }
	const Vector3D &GetAngularSpeed() const { return angular_speed; }
	const Vector3D &GetAngularAcceleration() const { return angular_acceleration; }
	
	nlohmann::json ToJson() const;
	
};

#endif
