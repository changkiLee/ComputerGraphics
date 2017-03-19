#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "..\Include\Common.h"

class Light
{
protected : 
	float attenuation_a;
	float attenuation_b;
	float attenuation_c;
	float lightPosition[3];		// ��ġ
	float lightAmbient[3];		// �ֺ���
	float lightDiffuse[3];		// ���ݻ�
	float lightSpecular[3];		// ���ݻ�
	GLenum lightNumber;			// ���� ��ȣ

public :
	Light();
	virtual ~Light();

	void setAttenuation(const float &a, const float &b, const float &c);
	void setPosition(const float pos[3]);
	void setPosition(const float &x, const float &y, const float &z);
	void setAmbient(const float ambient[3]);
	void setAmbient(const float &ambientR, const float &ambientG, const float &ambientB);
	void setDiffuse(const float diffuse[3]);
	void setDiffuse(const float &diffuseR, const float &diffuseG, const float &diffuseB);
	void setSpecular(const float specular[3]);
	void setSpecular(const float &specularR, const float &specularG, const float &specularB);
	
	virtual void lightON(GLenum num) = 0;
	virtual void lightOFF() = 0;
};

#endif