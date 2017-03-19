#include "Object.h"
#include <iostream>
using namespace std;

Object::Object()
{
	cat = 0;
	rad = 0.0;
	coef_a = 0.0; coef_b = 0.0; coef_c = 0.0; coef_d = 0.0;
	shn = 0;
	refl = 0.0; refr = 0.0; idxr = 0.0;
	cent.SetVector(0.0, 0.0, 0.0);
	amb.SetVector(0.0, 0.0, 0.0);
	diff.SetVector(0.0, 0.0, 0.0);
	spec.SetVector(0.0, 0.0, 0.0);
}

Object::~Object()
{

}

void Object::SetCat(int n)
{
	cat = n;
}

void Object::SetRad(float r)
{
	rad = r;
}

void Object::SetCoef(float a, float b, float c, float d)
{
	coef_a = a; coef_b = b; coef_c = c; coef_d = d;
}

void Object::SetShn(int s)
{
	shn = s;
}

void Object::SetRef(float _refl, float _refr, float _idxr)
{
	refl = _refl; refr = _refr; idxr = _idxr;
}

void Object::SetCent(float x, float y, float z)
{
	cent.SetVector(x, y, z);
}

void Object::SetAmb(float x, float y, float z)
{
	amb.SetVector(x, y, z);
}

void Object::SetDiff(float x, float y, float z)
{
	diff.SetVector(x, y, z);
}

void Object::SetSpec(float x, float y, float z)
{
	spec.SetVector(x, y, z);
}

Vector Object::GetCent()
{
	return cent;
}

Vector Object::GetPlaneNorm()
{
	Vector tmp(coef_a, coef_b, coef_c);
	return tmp;
}

float Object::GetD()
{
	return coef_d;
}

float Object::GetRad()
{
	return rad;
}

float Object::GetRefl()
{
	return refl;
}

float Object::GetRefr()
{
	return refr;
}

float Object::GetIdxr()
{
	return idxr;
}

Vector Object::GetAmb()
{
	return amb;
}

Vector Object::GetDiff()
{
	return diff;
}

Vector Object::GetSpec()
{
	return spec;
}

int Object::GetShn()
{
	return shn;
}