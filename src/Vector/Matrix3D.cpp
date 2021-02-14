#include <Vector/Matrix3D.h>

using namespace std;

Matrix3D::Matrix3D(double a00, double a01, double a02, double a10, double a11, double a12, double a20, double a21, double a22)
{
	M[0][0] = a00;
	M[0][1] = a01;
	M[0][2] = a02;
	
	M[1][0] = a10;
	M[1][1] = a11;
	M[1][2] = a12;
	
	M[2][0] = a20;
	M[2][1] = a21;
	M[2][2] = a22;
}

double Matrix3D::GetDet(void)
{
	double det = 0;
	
	det += M[0][0] * M[1][1] * M[2][2];
	det += M[0][1] * M[1][2] * M[2][0];
	det += M[0][2] * M[1][0] * M[2][1];
	det -= M[0][2] * M[1][1] * M[2][0];
	det -= M[1][2] * M[2][1] * M[0][0];
	det -= M[2][2] * M[0][1] * M[1][0];
	
	printf("det = %f\n", det);
	return det;
}

void Matrix3D::Invert(void)
{
	double det = GetDet();
	
	M[0][0] = (M[1][1]*M[2][2] - M[1][2]*M[2][1]) / det;
	M[0][1] = (M[0][2]*M[2][1] - M[0][1]*M[2][2]) / det;
	M[0][2] = (M[0][1]*M[1][2] - M[0][2]*M[1][1]) / det;
	M[1][0] = (M[1][2]*M[2][0] - M[1][0]*M[2][2]) / det;
	M[1][1] = (M[0][0]*M[2][2] - M[0][2]*M[2][0]) / det;
	M[1][2] = (M[0][2]*M[1][0] - M[0][0]*M[1][2]) / det;
	M[2][0] = (M[1][0]*M[2][1] - M[1][1]*M[2][0]) / det;
	M[2][1] = (M[0][1]*M[2][0] - M[0][0]*M[2][1]) / det;
	M[2][2] = (M[0][0]*M[1][1] - M[0][1]*M[1][0]) / det;
}

Matrix3D Matrix3D::operator*(double d) const
{
	Matrix3D M = *this;
	M*= d;
	
	return M;
}

Vector3D Matrix3D::operator*(const Vector3D &v) const
{
	Vector3D r;
	
	r.x = M[0][0] * v.x + M[0][1] * v.y + M[0][2] * v.z;
	r.y = M[1][0] * v.x + M[1][1] * v.y + M[1][2] * v.z;
	r.z = M[2][0] * v.x + M[2][1] * v.y + M[2][2] * v.z;
	
	return r;
}
	
Matrix3D &Matrix3D::operator*=(double d)
{
	for(int y=0;y<3;y++)
		for(int x=0;x<3;x++)
			M[y][x] *= d;
	
	return *this;
}

Matrix3D &Matrix3D::operator+=(const Matrix3D &N)
{
	for(int y=0;y<3;y++)
		for(int x=0;x<3;x++)
			M[y][x] += N.M[y][x];
	
	return *this;
}

void Matrix3D::Printf(const string &name) const
{
	string pad;
	pad.append(name.length()+3, ' ');
	printf("%s = ", name.c_str());
	for(int y=0;y<3;y++)
	{
		if(y>0)
			printf("%s", pad.c_str());
		for(int x=0;x<3;x++)
			printf("%f ", M[y][x]);
		printf("\n");
	}
}
