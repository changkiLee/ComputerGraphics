#pragma once


struct MSVector4
{
	float x, y, z, w;
	
	MSVector4(void);
	MSVector4(float _x, float _y, float _z, float _w = 1);
	MSVector4(const MSVector4& vec);
	~MSVector4(void);

	void MSVector4_Init(float _x, float _y, float _z, float _w = 1);
	void MSVector4_Init(const MSVector4& vec);
	float MSVector4_DotProduct(const MSVector4& vec);
	
	MSVector4& operator=(const MSVector4& vec);
};



struct MSVector3
{
	float x, y, z;

	MSVector3(void);
	MSVector3(float _x, float _y, float _z);
	MSVector3(const MSVector3& vec);
	~MSVector3(void);

	void MSVector3_Init(float _x, float _y, float _z);
	void MSVector3_Init(const MSVector3& vec);
	
	static MSVector3 Vec3Cross(MSVector3* result, MSVector3& vec1, MSVector3& vec2);
	static float Vec3Dot(MSVector3& vec1, MSVector3& vec2);
	static MSVector3 Vec3Normalize(MSVector3& vec);
	static float Vec3GetLength(MSVector3& vec);
	static float Vec3GetDistance(MSVector3& v0, MSVector3& v1);
	static MSVector3 Vec3Lerp(MSVector3& v0, MSVector3& v1, float t);
	
	// spherical coordinate...
	float GetTheta();
	float GetPI();
	//
	MSVector3& operator=(const MSVector3& vec);
	MSVector3 operator+(const MSVector3& vec);
	MSVector3 operator-(const MSVector3& vec);
	MSVector3 operator*(const float value);
	MSVector3 operator/(const float value);
};

struct MSVector2
{

	float x, y;

	MSVector2(void);
	MSVector2(float _x, float _y);
	MSVector2(const MSVector2& vec);
	~MSVector2(void);

	void MSVector2_Init(float _x, float _y);
	void MSVector2_Init(const MSVector2& vec);

	static float Vec2Dot(MSVector2& vec1, MSVector2& vec2);
	static MSVector2 Vec2Normalize(MSVector2& vec);
	static float Vec2GetLength(MSVector2& vec);

	static MSVector2 Vec2Lerp(MSVector2& v0, MSVector2& v1, float t);
	static float Vec2GetDistance(MSVector2& v0, MSVector2& v1);

	//
	MSVector2& operator=(const MSVector2& vec);
	MSVector2 operator+(const MSVector2& vec);
	MSVector2 operator-(const MSVector2& vec);
	MSVector2 operator*(const float value);
	MSVector2 operator/(const float value);
};;