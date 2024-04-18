#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "Structs.h"

#include <fstream>
#include <iostream>

class Cube
{
private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;
	static int numVertices, numColors, numIndices;


	Vector3 m_position;
	float m_rotation;

	unsigned char m_rotAxis;
	float m_rotSpeed;

	bool m_xActive;
	bool m_yActive;
	bool m_zActive;

public:
	Cube(float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed);
	~Cube();

	void SetRotation(float rotation);
	void Draw();
	void Update();

	static bool LoadTXT(char* path);

	static bool LoadOBJ(char* path);
};

