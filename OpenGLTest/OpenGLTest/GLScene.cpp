#include "GLScene.h"

#include <time.h>

//GLScene Constructor containing all GLUT init functions
GLScene::GLScene(int argc, char* argv[]) 
{	
	//camera init
	camera = new Camera();

	//Cube::LoadTXT((char*)"cube.txt");
	//load cubes
	Cube::LoadOBJ((char*)"teapot.obj");
	//Cube::LoadTXT((char*)"cube.txt");

	//make cube(s)
	srand(time(NULL));
	for(int i = 0; i < 200; i++)
		cube[i] = new Cube(
		(rand() % (20 - -20 + 1)) + -20.0f,
			(rand() % (20 - -20 + 1)) + -20.0f,
			(rand() % (20 - -20 + 1)) + -20.0f,
			(bool)(rand() % 2),
			(bool)(rand() % 2),
			(bool)(rand() % 2),
			(rand() % (5 - -5 + 1)) + -5.0f);

	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = -20.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;//Temp

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
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

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	//set correct perspective
	gluPerspective(45, 1, 0.1f, 1000); //ZNEAR MUST BE NON ZERO

	

	//set matrixmode back to modelview
	glMatrixMode(GL_MODELVIEW);
	
	
	

	//enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	

	

	//call glut main loop
	glutMainLoop();
	
}

//Display function, called continuously and draws screen
void GLScene::Display() 
{
	//Clear Image
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 200; i++)
		cube[i]->Draw();
	//Flush GPU
	glFlush();
	glutSwapBuffers();
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

	for (int i = 0; i < 200; i++)
		cube[i]->Update();

	glutPostRedisplay();
}

void GLScene::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	//forward/backward
	case 'w':
		camera->eye.z -= 0.5f;
		camera->center.z -= 0.5f;
		break;
	case 's':
		camera->eye.z += 0.5f;
		camera->center.z += 0.5f;
		break;
	//left/right
	case 'a':
		camera->eye.x -= 0.5f;
		camera->center.x -= 0.5f;
		break;
	case 'd':
		camera->eye.x += 0.5f;
		camera->center.x += 0.5f;
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