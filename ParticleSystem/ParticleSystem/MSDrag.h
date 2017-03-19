#pragma once
#include "MSForce.h"

class MSDrag : public MSForce
{
protected:
	MSParticle*	m_pParticle;
	float		m_fKDrag;

	void Init();
public:
	MSDrag(void);
	MSDrag(MSParticle* pP1, float fK);

	virtual ~MSDrag(void);

	void SetParticle(MSParticle* pP1)	{ if(pP1!=NULL) m_pParticle = pP1;}
	void SetkD(float kD)				{ m_fKDrag = kD;}

	const MSParticle* GetParticle()		{ return m_pParticle;}
	const float GetkD()					{ return m_fKDrag;}

	virtual void SetForce(float dTime);
	virtual void SetForce(float dTime, vector<MSParticle*> &particles);

	virtual void Render() {}
};

