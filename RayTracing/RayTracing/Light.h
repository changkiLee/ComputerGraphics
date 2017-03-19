#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vector.h"

class Light
{
public:
	Light();
	~Light();

	void SetCat(int n);
	void SetPosition(float x, float y, float z);
	void SetAmb(float x, float y, float z);
	void SetDiff(float x, float y, float z);
	void SetSpec(float x, float y, float z);
	void SetAtt(float x, float y, float z);
	void SetDirection(float x, float y, float z);

	Vector GetPosition();
	Vector GetAmb();
	Vector GetDiff();
	Vector GetSpec();
	Vector GetAtt();
	Vector GetDirection();
	int GetCat();

private:
	int cat;			// category(0: directional, 1: point, 2: spot)
	Vector position;	// position
	Vector direction;	// direction
	Vector amb;			// ambient
	Vector diff;		// diffuse
	Vector spec;		// specular
	Vector att;			// attenuation
};

#endif // _LIGHT_H
