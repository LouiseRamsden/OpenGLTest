#pragma once

#include "Structs.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* m_mesh;
	Texture2D* m_texture;
	Vector3 m_position;

public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	Vector3 GetPosition();

	bool spinning = false;
};

