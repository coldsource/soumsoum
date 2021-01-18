#include <Vector/Vector3D.h>

#include <math.h>

using json = nlohmann::json;

Vector3D::Vector3D()
{
	;
}

Vector3D::Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::FromNormAngle(double L, double x, double z)
{
	return Vector3D(L*cos(x)*sin(z), L*cos(x)*cos(z), -L*cos(x)*tan(x));
}

double Vector3D::GetNorm() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::operator+(const Vector3D &v) const
{
	return Vector3D(x+v.x, y+v.y, z+v.z);
}

Vector3D Vector3D::operator*(double d) const
{
	Vector3D v = *this;
	v *= d;
	
	return v;
}

Vector3D Vector3D::operator*(const Vector3D &v) const
{
	Vector3D r = *this;
	r *= v;
	
	return r;
}

Vector3D Vector3D::operator/(double d) const
{
	Vector3D v = *this;
	v /= d;
	
	return v;
}

Vector3D &Vector3D::operator*=(double d)
{
	x *= d;
	y *= d;
	z *= d;
	
	return *this;
}

Vector3D &Vector3D::operator*=(const Vector3D &v)
{
	double nx = y*v.z - z*v.y;
	double ny = z*v.x - x*v.z;
	double nz = x*v.y - y*v.x;
	
	this->x = nx;
	this->y = ny;
	this->z = nz;
	
	return *this;
}

Vector3D &Vector3D::operator+=(const Vector3D &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	
	return *this;
}

Vector3D &Vector3D::operator/=(double d)
{
	x /= d;
	y /= d;
	z /= d;
	
	return *this;
}

Vector3D &Vector3D::operator=(const Vector3D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	
	return *this;
}

nlohmann::json Vector3D::ToJson() const
{
	json j;
	j["x"] = x;
	j["y"] = y;
	j["z"] = z;
	j["norm"] = GetNorm();
	
	return j;
}

nlohmann::json Vector3D::ToJson(double x0, double y0, double z0) const
{
	json j = ToJson();
	j["x0"] = x0;
	j["y0"] = y0;
	j["z0"] = z0;
	
	return j;
}

nlohmann::json Vector3D::ToJson(const Vector3D &position) const
{
	json j = ToJson();
	j["x0"] = position.x;
	j["y0"] = position.y;
	j["z0"] = position.z;
	
	return j;
}
