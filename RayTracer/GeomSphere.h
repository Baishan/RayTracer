#pragma once
#include <stdio.h>
#include "GeomObject.h"
#include "Ray.h"
#include "Vector3.h"
#include "Config.h"

class GeomSphere : public GeomObject
{
public:
	Vector3 pos;
	Real radius;

public:
	inline GeomSphere(const Vector3 & pos, const Real radius):pos(pos),radius(radius){}
	bool rayIntersectQuery(const Ray & ray, Real & t);
	virtual void getNormalAtPoint(const Vector3 & point, Vector3 & normal);
};