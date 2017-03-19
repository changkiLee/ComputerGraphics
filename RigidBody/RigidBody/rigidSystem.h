#ifndef _RIGIDSYSTEM_H
#define _RIGIDSYSTEM_H

#include "gmath.h"
#include "box.h"
#include "force.h"
#include "gravity.h"
#include "external.h"

class RigidSystem
{
public:
	RigidSystem();
	RigidSystem(RigidSystem &r);
	~RigidSystem();

	void Action(float dt);

	//void addMesh(Box _b);
	void addBox(Box *_b);
	void addForce(Force *_force);
	void rigidRender();
	void init();

public:
	Box *m_box;
	vector <Force*> force;
};

#endif
