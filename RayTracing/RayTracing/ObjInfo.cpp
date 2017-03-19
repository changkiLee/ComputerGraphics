#include "ObjInfo.h"
#include <iostream>
using namespace std;

ObjInfo::ObjInfo()
{

}

ObjInfo::~ObjInfo()
{

}

void ObjInfo::SetInfo(const Vector &_point, const Vector &_normal, const Object &_mtrl)
{
	point = _point;
	normal = _normal;
	mtrl = _mtrl;
}

Vector ObjInfo::GetPoint()
{
	return point;
}

Vector ObjInfo::GetNormal()
{
	return normal;
}

Object ObjInfo::GetMtrl()
{
	return mtrl;
}