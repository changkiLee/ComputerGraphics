#include "..\Include\DirectionLight.h"

DirectionLight::DirectionLight() : Light(){}

DirectionLight::~DirectionLight()
{
}

void DirectionLight::lightON(GLenum num)
{
	float dirLightPos[4];
	for(int i = 0; i < 3; i++)
		dirLightPos[i] = lightPosition[i];
	dirLightPos[3] = 0;	// 방향성 광원(벡터)
	lightNumber = num;

	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, attenuation_a);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, attenuation_b);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, attenuation_c);
	glLightfv(lightNumber, GL_POSITION, dirLightPos);		// 위치
	glLightfv(lightNumber, GL_AMBIENT, lightAmbient);		// 주변광
	glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);		// 난반사
	glLightfv(lightNumber, GL_SPECULAR, lightSpecular);		// 전반사

	glEnable(lightNumber);
}

void DirectionLight::lightOFF()
{
	glDisable(lightNumber);
}