#include "MSForce.h"


MSForce::MSForce(void)
{
	Init();
}
MSForce::MSForce(FORCE_TYPE forceType)
{
	m_ForceType = forceType;
}

MSForce::~MSForce(void)
{

}
void MSForce::Init()
{
	m_ForceType = GRAVITY;
}