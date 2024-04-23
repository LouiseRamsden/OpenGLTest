#include "MeshLoader.h"

#include <iostream>
#include <fstream>


namespace MeshLoader
{
	void LoadVertices(std::ifstream& inFile, Mesh& mesh);
	void LoadColours(std::ifstream& inFile, Mesh& mesh);
	void LoadIndices(std::ifstream& inFile, Mesh& mesh);

	void LoadVertices(std::ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColours(std::ifstream& inFile, Mesh& mesh)
	{
		//TODO: LOAD COLOURS
	}

	void LoadIndices(std::ifstream& inFile, Mesh& mesh)
	{
		//TODO: Load Indices
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		std::ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			std::cerr << "Can't open texture file " << path << std::endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE

		return mesh;
	}
}