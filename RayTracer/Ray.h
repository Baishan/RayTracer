#pragma once

#include "Vector3.h"

class Ray{
public:
	Vector3 pos;
	Vector3 dir;

public:
	Ray(const Vector3 & pos, const Vector3 & dir):pos(pos),dir(dir){}
	inline Vector3 evaluate(const Real t) const {return pos + dir*t;} 
};