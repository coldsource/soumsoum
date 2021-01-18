#ifndef _MOVINGBODY_H_
#define _MOVINGBODY_H_

#include <Vector/Vector3D.h>
#include <Fluid/Volume.h>
#include <Force/Force.h>

#include <map>
#include <string>

#include <nlohmann/json.hpp>

class MovingBody:public Volume
{
protected:
	Vector3D acceleration;
	Vector3D speed;
	Vector3D position;
	
	Vector3D angular_acceleration;
	Vector3D angular_speed;
	Vector3D attitude;
	
	struct st_force
	{
		Vector3D position;
		Vector3D force;
	};
	
	std::map <std::string, st_force> forces;
	
public:
	void StepTime(double dt);
	
	const Vector3D &GetPosition() const { return position; }
	const Vector3D &GetSpeed() const { return speed; }
	const Vector3D &GetAcceleration() const { return acceleration; }
	const Vector3D &GetAttitude() const { return attitude; }
	
	nlohmann::json ToJson() const;
	
};

#endif
