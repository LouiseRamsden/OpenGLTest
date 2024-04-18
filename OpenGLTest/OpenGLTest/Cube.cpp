#include "Cube.h"

Vertex* Cube::indexedVertices = nullptr;

Color* Cube::indexedColors = nullptr;

GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;

int Cube::numColors = 0;

int Cube::numIndices = 0;

Cube::Cube(float x, float y, float z, bool xRot, bool yRot, bool zRot, float rotSpeed) 
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
Cube::~Cube() 
{

}

void Cube::SetRotation(float rotation) 
{
	m_rotation = rotation;
	
}

void Cube::Draw()
{
	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr) 
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
		glColorPointer(3, GL_FLOAT, 0, indexedColors);

		glPushMatrix();
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotation, (float)m_xActive, (float)m_yActive, (float)m_zActive);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

void Cube::Update() 
{
	m_rotation += m_rotSpeed;
	if (m_rotation > 360.0f)
	{
		m_rotation -= 360.f;
	}
}

bool Cube::LoadTXT(char* path) 
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good()) 
	{
		std::cerr << "Can't open text file " << path << std::endl;
		return false;
	}

	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++) 
	{
		inFile >> indexedVertices[i].x;
		inFile >> indexedVertices[i].y;
		inFile >> indexedVertices[i].z;
	}
	inFile >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		inFile >> indexedColors[i].r;
		inFile >> indexedColors[i].g;
		inFile >> indexedColors[i].b;
	}
	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		inFile >> indices[i];
	}

	inFile.close();

	return true;

}

bool Cube::LoadOBJ(char* path) 
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file " << path << std::endl;
		return false;
	}

	Vertex vertexBuffer[20000];
	GLushort indicesBuffer[20000];

	char temp;
	
	while (!inFile.eof()) 
	{
		inFile >> temp;
		switch (temp) 
		{
		case 'v':
			inFile >> vertexBuffer[numVertices].x;
			inFile >> vertexBuffer[numVertices].y;
			inFile >> vertexBuffer[numVertices].z;
			numVertices++;
			break;
		case 'f':
			inFile >> indicesBuffer[numIndices];
			numIndices++;
			inFile >> indicesBuffer[numIndices];
			numIndices++;
			inFile >> indicesBuffer[numIndices];
			numIndices++;
			break;
		default:
			break;
		}
	}

	indexedVertices = new Vertex[numVertices];
	numColors = numVertices;
	indexedColors = new Color[numColors];
	indices = new GLushort[numIndices];
	for (int i = 0; i < numVertices; i++) 
	{
		vertexBuffer[i] = indexedVertices[i];
	}
	for (int i = 0; i < numColors; i++)
	{
		indexedColors[i] = { 0.0f,1.0f,0.0f };
	}
	for (int i = 0; i < numIndices; i++) 
	{
		indicesBuffer[i] = indices[i];
	}

	inFile.close();
	return true;
}