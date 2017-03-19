#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "..\Include\Common.h"

class Light
{
protected : 
	float attenuation_a;
	float attenuation_b;
	float attenuation_c;
	float lightPosition[3];		// 위치
	float lightAmbient[3];		// 주변광
	float lightDiffuse[3];		// 난반사
	float lightSpecular[3];		// 전반사
	GLenum lightNumber;			// 조명 번호

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