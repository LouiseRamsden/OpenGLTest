#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "Structs.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>

class StaticMesh
{
private:
	Mesh* m_mesh;


	Vector3 m_position;
	float m_rotation;

	unsigned char m_rotAxis;
	float m_rotSpeed;

	bool m_xActive;
	bool m_yActive;
	bool m_zActive;

public:
	StaticMesh(Mesh* mesh, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed);
	~StaticMesh();

	void SetRotation(float rotation);
	void Draw();
	void Update();
};

