#include "Cube.h"

Vertex Cube::indexedVertices[] = {
	1, 1, 1, -1, 1, 1,	// v0,v1,
	-1,-1, 1, 1,-1, 1,	// v2,v3
	1,-1,-1, 1, 1,-1,	// v4,v5
	-1, 1,-1, -1,-1,-1	// v6,v7 
};

Color Cube::indexedColors[] = {
	1, 1, 1, 1, 1, 0,	// v0,v1,
	1, 0, 0, 1, 0, 1,	// v2,v3
	0, 0, 1, 0, 1, 1,	// v4,v5
	0, 1, 0, 0, 0, 0	//v6,v7 
};

GLushort Cube::indices[] = {
	0, 1, 2, 2, 3, 0,	// front
	0, 3, 4, 4, 5, 0,	// right
	0, 5, 6, 6, 1, 0,	// top
	1, 6, 7, 7, 2, 1,	// left
	7, 4, 3, 3, 2, 7,	// bottom
	4, 7, 6, 6, 5, 4	// back
};


Cube::Cube(float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed) 
{

	m_xActive = xRot;
	m_yActive = yRot;
	m_zActive = zRot;

	m_rotSpeed = rotSpeed;

	m_rotation = 0.0f;
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

		
}
Cube::~Cube() 
{

}

void Cube::SetRotation(float rotation) 
{
	m_rotation = rotation;
	
}

void Cube::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_rotation, (float)m_xActive, (float)m_yActive, (float)m_zActive);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Cube::Update() 
{
	m_rotation += m_rotSpeed;
	if (m_rotation > 360.0f)
	{
		m_rotation -= 360.f;
	}
}