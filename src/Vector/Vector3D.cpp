#include <Vector/Vector3D.h>

#include <math.h>

using json = nlohmann::json;

Vector3D::Vector3D()
{
}

Vector3D::Vector3D(const Vector3D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3D::Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::FromSpherical(double L, double x, double z)
{
	return Vector3D(L*cos(x)*sin(z), L*cos(x)*cos(z), L*sin(x));
}

void Vector3D::ToSpherical(double *L, double *ax, double *az) const
{
	*L = GetNorm();
	
	if(x==0 && y==0)
	{
		*ax = z>=0?M_PI/2:-M_PI/2;
		*az = 0;
	}
	else
	{
		*ax = M_PI / 2.0 - acos(z / *L);
		*az = M_PI / 2.0 - atan2(y,x);
	}
}

bool Vector3D::IsNull() const
{
	return x==0 && y==0 && z==0;
}

double Vector3D::GetNorm() const
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3D::RotateX(double a)
{
	a *= -1;
	y = cos(a) * y + sin(a) * z;
	z = -sin(a) * y + cos(a) * z;
}

void Vector3D::RotateY(double a)
{
	x = cos(a) * x -sin(a) * z;
	z = sin(a) * x + cos(a) * z;
}

void Vector3D::RotateZ(double a)
{
	a *= -1;
	x = cos(a) * x + sin(a) * y;
	y = -sin(a) * x + cos(a) * y;
}

void Vector3D::Printf(const std::string &name) const
{
	printf("%s = (%f, %f, %f)\n",name.c_str(), x, y, z);
}

void Vector3D::PrintfSpherical(const std::string &name) const
{
	double L, ax, az;
	ToSpherical(&L, &ax, &az);
	printf("%s = {%f, %f, %f}\n",name.c_str(), L, ax, az);
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
