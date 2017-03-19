#ifndef _EXTERNAL_H
#define _EXTERNAL_H

#include "force.h"

class External : public Force
{
public:
	External(GVector3 _f, int _n, float existTime);
	virtual~External();

	virtual void SetForce(float _dt, Box *_b);
	virtual void initForce();
	bool Enable() { return b_Enable; };

private:
	GVector3 ex_f;
	int n;

	float CurrentTime;
	float ExistTime;
	bool  b_Enable;
};

#endif
