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

	~GLScene(void);
private:
	float rotation;
	float rotationSpeedMult;

	Camera* camera;
	Cube* cube;
	Cube* cube2;
};

