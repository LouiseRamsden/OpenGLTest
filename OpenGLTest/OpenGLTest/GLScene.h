#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESH_RATE 16

class GLScene
{
public:
	GLScene(int argc, char* argv[]);

	void Display();

	void Update();

	void DrawPolygon();

	~GLScene(void);
private:
	float rotation;
	float rotationSpeedMult;
};

