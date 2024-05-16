#pragma once
#include <cmath>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "LitObject.h"
#include "UnlitObject.h"

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

	void InitLighting();

	void InitGL(int argc, char* argv[]);

	void DrawString(const char* text, Vector3* position, Color* color);

	~GLScene(void);
private:
	Camera* camera;
	SceneObject* m_objects[100];
	Vector4* m_lightPosition;
	Lighting* m_lightData;

};

