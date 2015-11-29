#include "GeomSphere.h"

bool GeomSphere::rayIntersectQuery(const Ray & ray, Real & t)
{
	Ray ray2 = ray;
	ray2.pos = ray2.pos - this->pos;

	Real a = ray2.dir.dotProduct(ray2.dir);
	Real b = ray2.pos.dotProduct(ray2.dir)*2;
	Real c = ray2.pos.dotProduct(ray2.pos) - this->radius*this->radius;

	Real bm4ac = b*b - 4*a*c;
	if(bm4ac < 0) return false; //missed sphere

	Real den = sqrt(bm4ac);
	
	Real t0 = ((0-b) + den)/(2*a);
	Real t1 = ((0-b) - den)/(2*a);
	

	if(t0 > 0 && t0 <= t1)
	{
		t = t0;
		return true;
	}
	else if(t1 > 0 && t1 <= t0)
	{
		t = t1;
		return true;
	}
	else
	{
		return false; //intersects behind 
	}
}

void GeomSphere::getNormalAtPoint(const Vector3 & point, Vector3 & normal)
{
	normal = (point - this->pos);
	normal.normalize();
}