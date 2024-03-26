#pragma once
#include <cmath>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESH_RATE 16

struct Vector3 
{
	float x, y, z;
	void normalize() 
	{
		float length = sqrtf((x * x) + (y * y) + (z * z));
		x = x / length;
		y = y / length;
		z = z / length;
	}
};

struct Camera 
{
	Vector3 eye, //View Position
		center, //Look at target
		up; //up vector
};

class GLScene
{
public:
	GLScene(int argc, char* argv[]);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void DrawPolygon();

	~GLScene(void);
private:
	float rotation;
	float rotationSpeedMult;

	Camera* camera;
};

