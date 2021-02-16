#ifndef _DIVINGPLANE_H_
#define _DIVINGPLANE_H_

#include <Simulation/SimulationObject.h>
#include <Simulation/SimulationStatus.h>
#include <Dynamic/MovingBodyPart.h>
#include <Submarine/Component.h>

#include <nlohmann/json.hpp>

class DivingPlane:public MovingBodyPart, public Component, public SimulationObject, public SimulationStatus
{
	const double Cz = -0.6;
	
	double tilt = 0;
	double targeted_tilt = 0;
	double tilt_second = 0.25;

public:
	DivingPlane(const std::string name, const Vector3D &position):MovingBodyPart(name, position, 0) {};
	
	std::string GetName() const { return "diving_plane"; }
	
	double GetVolume() const { return 0; }
	double GetImmersedVolume(double depth) const { return 0; };
	void GetContactSurfaces(Vector3D *positive, Vector3D *negative) const;
	void GetCx(Vector3D *positive, Vector3D *negative) const;
	double GetCz() const;
	
	void HandleCommand(const nlohmann::json &j);
	
	void StepTime(double dt);
	
	nlohmann::json ToJson() const;
};

#endif
