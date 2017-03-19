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
	pointLightPos[3] = 1;	// �� ����(����Ʈ)

	lightNumber = num;

	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, attenuation_a);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, attenuation_b);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, attenuation_c);
	glLightfv(lightNumber, GL_POSITION, pointLightPos);	// ��ġ
	glLightfv(lightNumber, GL_AMBIENT, lightAmbient);	// �ֺ���
	glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);	// ���ݻ�
	glLightfv(lightNumber, GL_SPECULAR, lightSpecular);	// ���ݻ�

	glEnable(lightNumber);
}

void PointLight::lightOFF()
{
	glDisable(lightNumber);
}