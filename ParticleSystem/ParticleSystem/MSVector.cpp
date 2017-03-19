#include "MSVector.h"
#include "define.h"
#include <Windows.h>
#include <cmath>

MSVector4::MSVector4(void)
{
	MSVector4_Init(0,0,0,0);
}
MSVector4::MSVector4(float _x, float _y, float _z, float _w)
{
	MSVector4_Init(_x, _y, _z, _w);
}
MSVector4::MSVector4(const MSVector4& vec)
{
	MSVector4_Init(vec);
}

MSVector4::~MSVector4(void)
{
}


void MSVector4::MSVector4_Init(const MSVector4& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

void MSVector4::MSVector4_Init(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

float MSVector4::MSVector4_DotProduct(const MSVector4& vec)
{
	return (x * vec.x) + (y * vec.y) + (z * vec.z) + (w * vec.w);
}

MSVector4& MSVector4::operator=(const MSVector4& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;

	return *this;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MSVector3::MSVector3(void)
{
	MSVector3_Init(0,0,0);

}

MSVector3::MSVector3(float _x, float _y, float _z)
{
	MSVector3_Init(_x, _y, _z);

}

MSVector3::MSVector3(const MSVector3& vec)
{
	MSVector3_Init(vec);
}

MSVector3::~MSVector3(void)
{

}

void MSVector3::MSVector3_Init(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void MSVector3::MSVector3_Init(const MSVector3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

MSVector3 MSVector3::Vec3Cross(MSVector3* result, MSVector3& vec1, MSVector3& vec2)
{
	MSVector3 res;

	res.x = vec1.y * vec2.z - vec1.z * vec2.y;
	res.y = vec1.z * vec2.x - vec1.x * vec2.z;
	res.z = vec1.x * vec2.y - vec1.y * vec2.x;

	if( result != NULL )
	{
		result->x = res.x;
		result->y = res.y;
		result->z = res.z;
	}

	return res;

}
float MSVector3::Vec3Dot(MSVector3& vec1, MSVector3& vec2)
{

	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

MSVector3 MSVector3::Vec3Normalize(MSVector3& vec)
{
	float length = Vec3GetLength(vec);

	if( length != 0)
	{
		MSVector3 result = vec/length;
		return result;
	}


	///
	return MSVector3(0,0,0);

}
float MSVector3::Vec3GetLength(MSVector3& vec)
{
	float length =  sqrt( pow(vec.x, 2.0f) + pow(vec.y, 2.0f) + pow(vec.z,2.0f) );

	return length;
}
float MSVector3::Vec3GetDistance(MSVector3& v0, MSVector3& v1)
{
	MSVector3 vD = v1 - v0;
	return Vec3GetLength(vD);
}

MSVector3& MSVector3::operator=(const MSVector3& vec)
{

	x = vec.x;
	y = vec.y;
	z = vec.z;
	return (*this);
}

MSVector3 MSVector3::Vec3Lerp(MSVector3& v0, MSVector3& v1, float t)
{
	// 일단 임시로...
	if( t < 0.0f) t = 0;
	else if( t > 1.0f) t = 1.0f;
	
	MSVector3 result ;

	result = v0 * (1-t) + v1 * t;

	return result;
}
float MSVector3::GetTheta()
{
	float theta;
	

	MSVector3 vec = MSVector3(this->x, this->y, this->z) ;
	float length = Vec3GetLength(vec);
	 
	if( length != 1.0f )
		vec = Vec3Normalize(vec);
	
	if( fabs(vec.z)-1.0f < 1.0e-4f && fabs(vec.z)-1.0f > -1.0e-4f) theta = 0.0f;
	else theta = acos(vec.z);

	return theta;
}

float MSVector3::GetPI()
{
	float phi;

	MSVector3 vec = MSVector3(this->x, this->y, this->z) ;
	float length = Vec3GetLength(vec);

	if( length != 1.0f )
		vec = Vec3Normalize(vec);

	phi = atan2(vec.y, vec.z);
	if( phi < 0 ) phi += 2.0 * PI_;
	return phi;
}
MSVector3 MSVector3::operator+(const MSVector3& vec)
{
	return MSVector3(x + vec.x, y + vec.y, z + vec.z);
}
MSVector3 MSVector3::operator-(const MSVector3& vec)
{
	return MSVector3(x - vec.x, y - vec.y, z - vec.z);
}
MSVector3 MSVector3::operator*(const float value)
{
	return MSVector3(x * value, y * value, z * value);
}
MSVector3 MSVector3::operator/(const float value)
{
	return MSVector3(x / value, y / value, z / value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MSVector2::MSVector2(void)
{
	MSVector2_Init(0,0);
}

MSVector2::MSVector2(float _x, float _y)
{
	MSVector2_Init(_x, _y);
}

MSVector2::MSVector2(const MSVector2& vec)
{
	MSVector2_Init(vec);
}

MSVector2::~MSVector2(void)
{

}

void MSVector2::MSVector2_Init(float _x, float _y)
{
	this->x = _x; this->y = _y;
}
void MSVector2::MSVector2_Init(const MSVector2& vec)
{
	this->x = vec.x; this->y = vec.y;
}


float MSVector2::Vec2Dot(MSVector2& vec1, MSVector2& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}
MSVector2 MSVector2::Vec2Normalize(MSVector2& vec)
{
	float length = Vec2GetLength(vec);

	if( length != 0)
	{
		MSVector2 result = vec/length;
		return result;
	}


	///
	return MSVector2(0,0);
}
float MSVector2::Vec2GetLength(MSVector2& vec)
{
	float length =  sqrt( pow(vec.x, 2.0f) + pow(vec.y, 2.0f));

	return length;
}	

MSVector2 MSVector2::Vec2Lerp(MSVector2& v0, MSVector2& v1, float t)
{
	// 일단 임시로...
	if( t < 0.0f) t = 0;
	else if( t > 1.0f) t = 1.0f;

	MSVector2 result ;

	result = v0 * (1-t) + v1 * t;

	return result;
}
float MSVector2::Vec2GetDistance(MSVector2& v0, MSVector2& v1)
{
	MSVector2 vD = v1 - v0;
	return Vec2GetLength(vD);
}

MSVector2& MSVector2::operator=(const MSVector2& vec)
{
	x = vec.x;
	y = vec.y;
	return (*this);
}

MSVector2 MSVector2::operator+(const MSVector2& vec)
{
	return MSVector2(x + vec.x, y + vec.y);
}
MSVector2 MSVector2::operator-(const MSVector2& vec)
{
	return MSVector2(x - vec.x, y - vec.y);
}
MSVector2 MSVector2::operator*(const float value)
{
	return MSVector2(x * value, y * value);
}
MSVector2 MSVector2::operator/(const float value)
{
	return MSVector2(x / value, y / value);
}
