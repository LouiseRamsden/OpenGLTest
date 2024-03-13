#include "GLUTCallbacks.h"
#include "GLScene.h"

namespace GLUTCallbacks 
{
	namespace 
	{
		GLScene* glScene = nullptr;
	}

	void Init(GLScene* gl) 
	{
		glScene = gl;
	}

	void Display() 
	{
		if (glScene != nullptr) 
		{
			glScene->Display();
		}
	}
}