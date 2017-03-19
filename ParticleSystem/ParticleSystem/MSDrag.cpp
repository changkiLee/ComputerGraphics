#include "MSDrag.h"
#include <Windows.h>

MSDrag::MSDrag(void) : MSForce(DRAG)
{
	m_pParticle = NULL;
	m_fKDrag = 0.0f;
}

MSDrag::MSDrag(MSParticle* pP1, float fK) : MSForce(DRAG)
{
	m_pParticle = pP1;
	m_fKDrag = fK;
}

MSDrag::~MSDrag(void)
{
}

void MSDrag::SetForce(float dTime)
{
	if( m_pParticle!=NULL)
	{
		MSVector2 velo = m_pParticle->GetVelocity();

		m_pParticle->AddForce(velo * (-m_fKDrag) );

	}
	

}

void MSDrag::SetForce(float dTime, vector<MSParticle*> &particles)
{

}