#include "MSSpring.h"
#include <GL\glut.h>
MSSpring::MSSpring()
{
	
}

MSSpring::MSSpring(MSParticle* pP1, MSParticle* pP2, float kD, float kS)
{
	m_ForceType = SPRING;
	m_pP1 = pP1;
	m_pP2 = pP2;
	m_fkD = kD;
	m_fkS = kS;

	SetInitDistance();

}

/*
MSSpring::MSSpring(int index1, int index2, float kD, float kS)
{
	m_ForceType = SPRING;
	m_iIndex1 = index1;
	m_iIndex2 = index2;
	m_fkD = kD;
	m_fkS = kS;

	//SetInitDistance();


}
*/

MSSpring::MSSpring(MSSpring& spring)
{
	m_ForceType = SPRING;
	
	m_pP1 = spring.m_pP1;
	m_pP2 = spring.m_pP2;
	m_fkD = spring.m_fkD;
	m_fkS = spring.m_fkS;

	SetInitDistance();
}

MSSpring::~MSSpring(void)
{

}

void MSSpring::Init()
{
	MSForce::Init();
	m_ForceType = SPRING;
	
	m_pP1 = NULL;
	m_pP2 = NULL;
	

	m_fkD = 0.0f;
	m_fkS = 0.0f;
}
void MSSpring::SetInitDistance( /*vector<MSParticle> &particles*/)
{
	/*
	MSVector2 vP1 = particles[m_iIndex1].GetPosition();
	MSVector2 vP2 = particles[m_iIndex2].GetPosition();
	m_fInitDistance = MSVector2::Vec2GetDistance(vP1, vP2);
	*/
	
	if( (m_pP1!= NULL) && (m_pP2!= NULL) )
	{
		MSVector2 vP1 = m_pP1->GetPosition();
		MSVector2 vP2 = m_pP2->GetPosition();
		m_fInitDistance = MSVector2::Vec2GetDistance(vP1, vP2);
	}
	else 
		m_fInitDistance = 0.0f;
	
}


void MSSpring::SetParticles(MSParticle* pP1, MSParticle* pP2)
{
	if( pP1 != NULL)
		m_pP1 = pP1;
	if( pP2 != NULL)
		m_pP2 = pP2;

	SetInitDistance();
}
void MSSpring::SetForce(float dTime)
{
	MSVector2 vP1 = m_pP1->GetPosition();
	MSVector2 vP2 = m_pP2->GetPosition();

	MSVector2 vDelta = vP1 - vP2;
	float deltaLength = MSVector2::Vec2GetLength(vDelta);

	MSVector2 vV1 = m_pP1->GetVelocity();
	MSVector2 vV2 = m_pP2->GetVelocity();
	MSVector2 vDeltaVelo = vV1 - vV2;

	MSVector2 vUnitDelta;
	if( deltaLength < 0.1e-10)
		vUnitDelta = vDelta;
	else
		vUnitDelta = vDelta / deltaLength;

	float vDeltaVelo_dot_UnitDelta = MSVector2::Vec2Dot(vUnitDelta, vDeltaVelo);

	MSVector2 vF1 = vUnitDelta * -( m_fkS * ( deltaLength - (m_fInitDistance)) + m_fkD * vDeltaVelo_dot_UnitDelta);
	MSVector2 vF2 = vF1 * -1.0f;

	m_pP1->AddForce(vF1);
	m_pP2->AddForce(vF2);
	
}

void MSSpring::Render()
{
	
	glColor3f(0.0f, 1.0f, 0.0f);

	MSVector2 vV0 = m_pP1->GetPosition();
	MSVector2 vV1 = m_pP2->GetPosition();

	glBegin(GL_LINES);
	glVertex2f(vV0.x, vV0.y);
	glVertex2f(vV1.x, vV1.y);
	glEnd();
	
}


MSSpring& MSSpring::operator=(const MSSpring& spring)
{
	
	m_ForceType = SPRING;
	m_pP1 = spring.m_pP1;
	m_pP2 = spring.m_pP2;
	m_fkD = spring.m_fkD;
	m_fkS = spring.m_fkS;
	return (*this);
}
