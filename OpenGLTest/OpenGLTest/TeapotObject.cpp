#include "TeapotObject.h"


TeapotObject::TeapotObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed) : SceneObject(mesh, texture)
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
TeapotObject::~TeapotObject() 
{

}

void TeapotObject::Draw() 
{
	if (m_mesh->Vertices != nullptr && m_mesh->Normals != nullptr && m_mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		//glColorPointer(3, GL_FLOAT, 0, m_mesh->Colors);

		glPushMatrix();
		//glScalef(100.0f, 100.0f, 100.0f);
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotation * 10, 0.0f, 1.0f, 0.0f);
		glRotatef(1, (float)m_xActive, (float)m_yActive, (float)m_zActive);
		glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}
void TeapotObject::Update() 
{
	
}