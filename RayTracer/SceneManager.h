#pragma once
#include <exception>
#include <vector>

#include <cv.h>
#include <highgui.h>

#include "Camera.h"

#include "GeomObject.h"
#include "GeomTriangle.h"
#include "GeomSphere.h"
#include "Light.h"

class SceneManager {
private:
	static SceneManager * globalPtr;
	std::vector<GeomObject *> sceneObjects;
	std::vector<Light *> lights;

public:
	SceneManager();
	static SceneManager * getSingletonPtr() {return globalPtr;}
	void rotateSceneX(Real angle);
	void attachObject(GeomObject * geomObject);
	void attachLight(Light * light);

	void createTestScene();
	bool rayIntersectTest(const Ray & ray, Real & t, GeomObject *& object);
	bool rayLightTest(Vector3 & pos, Vector3 & sufaceNormal, Vector3 & colour, Ray & viewRay,GeomObject * gObject);

	void rayTrace(const Camera & camera);
	void drawFrameBuffer(Vector3 * frameBuffer, int width, int height);
};