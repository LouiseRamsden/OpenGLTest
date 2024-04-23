#pragma once

#include "Structs.h"

class SceneObject
{
protected:
	Mesh* m_mesh;

public:
	SceneObject(Mesh* mesh);
	virtual ~SceneObject() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

