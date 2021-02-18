#include <Force/Lift.h>

#include <math.h>

Lift::Lift(const Volume &v, const Fluid &f, const Vector3D &attitude, const Vector3D &speed)
{
	if(speed.IsNull())
		return;
	
	double Cz =  v.GetCz();
	if(!Cz)
		return;
	
	Vector3D SP, SN;
	v.GetContactSurfaces(&SP, &SN);
	
	Vector3D incident_speed = speed;
	incident_speed.ToRG(attitude);
	
	double density = f.GetDensity();
	if(incident_speed.y > 0)
		z = 0.5 * density * (SP.z+SN.z) * Cz * pow(incident_speed.y, 2);
	
	FromRG(attitude);
}
