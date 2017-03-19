#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vector.h"

class Object
{
public:
	Object();
	~Object();

	void SetCat(int n);
	void SetRad(float r);
	void SetCoef(float a, float b, float c, float d);
	void SetShn(int s);
	void SetRef(float _refl, float _refr, float _idxr);
	void SetCent(float x, float y, float z);
	void SetAmb(float x, float y, float z);
	void SetDiff(float x, float y, float z);
	void SetSpec(float x, float y, float z);

	Vector GetCent();
	Vector GetPlaneNorm();
	float GetD();
	float GetRad();
	float GetRefl();
	float GetRefr();
	float GetIdxr();
	Vector GetAmb();
	Vector GetDiff();
	Vector GetSpec();
	int GetShn();

private:
	int cat;	// category (0: sphere, 1: plane)
	float rad;	// radius
	float coef_a, coef_b, coef_c, coef_d;	// coefficients
	int shn;	// shininess(power of specular)
	float refl, refr, idxr;	// reflection factor, refraction factor, index of refraction
	Vector cent;	// center
	Vector amb;		// ambient
	Vector diff;	// diffuse
	Vector spec;	// specular
};

#endif // _OBJECT_H
