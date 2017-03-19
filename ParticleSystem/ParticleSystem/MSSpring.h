#pragma once

#include "MSForce.h"

class MSSpring : public MSForce
{
// 지정된 두 객체만 영향을 미침.
protected:
	MSParticle* m_pP1;
	MSParticle* m_pP2;
	/*
	int m_iIndex1;
	int m_iIndex2;
	*/
	float m_fkD;
	float m_fkS;

	float m_fInitDistance;

	void Init();
	void SetInitDistance();
public:
	MSSpring();
	MSSpring(MSParticle* pP1, MSParticle* pP2, float kD, float kS);
	//MSSpring(int index1, int index2, float kD, float kS);
	MSSpring(MSSpring& spring);
	virtual ~MSSpring(void);
	//void SetInitDistance(vector<MSParticle> &particles);
	
	void SetParticle1(MSParticle* pP1)						{ if(pP1!=NULL) m_pP1 = pP1;}
	void SetParticle2(MSParticle* pP2)						{ if(pP2!=NULL) m_pP2 = pP2;}
	void SetParticles(MSParticle* pP1, MSParticle* pP2);
	
	void SetkD(float kD)									{ m_fkD = kD;}
	void SetkS(float kS)									{ m_fkS = kS;}

	
	const MSParticle* GetParticle1(MSParticle* pP1)				{ return m_pP1;}
	const MSParticle* GetParticle2(MSParticle* pP2)				{ return m_pP2;}
	
	const float GetkD(float kD)									{ return m_fkD;}
	const float GetkS(float kS)									{ return m_fkS;}

	virtual void SetForce(float dTime);
	virtual void SetForce(float dTime, vector<MSParticle*> &particles) {}

	virtual void Render();

	MSSpring& operator=(const MSSpring& spring);
};

