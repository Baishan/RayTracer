#pragma once
#include "Config.h"
#include "GeomObject.h"
#include "Vector3.h"

class GeomPlane : public GeomObject{
private:
	Vector3 normal;
	Vector3 pos;
public:
	GeomPlane ( const Vector3 & pos, const Vector3 & normal):GeomObject(),pos(pos),normal(normal){}
	virtual bool rayIntersectQuery(const Ray & ray,Real & t);
	virtual void getNormalAtPoint(const Vector3 & point, Vector3 & normal){normal = this->normal;}
	inline Vector3 getPos(){return pos;}
};