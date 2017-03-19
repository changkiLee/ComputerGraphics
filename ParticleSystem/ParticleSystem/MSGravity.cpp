#include "MSGravity.h"

MSGravity::MSGravity() : MSForce(GRAVITY)
{
	
}

MSGravity::MSGravity(const MSGravity& gravity) : MSForce(GRAVITY)
{
	m_vGravity = gravity.m_vGravity;
}
MSGravity::MSGravity(const MSVector2& gravity) : MSForce(GRAVITY)
{
	m_vGravity = gravity;
}


MSGravity::~MSGravity(void)
{
}

void MSGravity::Init()
{
	MSForce::Init();
	m_ForceType = GRAVITY;


}

void MSGravity::SetForce(float dTime)
{

}
void MSGravity::SetForce(float dTime, vector<MSParticle*> &particles)
{
	for(vector<MSParticle*>::iterator itor = particles.begin(); itor != particles.end(); itor++)
	{
		float mass = (*itor)->GetMass();
		(*itor)->AddForce( m_vGravity * mass);
	}
}

