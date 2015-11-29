#pragma once
#include <cmath>
#include "Config.h"


class Vector3
{
public:
	Real x;
	Real y;
	Real z;
public:
	inline Vector3(const Real x,const Real y, const Real z):x(x),y(y),z(z){}
	inline Real getX() const {return x;}
	inline Real getY() const {return y;}
	inline Real getZ() const {return z;}

	inline Vector3():x(0),y(0),z(0){}

	inline Vector3 operator+ (const Vector3 & v) const
	{
		return Vector3(x+v.getX(), y+v.getY(), z+v.getZ());
	}

	inline Vector3 operator* (const Real t) const
	{
		return Vector3(x*t,y*t,z*t);
	}

	inline Real dotProduct(const Vector3 & v) const
	{
		return x*v.getX() + y*v.getY() + z*v.getZ();
	}

	inline Real dotProduct(const Vector3 * v) const
	{
		return x*v->getX() + y*v->getY() + z*v->getZ();
	}

	inline Vector3 crossProduct(const Vector3 & v)
	{
		return Vector3(y*v.getZ() - z*v.getY(),z*v.getX() - x*v.getZ(),v.getY() * x - y*v.getX());
	}
	
	inline Real magnitude()
	{
		return sqrt(this->dotProduct(this));
	}

	inline void normalize()
	{
		Real mag = this->magnitude();
		x/=mag;
		y/=mag;
		z/=mag;
	}

	inline Vector3 operator-(const Vector3 & v) const
	{
		return Vector3(x-v.getX(),y-v.getY(),z-v.getZ());
	}
};