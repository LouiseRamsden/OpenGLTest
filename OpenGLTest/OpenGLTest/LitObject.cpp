
#include "LitObject.h"

//Objects that can be affected by light and can be textured
LitObject::LitObject(Mesh* mesh, Texture2D* texture,Texture2D* swapTexture, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed) : SceneObject(mesh, texture)
{
	m_xActive = xRot;
	m_yActive = yRot;
	m_zActive = zRot;

	m_rotSpeed = rotSpeed;

	m_rotation = 0.0f;
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	m_swapTexture = swapTexture;

		
}
LitObject::~LitObject()
{

}

void LitObject::SetRotation(float rotation)
{
	m_rotation = rotation;
	
}
void LitObject::SetMaterial()
{
	m_material = new Material();
	m_material->Ambient.x = 0.8; m_material->Ambient.y = 0.8; m_material->Ambient.z = 0.9;
	m_material->Ambient.w = 1.0;
	m_material->Diffuse.x = 0.8; m_material->Diffuse.y = 0.8; m_material->Diffuse.z = 0.9;
	m_material->Diffuse.w = 1.0;
	m_material->Specular.x = 1.0; m_material->Specular.y = 1.0; m_material->Specular.z = 1.0;
	m_material->Specular.w = 1.0;
	m_material->Shininess = 100.0f;
}
void LitObject::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Normals != nullptr && m_mesh->Indices != nullptr) 
	{
		SetMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(m_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(m_material->Specular.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(m_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(m_material->Shininess));

		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		
		if (spinning == true)
		{
			glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
		}
		else 
		{
			glBindTexture(GL_TEXTURE_2D, m_swapTexture->GetID());
			
		}
		
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, m_mesh->Normals);

		glPushMatrix();
		glTranslatef(m_position.x, m_position.y, m_position.z);
		if (spinning == true) 
		{
			glRotatef(sinf(m_rotation) * 50, (float)m_xActive, (float)m_yActive, (float)m_zActive);
		}
		glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void LitObject::Update()
{
	m_rotation += m_rotSpeed;
	if (m_rotation > 360.0f)
	{
		m_rotation -= 360.f;
	}
}

