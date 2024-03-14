#include "GLScene.h"

GLScene::GLScene(int argc, char* argv[]) 
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hello World!");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void GLScene::Display() 
{
	
}

GLScene::~GLScene(void) 
{
}