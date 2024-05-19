#include "UnlitObject.h"


UnlitObject::UnlitObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed, float scale) : SceneObject(mesh, texture)
{
	m_xActive = xRot;
	m_yActive = yRot;
	m_zActive = zRot;

	m_rotSpeed = rotSpeed;

	m_rotation = 0.0f;
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	m_scale = scale;

}
UnlitObject::~UnlitObject()
{

}

void UnlitObject::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Normals != nullptr && m_mesh->Indices != nullptr)
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, m_mesh->Colors);

		glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glScalef(m_scale, m_scale, m_scale);
		if (spinning == true) 
		{
			glRotatef(m_rotation * 10, 0.0f, 1.0f, 0.0f);
			glRotatef(m_rotation, (float)m_xActive, (float)m_yActive, (float)m_zActive);
		}
		glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
	}
}
void UnlitObject::Update()
{
	m_rotation += m_rotSpeed;
	if (m_rotation > 360.0f)
	{
		m_rotation -= 360.f;
	}
}