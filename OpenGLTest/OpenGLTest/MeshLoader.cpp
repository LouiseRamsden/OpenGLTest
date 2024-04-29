#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


namespace MeshLoader
{
	void LoadVertices(std::vector<Vertex> tempVertices, Mesh& mesh);
	void LoadColors(std::vector<Vertex> tempVertices, Mesh& mesh);
	void LoadIndices(std::vector<GLushort> tempIndices, Mesh& mesh);

	void LoadVertices(std::vector<Vertex> tempVertices, Mesh& mesh)
	{
		mesh.Vertices = new Vertex[mesh.VertexCount];

		for (int i = 0; i < mesh.VertexCount; i++)
		{
			mesh.Vertices[i].x = tempVertices[i].x;
			mesh.Vertices[i].y = tempVertices[i].y;
			mesh.Vertices[i].z = tempVertices[i].z;
		}
	}

	void LoadColors(std::vector<Vertex> tempVertices, Mesh& mesh)
	{
		mesh.Colors = new Color[mesh.ColorCount];

		for (int i = 0; i < mesh.ColorCount; i++)
		{
			mesh.Colors[i].r = 1.0f;//mesh.Vertices[i].x;
			mesh.Colors[i].g = 1.0f;//mesh.Vertices[i].y;
			mesh.Colors[i].b = 1.0f;//mesh.Vertices[i].z;
		}
	}

	void LoadIndices(std::vector<GLushort> tempIndices, Mesh& mesh)
	{
		mesh.Indices = new GLushort[mesh.IndexCount];

		for (int i = 0; i < mesh.IndexCount; i++)
		{
			mesh.Indices[i] = tempIndices[i] - 1;
		}
	}
	void LoadTexCoords(std::vector<TexCoord>tempTexCoords, Mesh& mesh) 
	{
		mesh.TexCoords = new TexCoord[mesh.TexCoordsCount];
		for (int i = 0; i < mesh.TexCoordsCount; i++)
		{
			mesh.TexCoords[i].u = tempTexCoords[i].u;
			mesh.TexCoords[i].v = tempTexCoords[i].v;
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		std::ifstream inFile;
		inFile.open(path);
		if (!inFile.good())
		{
			std::cerr << "Can't open text file " << path << std::endl;
			return nullptr;
		}

		std::vector<GLushort> tempIndices;
		std::vector<Vertex> tempVertices;
		std::vector<TexCoord> tempTexCoords;
		std::vector<GLushort> tempTexCoordindices;
		std::string input;
		
		bool vertMode = false;
		bool indexMode = false;
		bool texCoordMode = false;
		
		int lineNum = 0;

		bool texIndicesInFile = false;

		for (std::string line; std::getline(inFile, line, '\n');)
		{

			std::istringstream a;
			a.str(line);
			for (std::string token; std::getline(a, token, ' ');)
			{
				if (vertMode == true)
				{
					switch(lineNum)
					{
					case 0:
						tempVertices[mesh->VertexCount - 1].x = (GLfloat)stof(token);
						break;
					case 1:
						tempVertices[mesh->VertexCount - 1].y = (GLfloat)stof(token);
						break;
					case 2:
						tempVertices[mesh->VertexCount - 1].z = (GLfloat)stof(token);
						break;
					}
					lineNum++;

				}
				if (texCoordMode == true) 
				{
					switch (lineNum)
					{
					case 0:
						tempTexCoords[mesh->TexCoordsCount - 1].u = (GLfloat)stof(token);
						break;
					case 1:
						tempTexCoords[mesh->TexCoordsCount - 1].v = (GLfloat)stof(token);
						break;
					}
					lineNum++;
				}
				if (indexMode == true)
				{
					std::istringstream b;
					b.str(token);
					uint8_t tokenCount = 0;
					for (std::string indexToken; std::getline(b, indexToken, '/');)
					{
						switch(tokenCount)
						{
						case 0:
							tempIndices[mesh->IndexCount - 3 + lineNum] = (GLushort)stoi(token);
							tokenCount++;
							break;
						case 1:
							tempTexCoordindices[mesh->TexCoordIndexCount - 3 + lineNum] = (GLushort)stoi(token);
							tokenCount++;
							break;
						default:
							break;
						}
						
					}
					lineNum++;
						

				}
				if (token == "v")
				{
					vertMode = true;
					indexMode = false;
					texCoordMode = false;
					tempVertices.push_back({ 0,0,0 });
					mesh->VertexCount++;
					lineNum = 0;
				}
				if (token == "vt")
				{
					texCoordMode = true;
					vertMode = false;
					indexMode = false;
					tempTexCoords.push_back({ 0,0 });
					mesh->TexCoordsCount++;
					lineNum = 0;

				}
				if (token == "f")
				{
					indexMode = true;
					vertMode = false;
					texCoordMode = false;
					tempIndices.push_back(0);
					tempIndices.push_back(0);
					tempIndices.push_back(0);
					tempTexCoordindices.push_back(0);
					tempTexCoordindices.push_back(0);
					tempTexCoordindices.push_back(0);
					mesh->IndexCount += 3;
					mesh->TexCoordIndexCount += 3;
					lineNum = 0;
				}




			}
			indexMode = false;
			vertMode = false;
			texCoordMode = false;
		}
		mesh->ColorCount = mesh->VertexCount;
		
		std::cout << mesh->TexCoordIndexCount << "\n";
		std::cout << mesh->TexCoordsCount << "\n";
	

		LoadVertices(tempVertices, *mesh);
		LoadColors(tempVertices, *mesh);
		LoadIndices(tempIndices, *mesh);
		LoadTexCoords(tempTexCoords, *mesh);
		//Load Tex Indices
		//Load TexNormals
		//Load Normal Indices

		return mesh;
	}
}