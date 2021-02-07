#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include <nlohmann/json.hpp>

#include <string>

class Vector3D
{
public:
	double x = 0;
	double y = 0;
	double z = 0;
	
public:
	Vector3D();
	Vector3D(const Vector3D &v);
	Vector3D(double x, double y, double z);
	
	static Vector3D FromSpherical(double L, double x, double z);
	void ToSpherical(double *L, double *ax, double *az) const;
	
	bool IsNull() const;
	double GetNorm() const;
	
	void RotateX(double a);
	void RotateY(double a);
	void RotateZ(double a);
	
	void Printf(const std::string &name) const;
	void PrintfSpherical(const std::string &name) const;
	
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
