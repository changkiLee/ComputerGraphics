#include "Vector.h"
#include "math.h"
#include <iostream>
using namespace std;

Vector::Vector()
{
	_x = 0.0;
	_y = 0.0;
	_z = 0.0;
}

Vector::~Vector()
{

}

Vector::Vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}


Vector::Vector(const Vector& a)
{
	_x = a._x;
	_y = a._y;
	_z = a._z;
}

void Vector::SetVector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector Vector::CalD(const Vector &u, const Vector &v, const Vector &o, int i, int j)
{
	Vector d;
	d._x = u._x*i + v._x*j + o._x;
	d._y = u._y*i + v._y*j + o._y;
	d._z = u._z*i + v._z*j + o._z;
	return d;
}

Vector Vector::Cross(const Vector& a)
{
	Vector c;
	c._x = _y * a._z - _z * a._y;
	c._y = _z * a._x - _x * a._z;
	c._z = _x * a._y - _y * a._x;
	return c;
}

Vector Vector::Normalise()
{
	Vector c(_x, _y, _z);
	return c/c.Norm();
}

float Vector::Dot(const Vector& a)
{
	return _x*a._x + _y*a._y + _z*a._z;
}

float Vector::Norm()
{
	float n = _x * _x + _y * _y + _z * _z;
	return sqrt(n);
}

float Vector::GetX()
{
	return _x;
}

float Vector::GetY()
{
	return _y;
}

float Vector::GetZ()
{
	return _z;
}

Vector Vector::Mult(const Vector& a)
{
	Vector tmp(_x*a._x, _y*a._y, _z*a._z);
	return tmp;
}

Vector Vector::operator/(float n)
{
	Vector tmp(_x/n, _y/n, _z/n);
	return tmp;
}

void Vector::VecPrint()
{
	cout << "(" << _x << ", " << _y << ", " << _z << ")" << endl;
}