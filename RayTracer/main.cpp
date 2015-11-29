#include <stdio.h>
#include <conio.h>

#include "Camera.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "GeomObject.h"
#include "Ray.h"


 int main(int argc, char * argv[])
 {
	 SceneManager * m_scene = new SceneManager();
	 m_scene->createTestScene();
	 Camera camera;
	// camera.setPos(Vector3(0,0,0));
	// Vector3 dir = Vector3(-1,-1,-10) - camera.pos;
	// dir.normalize();
	// camera.setDir(dir);
	 m_scene->rayTrace(camera);

	  getch();
	 return 0;
 }