#include "GLUTCallbacks.h"
#include "GLScene.h"

namespace GLUTCallbacks
{
	namespace
	{
		GLScene* glScene = nullptr;
	}

	//Set current GL Scene to passed value
	void Init(GLScene* gl)
	{
		glScene = gl;
	}

	//Callback function that links to GlScene Display
	void Display()
	{
		if (glScene != nullptr)
		{
			glScene->Display();
		}
	}

	void Timer(int refreshMS)
	{
		if (glScene != nullptr)
		{
			glScene->Update();
			glutTimerFunc(refreshMS, GLUTCallbacks::Timer, refreshMS);
		}
	}
}