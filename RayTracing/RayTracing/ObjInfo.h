#ifndef _OBJINFO_H
#define _OBJINFO_H

#include "Vector.h"
#include "Object.h"

class ObjInfo
{
public:
	ObjInfo();
	~ObjInfo();

	void SetInfo(const Vector &_point, const Vector &_normal, const Object &_mtrl);

	Vector GetPoint();
	Vector GetNormal();
	Object GetMtrl();
	
private:
	Vector point;
	Vector normal;
	Object mtrl;
};

#endif // _OBJINFO_H
