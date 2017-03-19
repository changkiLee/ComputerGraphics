#include "..\Include\PVector3.h"

double PVector3::Precision = 1.0e-7;

PVector3::PVector3()
{
	pv[0] = pv[1] = pv[2] = 0.0;
}

PVector3::PVector3(double x, double y, double z)
{
	pv[0] = x;
	pv[1] = y;
	pv[2] = z;
}

PVector3::PVector3(const PVector3 &cpy)
{
	pv[0] = cpy.pv[0];
	pv[1] = cpy.pv[1];
	pv[2] = cpy.pv[2];
}

PVector3::~PVector3()
{

}

PVector3 &PVector3::set(const double &x, const double &y, const double &z)
{
	pv[0] = x;
	pv[1] = y;
	pv[2] = z;
	return *this;
}

PVector3 &PVector3::normalize()
{
	double len = norm(*this);
	if (EQ_ZERO(len, Precision))
		return *this;
	pv[0] /= len;
	pv[1] /= len;
	pv[2] /= len;
	return *this;
}

void PVector3::setPrecision(double error)
{
	Precision = error;
}

double PVector3::getPrecision()
{
	return Precision;
}

PVector3 &PVector3::operator =(const PVector3 &rhs)
{
	pv[0] = rhs.pv[0];
	pv[1] = rhs.pv[1];
	pv[2] = rhs.pv[2];
	return *this;
}

PVector3 &PVector3::operator +=(const PVector3 &rhs)
{
	pv[0] += rhs.pv[0];
	pv[1] += rhs.pv[1];
	pv[2] += rhs.pv[2];
	return *this;
}

PVector3 &PVector3::operator -=(const PVector3 &rhs)
{
	pv[0] -= rhs.pv[0];
	pv[1] -= rhs.pv[1];
	pv[2] -= rhs.pv[2];
	return *this;
}

PVector3 &PVector3::operator *=(const double &s)
{
	pv[0] *= s;
	pv[1] *= s;
	pv[2] *= s;
	return *this;
}

PVector3 &PVector3::operator /=(const double &s)
{
	pv[0] /= s;
	pv[1] /= s;
	pv[2] /= s;
	return *this;
}

PVector3 &PVector3::operator ^=(const PVector3 &rhs)
{
	double x = pv[0], y = pv[1], z = pv[2];
	pv[0] = y * rhs.pv[0] - z * rhs.pv[0];
	pv[1] = z * rhs.pv[1] - x * rhs.pv[1];
	pv[2] = x * rhs.pv[2] - y * rhs.pv[2];
	return *this;
}

PVector3 PVector3::operator +() const
{
	return *this;
}

PVector3 PVector3::operator -() const
{
	return *this * -1;
}

double &PVector3::operator [](const int &idx)
{
	assert(idx >= 0 && idx < 3);
	if(idx == 0)
		return pv[0];
	else if(idx == 1)
		return pv[1];
	else
		return pv[2];
}

const double &PVector3::operator [](const int &idx) const
{
	assert(idx >= 0 && idx < 3);
	if(idx == 0)
		return pv[0];
	else if(idx == 1)
		return pv[1];
	else
		return pv[2];
}

// Friend

PVector3 operator +(const PVector3 &lhs, const PVector3 &rhs)
{
	return PVector3(lhs.pv[0] + rhs.pv[0], lhs.pv[1] + rhs.pv[1], lhs.pv[2] + rhs.pv[2]);
}

PVector3 operator -(const PVector3 &lhs, const PVector3 &rhs)
{
	return PVector3(lhs.pv[0] - rhs.pv[0], lhs.pv[1] - rhs.pv[1], lhs.pv[2] - rhs.pv[2]);
}

double operator *(const PVector3 &lhs, const PVector3 &rhs)
{
	return lhs.pv[0] * rhs.pv[0] + lhs.pv[1] * rhs.pv[1] + lhs.pv[2] * rhs.pv[2];
}

PVector3 operator /(const PVector3 &lhs, const double &s)
{
	return PVector3(lhs.pv[0] / s, lhs.pv[1] / s, lhs.pv[2] / s);
}

PVector3 operator ^(const PVector3 &lhs, const PVector3 &rhs)
{
	return PVector3(lhs.pv[1] * rhs.pv[2] - lhs.pv[2] * rhs.pv[1], lhs.pv[2] * rhs.pv[0] - lhs.pv[0] * rhs.pv[2], lhs.pv[0] * rhs.pv[1] - lhs.pv[1] * rhs.pv[0]);
}

bool operator ==(const PVector3 &lhs, const PVector3 &rhs)
{
	double error = PVector3::Precision;
	return (EQ(lhs.pv[0], rhs.pv[0], error) && EQ(lhs.pv[1], rhs.pv[1], error) && EQ(lhs.pv[2], rhs.pv[2], error));
}

bool operator !=(const PVector3 &lhs, const PVector3 &rhs)
{
	double error = PVector3::Precision;
	return (!EQ(lhs.pv[0], rhs.pv[0], error) || !EQ(lhs.pv[1], rhs.pv[1], error) || !EQ(lhs.pv[2], rhs.pv[2], error));
}


PVector3 operator *(const PVector3 &lhs, const double &s)
{
	PVector3 ret(lhs);
	ret *= s;
	return ret;
}

PVector3 operator *(const double &s, const PVector3 &rhs)
{
	PVector3 ret(rhs);
	ret *= s;
	return ret;
}

ostream &operator <<(ostream &os, const PVector3 &v)
{
	os << "(" << setw(10) << v.pv[0] << ", " << setw(10) << v.pv[1] << ", " << setw(10) << v.pv[2] << ")";
	return os;
}

istream &operator >>(istream &is, PVector3 &v)
{
	is >> v.pv[0] >> v.pv[1] >> v.pv[2];
	return is;
}

PVector3 proj(const PVector3 &v, const PVector3 &w)
{
	return (v * w / (w.pv[0] * w.pv[0] + w.pv[1] * w.pv[1] + w.pv[2] * w.pv[2])) * w;
}

double dist(const PVector3 &v, const PVector3 &w)
{
	return norm(v - w);
}

double norm(const PVector3 &v)
{
	return SQRT(SQR(v.pv[0]) + SQR(v.pv[1]) + SQR(v.pv[2]));
}

double angle(const PVector3 &v, const PVector3 &w, bool radian)
{
	PVector3 p(v);
	PVector3 q(w);
	double cs, sn, theta;

	p.normalize();
	q.normalize();

	cs = p * q;
	sn = norm(p ^ q);

	theta = radian ? atan2(sn, cs) : RAD2DEG(atan2(sn, cs));
	return theta;
}