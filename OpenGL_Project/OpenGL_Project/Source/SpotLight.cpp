#include "..\Include\SpotLight.h"

SpotLight::SpotLight() : Light()
{
	spotDir[0] = spotDir[1] = spotDir[2] = 0.0;
	cutOff = 60.0;
	exponent = 128.0;
}

SpotLight::~SpotLight()
{
}

void SpotLight::setSpotDirection(const float dir[3])
{
	for(int i = 0; i < 3; i++)
		spotDir[i] = dir[i];
}

void SpotLight::setSpotDirection(const float &x, const float &y, const float &z)
{
	spotDir[0] = x;
	spotDir[1] = y;
	spotDir[2] = z;
}

void SpotLight::setCutOff(const float &coff)
{
	cutOff = coff;
}

void SpotLight::setExponent(const float &exp)
{
	exponent = exp;
}

void SpotLight::lightON(GLenum num)
{
	float spotLightPos[4];
	for(int i = 0; i < 3; i++)
		spotLightPos[i] = lightPosition[i];
	spotLightPos[3] = 1;	// 점 광원(포인트)

	lightNumber = num;

	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, attenuation_a);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, attenuation_b);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, attenuation_c);
	glLightfv(lightNumber, GL_POSITION, spotLightPos);	// 위치
	glLightfv(lightNumber, GL_AMBIENT, lightAmbient);	// 주변광
	glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);	// 난반사
	glLightfv(lightNumber, GL_SPECULAR, lightSpecular);	// 전반사

	glLightfv(lightNumber, GL_SPOT_DIRECTION, spotDir);
	glLightf(lightNumber, GL_SPOT_CUTOFF, cutOff);
	glLightf(lightNumber, GL_SPOT_EXPONENT, exponent);

	glEnable(lightNumber);
}

void SpotLight::lightOFF()
{
	glDisable(lightNumber);
}