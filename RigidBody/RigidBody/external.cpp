#include "external.h"

External::External(GVector3 _f, int _n, float existTime)
{
	type = OTHER;
	ex_f = _f;
	n = _n;

	CurrentTime = 0.0f;
	ExistTime = existTime;
	b_Enable = true;
}

External::~External()
{

}

void External::SetForce(float _dt, Box *_b)
{
	CurrentTime += _dt;
	if( CurrentTime > ExistTime)
	{
		CurrentTime = ExistTime;
		b_Enable = false;
	}

	_b->addForce(_b->m * ex_f);
	_b->setType(n);
}

void External::initForce()
{
	ex_f = GVector3(0.0f, 0.0f, 0.0f);
}