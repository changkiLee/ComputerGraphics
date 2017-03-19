#pragma once

#include <Windows.h>
#include "MSParticle.h"
#include <vector>
using namespace std;

class MSForce
{
public:
	enum FORCE_TYPE {
		GRAVITY = 0,
		DRAG,
		SPRING,
		IMPULSE,
		FORCE_END
	};
protected:
	FORCE_TYPE	m_ForceType;
	void Init();

public:
	MSForce(void);
	MSForce(FORCE_TYPE forceType);

	virtual ~MSForce(void);

	virtual void SetForce(float dTime) = 0;
	virtual void SetForce(float dTime, vector<MSParticle*> &particles) = 0;

	FORCE_TYPE GetType() { return m_ForceType;}

	virtual void Render() = 0;
};

