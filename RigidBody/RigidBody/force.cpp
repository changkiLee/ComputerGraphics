#include "force.h"

Force::Force()
{
	type = GRAVITY;
}

Force::Force(Force &r)
{
	type = r.type;
}

Force::~Force()
{

}
