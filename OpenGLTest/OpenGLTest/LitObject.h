#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GL/freeglut.h"
#include "SceneObject.h"
#include "Structs.h"


class LitObject : public SceneObject
{
private:


	Vector3 m_position;
	float m_rotation;

	unsigned char m_rotAxis;
	float m_rotSpeed;

	bool m_xActive;
	bool m_yActive;
	bool m_zActive;

	Material* m_material;

public:
	LitObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed);
	~LitObject();

	void SetRotation(float rotation);
	void SetMaterial();
	void Draw() override;
	void Update() override;
};

