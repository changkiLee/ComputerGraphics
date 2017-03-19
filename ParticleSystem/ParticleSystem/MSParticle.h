#pragma once

#include "MSVector.h"
class MSParticle
{
public:
	enum PARTICLE_TYPE
	{
		NORMAL = 0,
		FIXED,
		PARTICLE_TYPE_END
	};

protected:
	PARTICLE_TYPE	m_ParticleType;

	MSVector2		m_vPos;

	float			m_fMass;

	MSVector2		m_vVelocity;

	MSVector2		m_vForce;

	void Init();

public:
	MSParticle(void);
	MSParticle(PARTICLE_TYPE particleType, MSVector2& pos, float mass);
	MSParticle(const MSParticle& particle);
	~MSParticle(void);

	MSParticle& operator=(const MSParticle& particle);

	void Action(float dTime);
	void Render();


	void SetParticleType(PARTICLE_TYPE particleType)	{	m_ParticleType = particleType;	}
	void SetPosition(MSVector2& pos)					{	m_vPos = pos;	}
	void SetMass(float mass)							{	m_fMass = mass;	}

	void AddForce(MSVector2 &vForce)					{	m_vForce = m_vForce + vForce;	}

	void InitForce()									{	m_vForce = MSVector2(0,0);	}


	const PARTICLE_TYPE GetParticleType()				{ return m_ParticleType;	}
	MSVector2& GetPosition()							{ return m_vPos;	}
	const float GetMass()								{ return m_fMass;	}
	const MSVector2& GetVelocity()						{ return m_vVelocity;	}
};

