#include "..\Include\Light.h"

Light::Light()
{
	for(int i = 0; i < 3; i++)
	{
		lightPosition[i] = 0.0f;
		lightAmbient[i] = 0.0f;
		lightDiffuse[i] = 1.0f;
		lightSpecular[i] = 1.0f;
	}

	attenuation_a = 1.0f;
	attenuation_b = 0.0f;
	attenuation_c = 0.0f;
}

Light::~Light()
{

}

void Light::setAttenuation(const float &a, const float &b, const float &c)
{
	attenuation_a = a;
	attenuation_b = b;
	attenuation_c = c;
}

void Light::setPosition(const float pos[3])
{
	for(int i = 0; i < 3; i++)
		this->lightPosition[i] = pos[i];
}

void Light::setPosition(const float &x, const float &y, const float &z)
{
	this->lightPosition[0] = x;
	this->lightPosition[1] = y;
	this->lightPosition[2] = z;
}

void Light::setAmbient(const float ambient[3])
{
	for(int i = 0; i < 3; i++)
	{
		lightAmbient[i] = ambient[i];
	}
}

void Light::setAmbient(const float &ambientR, const float &ambientG, const float &ambientB)
{
	lightAmbient[0] = ambientR;
	lightAmbient[1] = ambientG;
	lightAmbient[2] = ambientB;
}

void Light::setDiffuse(const float diffuse[3])
{
	for(int i = 0; i < 3; i++)
	{
		lightDiffuse[i] = diffuse[i];
	}
}

void Light::setDiffuse(const float &diffuseR, const float &diffuseG, const float &diffuseB)
{
	lightDiffuse[0] = diffuseR;
	lightDiffuse[1] = diffuseG;
	lightDiffuse[2] = diffuseB;
}

void Light::setSpecular(const float specular[3])
{
	for(int i = 0; i < 3; i++)
	{
		lightSpecular[i] = specular[i];
	}
}

void Light::setSpecular(const float &specularR, const float &specularG, const float &specularB)
{
	lightSpecular[0] = specularR;
	lightSpecular[1] = specularG;
	lightSpecular[2] = specularB;
}