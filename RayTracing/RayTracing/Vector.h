#ifndef _VECTOR_H
#define _VECTOR_H

class Vector
{
public:
	Vector();
	~Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& a);
	void SetVector(float x, float y, float z);

	Vector CalD(const Vector &u, const Vector &v, const Vector &o, int i, int j);
	Vector Cross(const Vector& a);
	Vector Normalise();
	float Dot(const Vector& a);
	float Norm();
	float GetX();
	float GetY();
	float GetZ();
	void VecPrint();
	
	Vector Mult(const Vector& a);
	Vector operator/(float n);
	friend Vector operator*(float n, const Vector & a)
	{
		Vector tmp(a._x*n, a._y*n, a._z*n);
		return tmp;
	}
	friend Vector operator*(const Vector & a, float n)
	{
		Vector tmp(a._x*n, a._y*n, a._z*n);
		return tmp;
	}
	friend Vector operator+(const Vector& a, const Vector& b)
	{
		Vector tmp(a._x+b._x, a._y+b._y, a._z+b._z);
		return tmp;
	}
	friend Vector operator-(const Vector& a, const Vector& b)
	{
		Vector tmp(a._x-b._x, a._y-b._y, a._z-b._z);
		return tmp;
	}
	friend bool operator!=(const Vector& a, const Vector& b)
	{
		Vector tmp = a - b;
		float x = tmp.GetX();
		float y = tmp.GetY();
		float z = tmp.GetZ();
		if(x < 0){
			x = -x;
		}
		if(y < 0){
			y = -y;
		}
		if(z < 0){
			z = -z;
		}
		if(x < 0.001 && y < 0.001 && z < 0.001){
			return false;
		}
		else{
			return true;
		}				
	}
	friend bool operator==(const Vector& a, const Vector& b)
	{
		Vector tmp = a - b;
		float x = tmp.GetX();
		float y = tmp.GetY();
		float z = tmp.GetZ();
		if(x < 0){
			x = -x;
		}
		if(y < 0){
			y = -y;
		}
		if(z < 0){
			z = -z;
		}
		if(x < 0.001 && y < 0.001 && z < 0.001){
			return true;
		}
		else{
			return false;
		}		
	}

private:
	float _x;
	float _y;
	float _z;
};

#endif // _VECTOR_H