#ifndef _PVECTOR3_H_
#define _PVECTOR3_H_
#include "..\Include\Common.h"

class PVector3
{
private : 
	double pv[3];		// 좌표(x, y, z)

	static double Precision;		// 오차값

public :
	PVector3();									// 생성자
	PVector3(double x, double y, double z);		// 대입
	PVector3(const PVector3 &cpy);				// 복사
	virtual ~PVector3();						// 소멸자

	// 멤버 함수
	PVector3 &set(const double &x, const double &y, const double &z);
	PVector3 &normalize();				// 정규화
	void setPrecision(double error);	// 오차
	double getPrecision();

	// 연산자(대입/단항/첨자)
	PVector3 &operator =(const PVector3 &rhs);
	PVector3 &operator +=(const PVector3 &rhs);
	PVector3 &operator -=(const PVector3 &rhs);
	PVector3 &operator *=(const double &s);
	PVector3 &operator /=(const double &s);
	PVector3 &operator ^=(const PVector3 &rhs);		// 외적
	PVector3 operator +() const;
	PVector3 operator -() const;
	double &operator [](const int &idx);			// 첨자
	const double &operator [](const int &idx) const;
	
	// Friend
	friend PVector3 operator +(const PVector3 &lhs, const PVector3 &rhs);
	friend PVector3 operator -(const PVector3 &lhs, const PVector3 &rhs);
	friend double operator *(const PVector3 &lhs, const PVector3 &rhs);		// 내적
	friend PVector3 operator /(const PVector3 &lhs, const double &s);
	friend PVector3 operator ^(const PVector3 &lhs, const PVector3 &rhs);	// 외적
	friend bool operator ==(const PVector3 &lhs, const PVector3 &rhs);
	friend bool operator !=(const PVector3 &lhs, const PVector3 &rhs);
	friend PVector3 operator *(const PVector3 &lhs, const double &s);
	friend PVector3 operator *(const double &s, const PVector3 &rhs);
	friend ostream &operator <<(ostream &os, const PVector3 &v);
	friend istream &operator >>(istream &is, PVector3 &v);
	friend PVector3 proj(const PVector3 &v, const PVector3 &w);		// 정사영
	friend double dist(const PVector3 &v, const PVector3 &w);		// 거리
	friend double norm(const PVector3 &v);		// 길이
	friend double angle(const PVector3 &v, const PVector3 &w, bool radian);		// 사이각
};

#endif