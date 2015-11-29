
#include "Camera.h"

Camera::Camera():pos(Vector3(0,0,0)),dir(Vector3(0,0,-1)),fov(PI/4),nearClip(0.5),resX(800),resY(600)
	{
		imagePlaneWidth = tan(fov/2)*nearClip;
		imagePlaneHeight = (imagePlaneWidth/(float)resX)*(float)resY;
	}

