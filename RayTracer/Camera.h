
#pragma once
#include "Config.h"

#include "Vector3.h"

class Camera{
public:
	Vector3 pos;
	Vector3 dir;
	Real fov;
	Real nearClip;
	int resX;
	int resY;
	Vector3 imagePlanePos;
	Real imagePlaneWidth;
	Real imagePlaneHeight;


public:
	Camera();
	inline void setPos(const Vector3 & pos){this->pos = pos;}
	inline void setDir(const Vector3 & dir){this->dir = dir;}

};