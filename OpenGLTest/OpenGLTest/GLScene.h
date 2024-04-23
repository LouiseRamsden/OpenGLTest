#pragma once
#include <cmath>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Cube.h"

#include "Structs.h"

#define REFRESH_RATE 16



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
	Cube* cube[200];
	Cube* teapot;
};

