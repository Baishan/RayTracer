
#include "GeomPlane.h"

bool GeomPlane::rayIntersectQuery(const Ray & ray, Real & t)
{
	t =  (this->pos - ray.pos).dotProduct(this->normal) / ray.dir.dotProduct(this->normal);
	if(t > 0)
	{
		return true;
	}
	else return false;
}