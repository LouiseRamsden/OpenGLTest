#include "GLScene.h"

GLScene::GLScene(int argc, char* argv[]) 
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hello World");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void GLScene::Display() 
{
	//Clear Image
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw Objects
	DrawPolygon();
	//Flush GPU
	glFlush();
}

void GLScene::DrawPolygon() 
{
	//Begin Drawing
	glBegin(GL_POLYGON);
	{
		//Draw Object
		//GlColor before vertexes
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f); //Red
		glVertex2f(1.0f, 0.75);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f); //Green
		glVertex2f(0.5f, 0.0f);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f); //Blue
		glVertex2f(-1.0f, -0.25f);
		//End Drawing
		glEnd();
	}
	for (int i = 0; i < 100; i++) 
	{
		glBegin(GL_POLYGON); 
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(1.0f / (float)i, 1.0f / (float)i);
			glVertex2f(1.0f / (float)i, 0.9f / (float)i);
			glVertex2f(0.9f / (float)i, 0.9f / (float)i);
			glVertex2f(0.9f / (float)i, 1.0f / (float)i);
			glEnd();
		}
		glBegin(GL_POLYGON);
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(1.0f / (float)-i, 1.0f / (float)-i);
			glVertex2f(1.0f / (float)-i, 0.9f / (float)-i);
			glVertex2f(0.9f / (float)-i, 0.9f / (float)-i);
			glVertex2f(0.9f / (float)-i, 1.0f / (float)-i);
			glEnd();
		}
		glBegin(GL_POLYGON);
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(1.0f - (float)i/50, 1.0f / (float)i);
			glVertex2f(1.0f - (float)i/50, 0.9f / (float)i);
			glVertex2f(0.9f - (float)i/50, 0.9f / (float)i);
			glVertex2f(0.9f - (float)i/50, 1.0f / (float)i);
			glEnd();
		}
		glBegin(GL_POLYGON);
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(1.0f / (float)i, 1.0f - (float)i/50);
			glVertex2f(1.0f / (float)i, 0.9f - (float)i/50);
			glVertex2f(0.9f / (float)i, 0.9f - (float)i/50);
			glVertex2f(0.9f / (float)i, 1.0f - (float)i/50);
			glEnd();
		}
	}

	
}

GLScene::~GLScene(void) 
{
}