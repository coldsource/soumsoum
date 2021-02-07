#include <Submarine/DivingPlane.h>

#include <math.h>

using nlohmann::json;

void DivingPlane::GetContactSurfaces(Vector3D *positive, Vector3D *negative) const
{
	negative->x = positive->x = 2*0.3;
	negative->y = positive->y = abs(3 * 2 * sin(tilt));
	negative->z = positive->z = 3*2;
}

void DivingPlane::GetCx(Vector3D *positive, Vector3D *negative) const
{
	negative->x = positive->x = 0;
	negative->y = positive->y = 0.2;
	negative->z = positive->z = 0.7;
}

double DivingPlane::GetCz() const
{
	return Cz*tilt;
}

void DivingPlane::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="dive")
	{
		tilt += 0.1;
		if(tilt>1)
			tilt = 1;
	}
	else if(j["action"]=="surface")
	{
		tilt -= 0.1;
		if(tilt<-0.5)
			tilt = -0.5;
	}
	else if(j["action"]=="neutral")
		tilt = 0;
}

json DivingPlane::ToJson() const
{
	json j;
	
	j["tilt"] = tilt;
	
	return j;
}
