#include "GLScene.h"

#include "MeshLoader.h"
#include "Utils.h"

#include <time.h>
#include <random>

//GLScene Constructor containing all GLUT init functions
GLScene::GLScene(int argc, char* argv[]) 
{	
	
	
	InitGL(argc, argv);
	InitObjects();

	//call glut main loop
	glutMainLoop();
	
}

//Display function, called continuously and draws screen
void GLScene::Display() 
{
	//Clear Image
	glClearColor(0.0f, 0.1f, 0.5f, 1.0f); // Set background Color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 100; i++)
		m_objects[i]->Draw();
	
	// 
	// 
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

	for (int i = 0; i < 100; i++)
		m_objects[i]->Update();
	
	//


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

void GLScene::InitObjects() 
{
	//camera init
	camera = new Camera();

	//Cube::LoadTXT((char*)"cube.txt");
	//load cubes
	Mesh* cowMesh = MeshLoader::Load((char*)"cow.obj");
	Mesh* teapotMesh = MeshLoader::Load((char*)"teapot.obj");
	//Cube::LoadTXT((char*)"cube.txt");

	//make cube(s)
	srand(time(NULL));
	for (int i = 0; i < 50; i++)
		m_objects[i] = new CowObject(
			cowMesh,
			RAND_IN_RANGE(50, -50),
			RAND_IN_RANGE(50, -50),
			RAND_IN_RANGE(50, -50),
			false,
			false,
			false,
			0.1f);

	for(int i = 50; i < 100; i++)
		m_objects[i] = new TeapotObject(
			teapotMesh,
			(rand() % (20 - -20 + 1)) + -20.0f,
			(rand() % (20 - -20 + 1)) + -20.0f,
			(rand() % (20 - -20 + 1)) + -20.0f,
			(bool)(rand() % 2),
			(bool)(rand() % 2),
			(bool)(rand() % 2),
			0.1f);

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
}

void GLScene::InitGL(int argc, char* argv[]) 
{
	//callback game scene init
	GLUTCallbacks::Init(this);

	//glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Object Rotation Simulator");




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
}

//Destructor
GLScene::~GLScene(void) 
{
	delete camera;
	camera = nullptr;
}