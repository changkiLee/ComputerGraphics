#include "rigidSystem.h"

RigidSystem::RigidSystem()
{
	
}

RigidSystem::RigidSystem(RigidSystem &r)
{
	
}

RigidSystem::~RigidSystem()
{
	force.clear();
}

void RigidSystem::init()
{
	for(vector<Force*>::iterator itor = force.begin(); itor != force.end(); itor++)
	{
		if((*itor)->GetType() != Force::GRAVITY)
			(*itor)->initForce();
	}
}

void RigidSystem::Action(float dt)
{	
	m_box->force.Set(0.0, 0.0, 0.0);
	m_box->torq.Set(0.0, 0.0, 0.0);

	for(vector<Force*>::iterator itor = force.begin(); itor != force.end(); itor++)
	{
		switch( (*itor)->GetType() )
		{
		case Force::GRAVITY:
			{
				(*itor)->SetForce(dt, m_box);				
			}			
			break;
		case Force::OTHER:
			if( ((External*)(*itor)) -> Enable() )
			{				
				(*itor)->SetForce(dt, m_box);
			}
			else 
			{
				//m_box->rot.SetIdentity();
				vector<Force*>::iterator itor2 = itor-1;
				force.erase(itor);
				itor = itor2;
			}

			break;
		}
	}

	m_box->ForceApply(dt);
	m_box->RotApply(dt);
	m_box->find_all_collisions();
}

void RigidSystem::addBox(Box *_b)
{
	m_box = _b;
}

void RigidSystem::addForce(Force *_force)
{
	force.push_back(_force);
}

void RigidSystem::rigidRender()
{
	m_box->RenderBox();
}