#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include <nlohmann/json.hpp>

class Vector3D
{
public:
	double x = 0;
	double y = 0;
	double z = 0;
	
public:
	Vector3D();
	Vector3D(double x, double y, double z);
	
	static Vector3D FromNormAngle(double L, double x, double z);
	
	double GetNorm() const;
	
	Vector3D operator+(const Vector3D &v) const;
	Vector3D operator*(double d) const;
	Vector3D operator*(const Vector3D &v) const;
	Vector3D operator/(double d) const;
	
	Vector3D &operator+=(const Vector3D &v);
	Vector3D &operator*=(double d);
	Vector3D &operator*=(const Vector3D &v);
	Vector3D &operator/=(double d);
	
	Vector3D &operator=(const Vector3D &v);
	
	nlohmann::json ToJson() const;
	nlohmann::json ToJson(double x0, double y0, double z0) const;
	nlohmann::json ToJson(const Vector3D &position) const;
};

#endif
