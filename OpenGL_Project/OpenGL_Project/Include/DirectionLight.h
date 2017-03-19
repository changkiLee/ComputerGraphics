#ifndef _DIRECTIONLIGHT_H_
#define _DIRECTIONLIGHT_H_
#include "..\Include\Common.h"
#include "..\Include\Light.h"

class DirectionLight : public Light
{
private : 

public :
	DirectionLight();
	virtual ~DirectionLight();

	void lightON(GLenum num);
	void lightOFF();
};

#endif
