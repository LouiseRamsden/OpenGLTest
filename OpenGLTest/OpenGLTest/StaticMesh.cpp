
#include "StaticMesh.h"

#include <sstream>


StaticMesh::StaticMesh(Mesh* mesh, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed)
{
	m_mesh = mesh;
	m_xActive = xRot;
	m_yActive = yRot;
	m_zActive = zRot;

	m_rotSpeed = rotSpeed;

	m_rotation = 0.0f;
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

		
}
StaticMesh::~StaticMesh()
{

}

void StaticMesh::SetRotation(float rotation)
{
	m_rotation = rotation;
	
}

void StaticMesh::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Colors != nullptr && m_mesh->Indices != nullptr) 
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, m_mesh->Colors);

		glPushMatrix();
		//glScalef(100.0f, 100.0f, 100.0f);
		glTranslatef(0.0f, -2.5f, 0.0f);
		glRotatef(m_rotation * 10, 0.0f, 1.0f, 0.0f);
		glRotatef(sinf(m_rotation)*20, (float)m_xActive, (float)m_yActive, (float)m_zActive);
		glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

void StaticMesh::Update()
{
	m_rotation += m_rotSpeed;
	if (m_rotation > 360.0f)
	{
		m_rotation -= 360.f;
	}
}

