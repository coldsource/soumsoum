#ifndef _DIVINGPLANE_H_
#define _DIVINGPLANE_H_

#include <Dynamic/MovingBodyPart.h>
#include <Submarine/Component.h>

#include <nlohmann/json.hpp>

class DivingPlane:public MovingBodyPart, public Component
{
	const double Cz = -0.6;
	double tilt = 0;

public:
	DivingPlane(const std::string name, const Vector3D &position):MovingBodyPart(name, position, 0) {};
	
	double GetVolume() const { return 0; }
	double GetImmersedVolume(double depth) const { return 0; };
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const;
	void GetCx(Vector3D *positive, Vector3D *negative) const;
	double GetCz() const;
	
	void HandleCommand(const nlohmann::json &j);
	
	nlohmann::json ToJson() const;
};

#endif
