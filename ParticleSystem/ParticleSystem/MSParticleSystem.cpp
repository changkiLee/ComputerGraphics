#include "MSParticleSystem.h"


MSParticleSystem::MSParticleSystem(void)
{
	m_vParticles.clear();
	m_vForces.clear();

}


MSParticleSystem::~MSParticleSystem(void)
{
	m_vParticles.clear();
	m_vForces.clear();

}

void MSParticleSystem::AddParticle(MSParticle* particle)
{
	m_vParticles.push_back(particle);
}
void MSParticleSystem::AddForce(MSForce* pForce)
{
	m_vForces.push_back(pForce);
}

void MSParticleSystem::Action(float dTime)
{
	for(vector<MSParticle*>::iterator itor = m_vParticles.begin(); itor != m_vParticles.end(); itor++)
		(*itor)->InitForce();

	for(vector<MSForce*>::iterator itor = m_vForces.begin(); itor != m_vForces.end(); itor++)
	{
		switch( (*itor)->GetType() )
		{
		case MSForce::GRAVITY:
			(*itor)->SetForce(dTime,m_vParticles);
			break;
		case MSForce::SPRING:
			(*itor)->SetForce(dTime);
			break;
		case MSForce::DRAG:
			(*itor)->SetForce(dTime);
			break;
		case MSForce::IMPULSE:
			if( ((MSImpulse*)(*itor))->Enable() )
			{
				(*itor)->SetForce(dTime, m_vParticles);
			}
			else 
			{
				vector<MSForce*>::iterator itor2 = itor-1;
				MSVector2 dir = ((MSImpulse*)(*itor))->GetForce();
				cout << "Deleted Impluse - (" << dir.x << ", " << dir.y << ")" << endl;
				m_vForces.erase(itor);
				itor = itor2;

			}
			break;
		}
	}
	for(vector<MSParticle*>::iterator itor = m_vParticles.begin(); itor != m_vParticles.end(); itor++)
		(*itor)->Action(dTime);
}

void MSParticleSystem::Render()
{
	for(vector<MSParticle*>::iterator itor = m_vParticles.begin(); itor != m_vParticles.end(); itor++)
		(*itor)->Render();

	for(vector<MSForce*>::iterator itor = m_vForces.begin(); itor != m_vForces.end(); itor++)
		(*itor)->Render();

}