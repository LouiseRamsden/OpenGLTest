#include "GLScene.h"

//GLScene Constructor containing all GLUT init functions
GLScene::GLScene(int argc, char* argv[]) 
{

	rotation = 0.0f;
	rotationSpeedMult = 10.0f;

	//callback game scene init
	GLUTCallbacks::Init(this);
	
	//glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello World");
	
	//glut callback settings
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	//call glut main loop
	glutMainLoop();
}

//Display function, called continuously and draws screen
void GLScene::Display() 
{
	//Clear Image
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw Polygon
	DrawPolygon();
	//Flush GPU
	glFlush();
	glutSwapBuffers();
}

//Tester draw polygon function, contains random draw calls for messing around
void GLScene::DrawPolygon() 
{

	glPushMatrix();
	glRotatef(rotation * rotationSpeedMult, 0.0f, 0.0f, -1.0f);
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
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotation * rotationSpeedMult, 1.0f, 0.0f, 1.0f);
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
	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.5f, 0.5f, 0.0f);
	glRotatef(rotation * rotationSpeedMult, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	{
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f); //Green
		glVertex2f(-0.25f,0.25f);
		glVertex2f(0.25f, 0.25f);
		glVertex2f(0.25f, -0.25f);
		glVertex2f(-0.25f, -0.25f);
	}
	glEnd();
	glPopMatrix();

}

void GLScene::Update() 
{

	rotation += 0.5f;
	if (rotation >= 360.0f)
		rotation = 0.0f;
	glutPostRedisplay();
}

void GLScene::Keyboard(unsigned char key, int x, int y) 
{
	if (key == 'd')
		rotationSpeedMult = 0.0f;
}

//Destructor
GLScene::~GLScene(void) 
{
}