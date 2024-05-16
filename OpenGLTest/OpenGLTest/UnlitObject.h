#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "SceneObject.h"
#include "Structs.h"

class UnlitObject : public SceneObject
{
private:
	Vector3 m_position;
	float m_rotation;

	unsigned char m_rotAxis;
	float m_rotSpeed;

	bool m_xActive;
	bool m_yActive;
	bool m_zActive;

	float m_scale;

public:
	UnlitObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed, float scale = 1.0f);
	~UnlitObject();

	void Draw() override;
	void Update() override;

};

