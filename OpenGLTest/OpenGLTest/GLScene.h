#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"


class GLScene
{
public:
	GLScene(int argc, char* argv[]);

	void Display();

	void DrawPolygon();

	~GLScene(void);
};

