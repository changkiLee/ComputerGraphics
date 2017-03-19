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
	dirLightPos[3] = 0;	// ���⼺ ����(����)
	lightNumber = num;

	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, attenuation_a);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, attenuation_b);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, attenuation_c);
	glLightfv(lightNumber, GL_POSITION, dirLightPos);		// ��ġ
	glLightfv(lightNumber, GL_AMBIENT, lightAmbient);		// �ֺ���
	glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);		// ���ݻ�
	glLightfv(lightNumber, GL_SPECULAR, lightSpecular);		// ���ݻ�

	glEnable(lightNumber);
}

void DirectionLight::lightOFF()
{
	glDisable(lightNumber);
}