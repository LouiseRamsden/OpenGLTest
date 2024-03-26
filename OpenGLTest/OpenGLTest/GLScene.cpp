#include "GLScene.h"

//GLScene Constructor containing all GLUT init functions
GLScene::GLScene(int argc, char* argv[]) 
{

	rotation = 0.0f;
	rotationSpeedMult = 10.0f;
	
	//camera init
	camera = new Camera();

	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;

	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;

	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
	//callback game scene init
	GLUTCallbacks::Init(this);
	
	//glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Teapot Rotator Simulator");
	
	//glut callback settings
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);



	//set matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport to be entire window
	glViewport(0, 0, 800, 800);

	// set correct perspective
	gluPerspective(45, 1, 0, 1000);

	//set matrixmode back to modelview
	glMatrixMode(GL_MODELVIEW);
	
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
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glutWireTeapot(0.1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glutWireCube(0.4);
	glPopMatrix();

}

void GLScene::Update() 
{
	// resets modelview matrix
	glLoadIdentity();

	//camera lookat (Hell Function Call)
	gluLookAt(camera->eye.x,
		camera->eye.y,
		camera->eye.z,
		camera->center.x,
		camera->center.y,
		camera->center.z,
		camera->up.x,
		camera->up.y,
		camera->up.z);

	if (rotation >= 360.0f)
		rotation = 0.0f;
	glutPostRedisplay();
}

void GLScene::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	//forward/backward
	case 'w':
		camera->eye.z -= 0.05f;
		camera->center.z -= 0.05f;
		break;
	case 's':
		camera->eye.z += 0.05f;
		camera->center.z += 0.05f;
		break;
	//left/right
	case 'a':
		camera->eye.x -= 0.05f;
		camera->center.x -= 0.05f;
		break;
	case 'd':
		camera->eye.x += 0.05f;
		camera->center.x += 0.05f;
		break;
	//rotate
	case 'q':
		camera->center.x -= 0.05f;
		camera->center.z -= 0.05f;
		break;
	case 'e':
		camera->center.x += 0.05f;
		camera->center.z += 0.05f;
		break;
	default:
		break;
		


	}



}

//Destructor
GLScene::~GLScene(void) 
{
	delete camera;
	camera = nullptr;
}