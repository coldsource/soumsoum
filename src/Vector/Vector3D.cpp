#include <Vector/Vector3D.h>
#include <Vector/Matrix3D.h>

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
	double N = GetNorm();
	
	if(x==0 && y==0)
	{
		*ax = z>=0?M_PI/2:-M_PI/2;
		*az = 0;
	}
	else
	{
		*ax = M_PI / 2.0 - acos(z / N);
		*az = M_PI / 2.0 - atan2(y,x);
	}
	
	if(L)
		*L = N;
}

bool Vector3D::IsNull() const
{
	return x==0 && y==0 && z==0;
}

double Vector3D::GetNorm() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::GetUnit() const
{
	double n = GetNorm();
	return Vector3D(x / n, y / n, z / n);
}

void Vector3D::RotateX(double a)
{
	a *= -1;
	
	double yr = cos(a) * y + sin(a) * z;
	double zr = -sin(a) * y + cos(a) * z;
	
	y = yr;
	z = zr;
}

void Vector3D::RotateY(double a)
{
	double xr = cos(a) * x -sin(a) * z;
	double zr = sin(a) * x + cos(a) * z;
	
	x = xr;
	z = zr;
}

void Vector3D::RotateZ(double a)
{
	double xr = cos(a) * x + sin(a) * y;
	double yr = -sin(a) * x + cos(a) * y;
	
	x = xr;
	y = yr;
}

void Vector3D::Rotate(const Vector3D &r)
{
	Rotate(r, r.GetNorm());
}

void Vector3D::Rotate(const Vector3D &nr, double a)
{
	if(nr.IsNull())
		return;
	
	Vector3D r = nr.GetUnit();
	
	Matrix3D M = Matrix3D(1, 0, 0, 0, 1, 0, 0, 0, 1) * cos(a);
	M += Matrix3D(r.x*r.x, r.x*r.y, r.x*r.z, r.x*r.y, r.y*r.y, r.y*r.z, r.x*r.z, r.y*r.z, r.z*r.z) * (1-cos(a));
	M += Matrix3D(0, -r.z, r.y, r.z, 0, -r.x, -r.y, r.x, 0) * sin(a);
	
	*this = M*(*this);
}

void Vector3D::FromRG(const Vector3D &attitude)
{
	RotateX(attitude.x);
	RotateZ(attitude.z);
}

void Vector3D::ToRG(const Vector3D &attitude)
{
	RotateZ(-attitude.z);
	RotateX(-attitude.x);
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

Vector3D Vector3D::operator^(const Vector3D &v) const
{
	Vector3D r = *this;
	r ^= v;
	
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

Vector3D &Vector3D::operator^=(const Vector3D &v)
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

nlohmann::json Vector3D::ToJsonDeg() const
{
	json j;
	j["x"] = x/M_PI*180;
	j["y"] = y/M_PI*180;
	j["z"] = z/M_PI*180;
	
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
