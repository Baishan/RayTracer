#pragma once

#include "Config.h"
#include "Vector3.h"
#include "Ray.h"

class GeomObject{

protected:
	Vector3 diffuse;
	Real surfaceReflection;
	Vector3 specular;
	Real power;
public:
	
	inline GeomObject():surfaceReflection(0),power(0),specular(0,0,0){}
	inline void setDiffuse(const Vector3 & diffuse){this->diffuse = diffuse;}
	inline void setSpecular(const Vector3 & specular, const Real power){this->specular = specular;this->power = power;}
	inline void setReflectionFactor(const Real factor){this->surfaceReflection = factor;}
	inline Vector3 getDiffuse(){return diffuse;}
	inline Vector3 getSpecular(){return specular;}
	inline Real getPower(){return power;}
	inline Real getReflectionFactor(){return surfaceReflection;}

	virtual bool rayIntersectQuery(const Ray & ray, Real & t) = 0;
	virtual void getNormalAtPoint(const Vector3 & point, Vector3 & normal) = 0;
	
};