#pragma once

#include "GL/freeglut.h"

#include <cmath>

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
	Vector3 eye,	//View Position
		center,		//Look at target
		up;			//up vector
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct Mesh 
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	int VertexCount, ColorCount, IndexCount;
};
