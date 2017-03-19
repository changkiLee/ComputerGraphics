#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_
#include "..\Include\Common.h"
#include "..\Include\Light.h"

class PointLight : public Light
{
private : 

public :
	PointLight();
	virtual ~PointLight();

	void lightON(GLenum num);
	void lightOFF();
};

#endif
