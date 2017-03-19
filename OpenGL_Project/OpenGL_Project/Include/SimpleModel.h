#ifndef _SIMPLEMODEL_H_
#define _SIMPLEMODEL_H_

#include "..\Include\Common.h"

class SimpleModel
{
public :
	void renderFloor(const int &size);
	void renderSolidTeapot(const double &size);
	void renderSphere(const double &size, const int &slice, const int &stack);
	void renderTorus(const double &in, const double &out, const int &side, const int &ring);
	void renderString(const char *str, const float &r, const float &g, const float &b);
};

#endif