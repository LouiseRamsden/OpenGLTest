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
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			glScene->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(refreshMS - updateTime, GLUTCallbacks::Timer, refreshMS);
		}
	}

	void Keyboard(unsigned char key, int x, int y) 
	{
		glScene->Keyboard(key, x, y);
	}
}