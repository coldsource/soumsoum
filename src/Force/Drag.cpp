#include <Force/Drag.h>

#include <math.h>

Drag::Drag(const Volume &v, const Fluid &f, const Vector3D &attitude, const Vector3D &speed)
{
	if(speed.IsNull())
		return;
	
	Vector3D CxP, CxN;
	v.GetCx(&CxP, &CxN);
	
	Vector3D SP, SN;
	v.GetContactSurfaces(&SP, &SN);
	
	Vector3D incident_speed = speed;
	incident_speed.ToRG(attitude);
	
	Vector3D coef = 1 + 500 / (500 * incident_speed * incident_speed + 1);
	
	double density = f.GetDensity();
	if(incident_speed.x > 0)
		x += 0.5 * density * SP.x * CxP.x * pow(incident_speed.x, 2) * coef.x;
	if(incident_speed.x < 0)
		x += 0.5 * density * SN.x * CxN.x * pow(incident_speed.x, 2) * coef.x;
	if(incident_speed.y > 0)
		y += 0.5 * density * SP.y * CxP.y * pow(incident_speed.y, 2) * coef.y;
	if(incident_speed.y < 0)
		y += 0.5 * density * SN.y * CxN.y * pow(incident_speed.y, 2) * coef.y;
	if(incident_speed.z > 0)
		z += 0.5 * density * SP.z * CxP.z * pow(incident_speed.z, 2) * coef.z;
	if(incident_speed.z < 0)
		z += 0.5 * density * SN.z * CxN.z * pow(incident_speed.z, 2) * coef.z;
	
	if(incident_speed.x>=0)
		x *= -1;
	if(incident_speed.y>=0)
		y *= -1;
	if(incident_speed.z>=0)
		z *= -1;
	
	FromRG(attitude);
}
