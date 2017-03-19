#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_
#include "..\Include\Common.h"
#include "..\Include\Light.h"

class SpotLight : public Light
{
private : 
	// 집중광원 요소
	float spotDir[3];
	float cutOff;
	float exponent;

public :
	SpotLight();
	virtual ~SpotLight();

	void setSpotDirection(const float dir[3]);
	void setSpotDirection(const float &x, const float &y, const float &z);
	void setCutOff(const float &coff);
	void setExponent(const float &exp);

	void lightON(GLenum num);
	void lightOFF();
};

#endif
