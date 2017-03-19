#include "Light.h"
#include <iostream>
using namespace std;

Light::Light()
{
	amb.SetVector(0.0, 0.0, 0.0);
	diff.SetVector(0.0, 0.0, 0.0);
	spec.SetVector(0.0, 0.0, 0.0);
	att.SetVector(0.0, 0.0, 0.0);
}

Light::~Light()
{

}

void Light::SetCat(int n)
{
	cat = n;
}

void Light::SetPosition(float x, float y, float z)
{
	position.SetVector(x, y, z);
}

void Light::SetAmb(float x, float y, float z)
{
	amb.SetVector(x, y, z);
}

void Light::SetDiff(float x, float y, float z)
{
	diff.SetVector(x, y, z);
}

void Light::SetSpec(float x, float y, float z)
{
	spec.SetVector(x, y, z);
}

void Light::SetAtt(float x, float y, float z)
{
	att.SetVector(x, y, z);
}

void Light::SetDirection(float x, float y, float z)
{
	direction.SetVector(x, y, z);
}

Vector Light::GetPosition()
{
	return position;
}

Vector Light::GetDirection()
{
	return direction;
}


Vector Light::GetAmb()
{
	return amb;
}

Vector Light::GetDiff()
{
	return diff;
}

Vector Light::GetSpec()
{
	return spec;
}

Vector Light::GetAtt()
{
	return att;
}

int Light::GetCat()
{
	return cat;
}