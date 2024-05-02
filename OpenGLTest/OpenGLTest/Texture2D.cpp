#include "Texture2D.h"

#include <fstream>
#include <iostream>

Texture2D::Texture2D() 
{

}
Texture2D::~Texture2D() 
{
	glDeleteTextures(1, &m_ID);
}
bool Texture2D::Load(char* path, int width, int height) 
{
	char* tempTextureData;
	int fileSize;
	std::ifstream inFile;
	m_width = width, m_height = height;
	inFile.open(path, std::ios::binary);

	if (!inFile.good()) 
	{
		std::cout << "Problem with Texture File " << path << std::endl;
		return false;
	}

	inFile.seekg(0, std::ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char[fileSize];
	inFile.seekg(0, std::ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	std::cout << path << " loaded :)" << std::endl;

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData); // Do not do this, it just doesnt work :(
	

	delete[] tempTextureData;
	return true;

}
