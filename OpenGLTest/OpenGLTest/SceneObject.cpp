#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	m_mesh = mesh;
	m_texture = texture;
}

Vector3 SceneObject::GetPosition() 
{
	return m_position;
}
