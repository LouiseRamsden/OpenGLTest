#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "Structs.h"

class Cube
{
private:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];

	Vector3 m_position;
	float m_rotation;
public:
	Cube(float x, float y, float z);
	~Cube();

	void SetRotation(float rotation);
	void Draw();
	void Update();
};

