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

struct Vector4 
{
	float x, y, z, w;
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

struct TexCoord
{
	GLfloat u, v;
};


struct Mesh 
{
	Vertex* Vertices;
	Vector3* Normals;
	Color* Colors;
	GLushort* Indices;
	TexCoord* TexCoords;
	GLushort* TexCoordIndices;
	int VertexCount, NormalCount, IndexCount, TexCoordsCount, TexCoordIndexCount;
};

struct Lighting 
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material 
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};
