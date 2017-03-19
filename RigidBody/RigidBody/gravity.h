#ifndef _GRAVITY_H
#define _GRAVITY_H

#include "force.h"

class Gravity : public Force
{
public:
	Gravity();
	Gravity(GVector3 _g);
	virtual~Gravity();

	virtual void SetForce(float _dt, Box *_b);
	virtual void initForce();

private:
	GVector3 g;
};

#endif
