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
	// Check if we are in the water
	const Vector3D abs_pos = GetAbsolutePosition();
	if(abs_pos.z>0)
		return 0;
	
	return Cz*tilt;
}

void DivingPlane::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="dive")
	{
		targeted_tilt += 0.1;
		if(targeted_tilt>1)
			targeted_tilt = 1;
	}
	else if(j["action"]=="surface")
	{
		targeted_tilt -= 0.1;
		if(targeted_tilt<-0.5)
			targeted_tilt = -0.5;
	}
	else if(j["action"]=="neutral")
		targeted_tilt = 0;
}

void DivingPlane::StepTime(double dt)
{
	variable_sim(&tilt, targeted_tilt, tilt_second, dt);
}

json DivingPlane::ToJson() const
{
	json j;
	
	j["diving_plane"]["tilt"] = tilt*10;
	j["diving_plane"]["targeted_tilt"] = targeted_tilt;
	
	return j;
}
