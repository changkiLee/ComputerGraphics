#include "MSParticle.h"
#include <GL\glut.h>

extern int g_WorldWidth, g_WorldHeight;

MSParticle::MSParticle(void)
{
	Init();

}
MSParticle::MSParticle(PARTICLE_TYPE particleType, MSVector2& pos, float mass)
{
	Init();
	m_ParticleType = particleType;
	m_vPos = pos;
	m_fMass = mass;
}
MSParticle::MSParticle(const MSParticle& particle)
{
	this->m_fMass			= particle.m_fMass;
	this->m_ParticleType	= particle.m_ParticleType;
	this->m_vForce			= particle.m_vForce;
	this->m_vPos			= particle.m_vPos;
	this->m_vVelocity		= particle.m_vVelocity;

}
MSParticle::~MSParticle(void)
{

}

MSParticle& MSParticle::operator=(const MSParticle& particle)
{
	this->m_fMass			= particle.m_fMass;
	this->m_ParticleType	= particle.m_ParticleType;
	this->m_vForce			= particle.m_vForce;
	this->m_vPos			= particle.m_vPos;
	this->m_vVelocity		= particle.m_vVelocity;

	return (*this);
}

void MSParticle::Init()
{
	this->m_fMass			= 0;
	this->m_ParticleType	= NORMAL;
	this->m_vForce			= MSVector2(0.0f,0.0f);
	this->m_vPos			= MSVector2(0.0f,0.0f);
	this->m_vVelocity		= MSVector2(0.0f,0.0f);
}

void MSParticle::Action(float dTime)
{
	if(m_ParticleType == FIXED)
		m_vForce = MSVector2(0.0f, 0.0f);

	// Euler Method...
	
	m_vPos = m_vPos + m_vVelocity * dTime;
	m_vVelocity = m_vVelocity + (m_vForce / m_fMass) * dTime;
	

	// Midpoint Method
	/*
	m_vPos = m_vPos + m_vVelocity * dTime * 0.5f;
	m_vVelocity = m_vVelocity + (m_vForce / m_fMass) * dTime * 0.5f;
	*/
	
	if( m_vPos.x < 0)
		m_vPos.x = 0.0f;
	if( m_vPos.y < 0)
		m_vPos.y = 0.0f;
	if( m_vPos.x > g_WorldWidth)
		m_vPos.x = g_WorldWidth;
	if( m_vPos.y > g_WorldHeight)
		m_vPos.y = g_WorldHeight;

	
}

void MSParticle::Render()
{
	glPointSize(5.0f);

	switch(m_ParticleType)
	{
	case NORMAL:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case FIXED:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	default:
		return;
	}

	glBegin(GL_POINTS);
		glVertex2f(m_vPos.x, m_vPos.y);
	glEnd();

}