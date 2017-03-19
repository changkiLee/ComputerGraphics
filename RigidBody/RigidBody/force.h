#ifndef _FORCE_H
#define _FORCE_H

#include "gmath.h"
#include "box.h"

class Force
{
public:
	enum FORCE_TYPE {
		GRAVITY = 0,
		OTHER
	};

	FORCE_TYPE type;

public:
	Force();
	Force(Force &r);
	virtual ~Force();

	virtual void SetForce(float _dt, Box *_b) = 0;
	virtual void initForce() = 0;
	FORCE_TYPE GetType() { return type;}
};

#endif
