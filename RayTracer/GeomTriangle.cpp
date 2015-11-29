#include "GeomTriangle.h"

bool GeomTriangle::rayIntersectQuery(const Ray & ray,Real & t)
{
	//check for plane intersect
	Vector3 e1 = vertices[1] - vertices[0];
	e1.normalize();

	Vector3 e2 = vertices[2] - vertices[0];
	e2.normalize();

	Vector3 normal = e1.crossProduct(e2);
	normal.normalize();

	GeomPlane p(vertices[0],normal);
	if(!p.rayIntersectQuery(ray,t)) return false;


	Vector3 interPos = ray.evaluate(t);

	//check triangle intersect
	e2 = (vertices[2]-vertices[1]);
	e2.normalize();

	Vector3 e3 = (vertices[0]-vertices[2]);

	Vector3 cross1 = e1.crossProduct(interPos-vertices[0]);
	
	if(cross1.dotProduct(normal) < 0) return false;

	cross1  = e2.crossProduct(interPos-vertices[1]);
	if(cross1.dotProduct(normal) < 0) return false;

	cross1  = e3.crossProduct(interPos-vertices[2]);
	if(cross1.dotProduct(normal) < 0) return false;

	return true;
}

void GeomTriangle::getNormalAtPoint(const Vector3 & point, Vector3 & normal)
{
	Vector3 e1 = vertices[1] - vertices[0];
	e1.normalize();

	Vector3 e2 = vertices[2] - vertices[0];
	e2.normalize();

	normal = e1.crossProduct(e2);
	normal.normalize();
}