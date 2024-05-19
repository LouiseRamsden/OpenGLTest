#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


namespace MeshLoader
{
	//Forward declarations
	void LoadVertices(std::vector<Vertex> tempVertices, Mesh& mesh);
	void LoadNormals(std::vector<Vector3> tempVertices, Mesh& mesh);
	void LoadIndices(std::vector<GLushort> tempIndices, Mesh& mesh);

	//Passes vector data for vertices and puts it into mesh vertices and color
	void LoadVertices(std::vector<Vertex> tempVertices, Mesh& mesh)
	{
		mesh.Vertices = new Vertex[mesh.VertexCount];
		mesh.Colors = new Color[mesh.VertexCount];
		for (int i = 0; i < mesh.VertexCount; i++)
		{
			mesh.Vertices[i].x = tempVertices[i].x;
			mesh.Vertices[i].y = tempVertices[i].y;
			mesh.Vertices[i].z = tempVertices[i].z;
			mesh.Colors[i].r = sinf(tempVertices[i].x * 100);
			mesh.Colors[i].g = sinf(tempVertices[i].y * 100);
			mesh.Colors[i].b = sinf(tempVertices[i].z * 100);
		}
	}
	//Pass vector data for normals and puts into mesh normals
	void LoadNormals(std::vector<Vector3> tempNormals, Mesh& mesh)
	{
		mesh.Normals = new Vector3[mesh.NormalCount];

		for (int i = 0; i < mesh.NormalCount; i++)
		{
			mesh.Normals[i].x = tempNormals[i].x;
			mesh.Normals[i].y = tempNormals[i].y;
			mesh.Normals[i].z = tempNormals[i].z;
		}
	}
	//Pass vector data for indices and puts into mesh indices 
	void LoadIndices(std::vector<GLushort> tempIndices, Mesh& mesh)
	{
		mesh.Indices = new GLushort[mesh.IndexCount];

		for (int i = 0; i < mesh.IndexCount; i++)
		{
			mesh.Indices[i] = tempIndices[i] - 1;
		}
	}
	//Pass vector data for TexCoords and puts into mesh texcoords
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

		// create empty mesh data
		Mesh* mesh = new Mesh();

		// load file from path into file stream
		std::ifstream inFile;
		inFile.open(path);
		// check if the file is okay
		if (!inFile.good())
		{
			std::cerr << "Can't open text file " << path << std::endl;
			return nullptr;
		}

		// temporary data storage for mesh data
		std::vector<GLushort> tempIndices;
		std::vector<Vertex> tempVertices;
		std::vector<TexCoord> tempTexCoords;
		std::vector<GLushort> tempTexCoordindices;
		std::vector<Vector3> tempNormals;

		// booleans to confirm which mode it is inputting for the line
		bool vertMode = false;
		bool indexMode = false;
		bool texCoordMode = false;
		bool normalMode = false;

		// column count
		int lineNum = 0;

		// Loop on file splitting by new line
		for (std::string line; std::getline(inFile, line, '\n');)
		{
			// create string stream, input the line data
			std::istringstream a;
			a.str(line);
			
			// use that line data and split it by spaces
			for (std::string token; std::getline(a, token, ' ');)
			{
				
				// if the line is vertex data
				if (vertMode == true)
				{
					//based on the column take token, convert to float, and put in vector
					switch (lineNum)
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

				// if the line is texcoord data
				if (texCoordMode == true)
				{
					//based on the column take token, convert to float, and put in vector
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

				// if the line is normal data
				if (normalMode == true)
				{
					//based on the column take token, convert to float, and put in vector
					switch (lineNum)
					{
					case 0:
						tempNormals[mesh->NormalCount - 1].x = (GLfloat)stof(token);
						break;
					case 1:
						tempNormals[mesh->NormalCount - 1].y = (GLfloat)stof(token);
						break;
					case 2:
						tempNormals[mesh->NormalCount - 1].z = (GLfloat)stof(token);
						break;
					}
					lineNum++;
				}

				// if the line is index data
				if (indexMode == true)
				{
					// for expansion uses only, create new string stream, splitting on /
					std::istringstream b;
					b.str(token);
					for (std::string indexToken; std::getline(b, indexToken, '/');)
					{
						// insert index into the the vector casting it to a GLushort
						tempIndices[mesh->IndexCount - 3 + lineNum] = (GLushort)stoi(indexToken);
						break;
					}
					lineNum++;


				}

				// if the first thing in the line is v
				if (token == "v")
				{
					// deactivate all modes and turn vertex mode on
					vertMode = true;
					indexMode = false;
					texCoordMode = false;
					normalMode = false;
					// create space for the vertex in the vector
					tempVertices.push_back({ 0,0,0 });
					// increment the vertex count in the mesh data
					mesh->VertexCount++;
					// set line num back to zero
					lineNum = 0;
				}
				if (token == "vt")
				{
					// deactivate all modes and turn texcoord mode on
					texCoordMode = true;
					vertMode = false;
					indexMode = false;
					normalMode = false;
					// create space for texcoord in the vector
					tempTexCoords.push_back({ 0,0 });
					// increment the texcoord amount
					mesh->TexCoordsCount++;
					// set line num back to zero
					lineNum = 0;

				}
				if (token == "vn")
				{
					// deactivate all modes and turn texcoord mode on
					indexMode = false;
					vertMode = false;
					texCoordMode = false;
					normalMode = true;
					// create space for normal vector in vector
					tempNormals.push_back({ 0,0,0 });
					// increment normal amount
					mesh->NormalCount++;
					// set line num back to zero
					lineNum = 0;

				}
				if (token == "f")
				{
					// deactivate all modes, turn on index mode on
					indexMode = true;
					vertMode = false;
					texCoordMode = false;
					normalMode = false;
					// create space for indices
					tempIndices.push_back(0);
					tempIndices.push_back(0);
					tempIndices.push_back(0);
					// increment index count by 3
					mesh->IndexCount += 3;
					// set line num to 0
					lineNum = 0;
				}
			}
			// deactivate all modes
			indexMode = false;
			vertMode = false;
			texCoordMode = false;
			normalMode = false;

		}

		

		LoadVertices(tempVertices, *mesh);
		LoadNormals(tempNormals, *mesh);
		LoadIndices(tempIndices, *mesh);
		LoadTexCoords(tempTexCoords, *mesh);
		//Load Tex Indices
		//Load TexNormals
		//Load Normal Indices

		return mesh; // return new mesh
	}
}