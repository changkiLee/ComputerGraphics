#include "gravity.h"

Gravity::Gravity()
{
	type = GRAVITY;
	g = GVector3(0.0f, -9.8f, 0.0f);
}

Gravity::Gravity(GVector3 _g)
{
	type = GRAVITY;
	g = _g;
}

Gravity::~Gravity()
{

}

void Gravity::SetForce(float _dt, Box *_b)
{
	_b->addForce(_b->m * g);
}

void Gravity::initForce()
{
	//g = GVector3(0.0f, 0.0f, 0.0f);
}