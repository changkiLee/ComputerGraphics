#include "MSImpulse.h"


MSImpulse::MSImpulse(MSVector2 &vForce, float existTime) : MSForce(IMPULSE)
{

	m_vForce = vForce;
	m_fExistTime = existTime;
	m_fCurrentTime = 0.0f;
	m_bEnable = true;
}


MSImpulse::~MSImpulse(void)
{
}


void MSImpulse::SetForce(float dTime, vector<MSParticle*> &particles)
{
	m_fCurrentTime += dTime;
	if( m_fCurrentTime > m_fExistTime)
	{
		m_fCurrentTime = m_fExistTime;
		m_bEnable = false;
	}
	MSVector2 vForce = MSVector2::Vec2Lerp(m_vForce, MSVector2(0,0), m_fCurrentTime/m_fExistTime);

	for(vector<MSParticle*>::iterator itor = particles.begin(); itor != particles.end(); itor++)
	{
		float mass = (*itor)->GetMass();
		(*itor)->AddForce( vForce * mass);
	}
}