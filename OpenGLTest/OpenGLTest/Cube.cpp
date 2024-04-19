
#include "Cube.h"



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
	bool vertMode;
	bool indexMode;
	int lineNum = 0;
	for (std::string line; std::getline(inFile, line, ' ');)
	{
		if (line == "v" || line.find("v"))
		{
			vertMode = true;
			indexMode = false;
			tempVertices.push_back({ 0,0,0 });
			numVertices++;
			lineNum = 0;
		}
		if (line == "f" || line.find("f"))
		{
			indexMode = true;
			vertMode = false;
			tempIndices.push_back(0);
			tempIndices.push_back(0);
			tempIndices.push_back(0);
			numIndices += 3;
			lineNum = 0;
		}
		std::cout << line << std::endl;
	}
	std::cout << numIndices << "Number Of Indices" << std::endl;
	std::cout << numVertices << "Number of Vertices" << std::endl;
	return true;
}
//	while (true)
//	{
//
//
//
//
//
//		if (strcmp(lineHeader, "v") == 0) 
//		{
//			Vertex vertex;
//			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
//			tempVertices.push_back(vertex);
//			numVertices++;
//		}
//		else if (strcmp(lineHeader, "f") == 0) 
//		{
//			GLuint vertexIndex[3];
//
//			int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
//			if (matches != 3) 
//			{
//				std::cerr << "Error with file";
//				return false;
//			}
//			
//
//			tempIndices.push_back(vertexIndex[0]);
//			tempIndices.push_back(vertexIndex[1]);
//			tempIndices.push_back(vertexIndex[2]);
//			
//			numIndices += 3;
//		}
//	}
//	indexedVertices = new Vertex[numVertices];
//	indexedColors = new Color[numVertices];
//	numColors = numVertices;
//	for (int i = 0; i < numVertices; i++) 
//	{
//		indexedVertices[i] = tempVertices[i];
//	}
//	
//	for (int i = 0; i < numColors; i++)
//	{
//		indexedColors[i].r = (float) 1/(i/1000);
//		indexedColors[i].g = 0.0f;
//		indexedColors[i].b = 0.0f;
//	}
//	indices = new GLushort[numIndices];
//	for (int i = 0; i < numIndices; i++) 
//	{
//		indices[i] = tempIndices[i];
//	}
//
//	return true;
//
//}

//Rewrite the general gist of this in C++ style, and then see if it works.