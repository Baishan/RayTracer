
#include "SceneManager.h"

SceneManager * SceneManager::globalPtr = 0;

SceneManager::SceneManager()
{
	if(this->globalPtr != 0) throw std::exception("More than one scenemanager");
	this->globalPtr = this;
}

void SceneManager::attachObject(GeomObject * geomObject)
{
	this->sceneObjects.push_back(geomObject);
}

void SceneManager::attachLight(Light * light)
{
	this->lights.push_back(light);
}

void SceneManager::createTestScene()
{
	GeomObject * tri = new GeomTriangle(Vector3(-6,-6,-12),Vector3(6,-6,-12),Vector3(0,6,-12));
	tri->setDiffuse(Vector3(1,0,0));
	//tri->setReflectionFactor(0.8);
	tri->setSpecular(Vector3(1,1,1),50);
	//this->attachObject(tri);

	/* tri = new GeomTriangle(Vector3(-10,-10,-12),Vector3(10,-10,-12),Vector3(-10,10,-12));
	tri->setDiffuse(Vector3(1,1,1));
	//tri->setReflectionFactor(0.8);
	tri->setSpecular(Vector3(1,1,1),50);
	this->attachObject(tri);*/

	/* tri = new GeomTriangle(Vector3(10,-10,-12),Vector3(10,10,-12),Vector3(-10,10,-12));
	tri->setDiffuse(Vector3(1,1,1));
	//tri->setReflectionFactor(0.8);
	tri->setSpecular(Vector3(1,1,1),50);
	this->attachObject(tri);*/

	GeomObject * plane = new GeomPlane(Vector3(0,0,-12),Vector3(0,0,1));
	plane->setDiffuse(Vector3(1,1,1));
	plane->setSpecular(Vector3(1,1,1),50);
	//plane->setReflectionFactor(0.9);
	this->attachObject(plane);

	GeomObject * sphere = new GeomSphere(Vector3(-1,-1,-10),1);
	sphere->setDiffuse(Vector3(0,0.5,0));
	sphere->setReflectionFactor(0.1);
	sphere->setSpecular(Vector3(1,1,1),60);
	this->attachObject(sphere);

	sphere = new GeomSphere(Vector3(1,-1,-10),1.2);
	this->attachObject(sphere);
	sphere->setDiffuse(Vector3(0,0.5,0.5));
	sphere->setReflectionFactor(0.8);
	sphere->setSpecular(Vector3(0,1,1),80);
	 sphere = new GeomSphere(Vector3(0,1,-10),1.5);
	sphere->setDiffuse(Vector3(0,0,0.8));
	sphere->setSpecular(Vector3(1,1,1),10);
	sphere->setReflectionFactor(0.1);
	this->attachObject(sphere);
	

	Light * light = new Light(Vector3(1,0,-5),1.0);
	this->attachLight(light);

	light = new Light(Vector3(-1,0,-8),1.0);
	this->attachLight(light);
}

bool SceneManager::rayIntersectTest(const Ray & ray,Real & t, GeomObject *& intersectObject)
{
	bool intersects = false;
	t = 99999;
	for(int x = 0; x < this->sceneObjects.size(); ++x)
	{
		Real at = 0;
		if(this->sceneObjects[x]->rayIntersectQuery(ray,at))
		{
			if(at < t) 
				{
					t = at;
					intersectObject = sceneObjects[x];
		
					intersects = true;
			}
		}
	}
	return intersects;
}

bool SceneManager::rayLightTest(Vector3 & pos, Vector3 & surfaceNormal, Vector3 & colour,Ray & viewRay,GeomObject * gObject)
{
	Vector3 diffuse = colour;
	colour = Vector3(0,0,0);
	bool res = false;
	for(int x = 0; x < this->lights.size(); ++x)
	{
		Vector3  v = lights[x]->pos - pos;
		v.normalize();
		Ray r(pos+(v*0.0001),v);
		Real t;
		GeomObject * geomObject;
		if(surfaceNormal.dotProduct(v) > 0)
		{
			if(!rayIntersectTest(r,t,geomObject))
			{
				
				float fViewProjection = viewRay.dir.dotProduct(surfaceNormal);
				float fLightProjection = r.dir.dotProduct(surfaceNormal);
				Vector3 blinnDir = r.dir - viewRay.dir;
				float temp = blinnDir.dotProduct(blinnDir);
				if (temp != 0.0f )
				{
					float blinn = (1.0/sqrt(temp)) * MAX(fLightProjection - fViewProjection , 0.0f);
					blinn = 1 * powf(blinn, gObject->getPower());
					colour = colour + gObject->getSpecular() *blinn;
				}

				 

					 colour = colour + (diffuse * surfaceNormal.dotProduct(v));
				res = true;
			}
		}
	}
	return res;
}

void SceneManager::rayTrace(const Camera & camera)
{
	Vector3 * frameBuffer = new Vector3[camera.resX*camera.resY];

	Vector3 imagePlanePos = camera.pos + camera.dir*camera.nearClip;
			imagePlanePos.x -= camera.imagePlaneWidth;
			imagePlanePos.y -= camera.imagePlaneHeight;

	for(int y = 0; y < camera.resY; ++y)
	{
		for(int x = 0; x < camera.resX; ++x)
		{
			Vector3 rayPos;
			rayPos.x = imagePlanePos.x + (Real)(x)*((camera.imagePlaneWidth*2)/camera.resX);
			rayPos.y = imagePlanePos.y + (Real)(y)*((camera.imagePlaneHeight*2)/camera.resY);
			rayPos.z = imagePlanePos.z;
			rayPos = rayPos - camera.pos;
			rayPos.normalize();
			
			Ray ray(camera.pos,rayPos);
			Real reflectionFactor = 0.5;

			Real t;
			GeomObject * geomObject = 0;
			int depth = 0;
			while(reflectionFactor > 0 && depth < 10 && this->rayIntersectTest(ray,t,geomObject))
			{
					Vector3 colour = geomObject->getDiffuse();
					Vector3 surfacePos = ray.evaluate(t);
					Vector3 surfaceNormal;
					geomObject->getNormalAtPoint(surfacePos,surfaceNormal);
					rayLightTest(surfacePos,surfaceNormal,colour,ray,geomObject);

					frameBuffer[camera.resX*y + x] =  frameBuffer[camera.resX*y + x] + colour * reflectionFactor;
					reflectionFactor *= geomObject->getReflectionFactor();
					Ray reflectRay(surfacePos,ray.dir - (surfaceNormal*2.0f) * (ray.dir.dotProduct(surfaceNormal)));
					ray = reflectRay;
					depth++;
			}

		}
	}

	drawFrameBuffer(frameBuffer,camera.resX,camera.resY);
}

void SceneManager::drawFrameBuffer(Vector3 * frameBuffer, int width, int height)
{
	IplImage * image = cvCreateImage(cvSize(width,height),8,3);
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			Vector3 * v = &frameBuffer[width*y + x];
			image->imageData[y*image->widthStep + x*image->nChannels +0] = v->getX() > 1.0f?255:v->getX()*255;
			image->imageData[y*image->widthStep + x*image->nChannels +1] = v->getY() > 1.0f?255:v->getY()*255;
			image->imageData[y*image->widthStep + x*image->nChannels +2] = v->getZ() > 1.0f?255:v->getZ()*255;
		}
	}
	cvNamedWindow("test",0);
	cvShowImage("test",image);
	cvWaitKey(0);

}