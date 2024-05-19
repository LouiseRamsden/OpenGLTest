#pragma once

#include "Structs.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* m_mesh;
	Texture2D* m_texture;

public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool spinning = false;
};

