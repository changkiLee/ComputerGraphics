#pragma once

#include <iostream>
#include <vector>

#include "MSParticle.h"
#include "MSForce.h"
#include "MSGravity.h"
#include "MSSpring.h"
#include "MSImpulse.h"

using namespace std;

class MSParticleSystem
{
private:
	vector<MSParticle*>	m_vParticles;
	vector<MSForce*>	m_vForces;

public:
	MSParticleSystem(void);
	~MSParticleSystem(void);


	void Action(float dTime);
	void Render();

	void AddParticle(MSParticle* particle);
	void AddForce(MSForce* pForce);

	vector<MSParticle*>& GetParticles() { return m_vParticles; }

};

