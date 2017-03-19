#pragma once
#include "MSForce.h"
#include "MSVector.h"


using namespace std;

class MSGravity : public MSForce
{
	// fixed �Ǿ��ִ� �ֵ� ���� ���� ������ ��ħ.
protected:
	MSVector2 m_vGravity;

	void Init();
public:
	MSGravity();
	MSGravity(const MSVector2& gravity);
	MSGravity(const MSGravity& gravity);

	virtual ~MSGravity(void);

	const MSVector2&	GetGravity()					{ return m_vGravity;	}
	void	SetGravity(MSVector2 &gravity)		{ m_vGravity = gravity;	}

	virtual void SetForce(float dTime);
	virtual void SetForce(float dTime, vector<MSParticle*> &particles);

	virtual void Render() {}
};

