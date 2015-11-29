#pragma once

#include "Config.h"
#include "GeomObject.h"
#include "GeomPlane.h"

class GeomTriangle : public GeomObject
{
private:
	Vector3 vertices[3];
public:
	inline GeomTriangle(const Vector3 & v1, const Vector3 & v2,const Vector3 & v3):GeomObject()
	{
		vertices[0] = v1; 
		vertices[1] = v2;
		vertices[2] = v3;
	}

	virtual bool rayIntersectQuery(const Ray & ray,Real & t);
	virtual void getNormalAtPoint(const Vector3 & point, Vector3 & normal);

};