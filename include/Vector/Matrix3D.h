#ifndef _MATRIX3D_H_
#define _MATRIX3D_H_

#include <Vector/Vector3D.h>

#include <string>

class Matrix3D
{
	double M[3][3];
	
public:
	Matrix3D(double a00, double a01, double a02, double a10, double a11, double a12, double a20, double a21, double a22);
	
	double GetDet(void);
	void Invert(void);
	
	Matrix3D operator*(double d) const;
	Vector3D operator*(const Vector3D &v) const;
	
	Matrix3D &operator*=(double d);
	Matrix3D &operator+=(const Matrix3D &N);
	
	void Printf(const std::string &name) const;
};

#endif
