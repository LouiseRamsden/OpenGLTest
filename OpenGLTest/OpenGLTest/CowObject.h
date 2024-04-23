#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "SceneObject.h"
#include "Structs.h"


class CowObject : public SceneObject
{
private:


	Vector3 m_position;
	float m_rotation;

	unsigned char m_rotAxis;
	float m_rotSpeed;

	bool m_xActive;
	bool m_yActive;
	bool m_zActive;

public:
	CowObject(Mesh* mesh, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed);
	~CowObject();

	void SetRotation(float rotation);
	void Draw() override;
	void Update() override;
};

