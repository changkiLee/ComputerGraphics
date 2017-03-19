#ifndef _PVECTOR3_H_
#define _PVECTOR3_H_
#include "..\Include\Common.h"

class PVector3
{
private : 
	double pv[3];		// ��ǥ(x, y, z)

	static double Precision;		// ������

public :
	PVector3();									// ������
	PVector3(double x, double y, double z);		// ����
	PVector3(const PVector3 &cpy);				// ����
	virtual ~PVector3();						// �Ҹ���

	// ��� �Լ�
	PVector3 &set(const double &x, const double &y, const double &z);
	PVector3 &normalize();				// ����ȭ
	void setPrecision(double error);	// ����
	double getPrecision();

	// ������(����/����/÷��)
	PVector3 &operator =(const PVector3 &rhs);
	PVector3 &operator +=(const PVector3 &rhs);
	PVector3 &operator -=(const PVector3 &rhs);
	PVector3 &operator *=(const double &s);
	PVector3 &operator /=(const double &s);
	PVector3 &operator ^=(const PVector3 &rhs);		// ����
	PVector3 operator +() const;
	PVector3 operator -() const;
	double &operator [](const int &idx);			// ÷��
	const double &operator [](const int &idx) const;
	
	// Friend
	friend PVector3 operator +(const PVector3 &lhs, const PVector3 &rhs);
	friend PVector3 operator -(const PVector3 &lhs, const PVector3 &rhs);
	friend double operator *(const PVector3 &lhs, const PVector3 &rhs);		// ����
	friend PVector3 operator /(const PVector3 &lhs, const double &s);
	friend PVector3 operator ^(const PVector3 &lhs, const PVector3 &rhs);	// ����
	friend bool operator ==(const PVector3 &lhs, const PVector3 &rhs);
	friend bool operator !=(const PVector3 &lhs, const PVector3 &rhs);
	friend PVector3 operator *(const PVector3 &lhs, const double &s);
	friend PVector3 operator *(const double &s, const PVector3 &rhs);
	friend ostream &operator <<(ostream &os, const PVector3 &v);
	friend istream &operator >>(istream &is, PVector3 &v);
	friend PVector3 proj(const PVector3 &v, const PVector3 &w);		// ���翵
	friend double dist(const PVector3 &v, const PVector3 &w);		// �Ÿ�
	friend double norm(const PVector3 &v);		// ����
	friend double angle(const PVector3 &v, const PVector3 &w, bool radian);		// ���̰�
};

#endif