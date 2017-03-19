#include "..\Include\PointLight.h"

PointLight::PointLight() : Light(){}

PointLight::~PointLight()
{
}

void PointLight::lightON(GLenum num)
{
	float pointLightPos[4];
	for(int i = 0; i < 3; i++)
		pointLightPos[i] = lightPosition[i];
	pointLightPos[3] = 1;	// 점 광원(포인트)

	lightNumber = num;

	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, attenuation_a);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, attenuation_b);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, attenuation_c);
	glLightfv(lightNumber, GL_POSITION, pointLightPos);	// 위치
	glLightfv(lightNumber, GL_AMBIENT, lightAmbient);	// 주변광
	glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);	// 난반사
	glLightfv(lightNumber, GL_SPECULAR, lightSpecular);	// 전반사

	glEnable(lightNumber);
}

void PointLight::lightOFF()
{
	glDisable(lightNumber);
}