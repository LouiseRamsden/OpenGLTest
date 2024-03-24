#pragma once

class GLScene;

namespace GLUTCallbacks 
{
	void Init(GLScene* gl);

	void Display();

	void Timer(int refreshMS);

	void Keyboard(unsigned char key, int x, int y);
}
