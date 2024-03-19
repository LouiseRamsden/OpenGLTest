#pragma once

class GLScene;

namespace GLUTCallbacks 
{
	void Init(GLScene* gl);

	void Display();

	void Timer(int refreshMS);
}
