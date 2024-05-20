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

#define OBJ_NUM 5


class GLScene
{
public:
	GLScene(int argc, char* argv[]);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void PassiveMotion(int x, int y);

	void InitObjects();

	void InitLighting();

	void InitGL(int argc, char* argv[]);

	void DrawString(const char* text, Vector3* position, Color* color);

	~GLScene(void);
private:
	Camera* camera;
	bool m_objMoving[OBJ_NUM];
	SceneObject* m_objects[OBJ_NUM];
	Vector4* m_lightPosition;
	Lighting* m_lightData;

};

