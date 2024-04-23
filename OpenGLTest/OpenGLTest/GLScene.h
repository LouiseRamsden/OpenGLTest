#pragma once
#include <cmath>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "CowObject.h"
#include "TeapotObject.h"

#include "Structs.h"

#define REFRESH_RATE 16

#define NUM_OBJECTS


class GLScene
{
public:
	GLScene(int argc, char* argv[]);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObjects();

	void InitGL(int argc, char* argv[]);

	~GLScene(void);
private:
	Camera* camera;
	SceneObject* m_objects[100];
};

