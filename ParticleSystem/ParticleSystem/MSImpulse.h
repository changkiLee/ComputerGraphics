#pragma once
#include "MSForce.h"
class MSImpulse : public MSForce
{
private:
	MSVector2 m_vForce;
	float m_fExistTime; // 힘이 존재하는 시간. 점점 감소하게 된다...
	float m_fCurrentTime;
	bool  m_bEnable;

public:
	MSImpulse(MSVector2 &vForce, float existTime);
	virtual ~MSImpulse(void);

	virtual void SetForce(float dTime){}
	virtual void SetForce(float dTime, vector<MSParticle*> &particles);

	bool Enable() { return m_bEnable; }

	virtual void Render(){}
	const MSVector2& GetForce() { return m_vForce; }
};

