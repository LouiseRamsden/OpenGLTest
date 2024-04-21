
#include "Cube.h"

#include <sstream>


Vertex* Cube::indexedVertices = nullptr;

Color* Cube::indexedColors = new Color[1];

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
		//glScalef(100.0f, 100.0f, 100.0f);
		glTranslatef(0.0f, -2.5f, 0.0f);
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
	

	//FILE* file = fopen(path, "r");
	//if (file == NULL) 
	//{
	//	std::cerr << "Unable to open file\n";
	//	return false;
	//}
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file " << path << std::endl;
		return false;
	}
	
	std::vector<GLushort> tempIndices;
	std::vector<Vertex> tempVertices;
	std::string input;
	bool vertMode = false;
	bool indexMode = false;
	int lineNum = 0;
	for (std::string line; std::getline(inFile, line,'\n');) 
	{
		
		std::istringstream a;
		a.str(line);		
		for (std::string token; std::getline(a, token, ' ');)
		{
			if (vertMode == true)
			{
				switch (lineNum)
				{
				case 0:
					tempVertices[numVertices - 1].x = (GLfloat)stof(token);
					break;
				case 1:
					tempVertices[numVertices - 1].y = (GLfloat)stof(token);
					break;
				case 2:
					tempVertices[numVertices - 1].z = (GLfloat)stof(token);
					break;
				}
				lineNum++;

			}
			if (indexMode == true) 
			{
				if (token != "f" || token!= "#")
				{
					tempIndices[numIndices - 3 + lineNum] = (GLushort)stoi(token);
					lineNum++;
				}

			}
			if (token == "v")
			{
				vertMode = true;
				indexMode = false;
				tempVertices.push_back({ 0,0,0 });
				numVertices++;
				lineNum = 0;
			}
			if (token == "f")
			{
				indexMode = true;
				vertMode = false;
				tempIndices.push_back(0);
				tempIndices.push_back(0);
				tempIndices.push_back(0);
				numIndices += 3;
				lineNum = 0;
			}

			
			
			
		}
		indexMode = false;
		vertMode = false;
	}

	numColors = numVertices;
	indices = new GLushort[numIndices];
	indexedVertices = new Vertex[numVertices];
	indexedColors = new Color[numColors];

	for (int i = 0; i < numVertices; i++)
	{
		 indexedVertices[i].z = tempVertices[i].z;
		 indexedVertices[i].y = tempVertices[i].y;
		 indexedVertices[i].x = tempVertices[i].x;
	}

	for (int i = 0; i < numIndices; i++)
	{
		indices[i] = tempIndices[i] - 1;
	}

	for (int i = 0; i < numColors; i++) 
	{
		indexedColors[i].r = indexedVertices[i].x;
		indexedColors[i].g = indexedVertices[i].y;
		indexedColors[i].b = indexedVertices[i].z;
	}

	std::cout << numIndices << " Indices" << std::endl;
	std::cout << numVertices << " Vertices" << std::endl;
	return true;
}
