#include "GLScene.h"

#include "MeshLoader.h"
#include "Utils.h"

#include <time.h>
#include <random>
#include <string>

//GLScene Constructor calls initialization and the glut mainloop
GLScene::GLScene(int argc, char* argv[]) 
{	
	
	
	InitGL(argc, argv);
	InitObjects();
	InitLighting();
	//call glut main loop
	glutMainLoop();
	
}

//Display function, called continuously and draws screen
void GLScene::Display() 
{	
	//Clear Image
	glClearColor(0.0f, 0.1f, 0.5f, 1.0f); // Set background Color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw Objects
	for (int i = 0; i < 50; i++)
		m_objects[i]->Draw();
	
	for (int i = 50; i < 100; i++)
		m_objects[i]->Draw();

	//Drawing Text
	Vector3 v = { camera->center.x + 8.0f, camera->center.y + 7.5f, camera->center.z - 0.5f};
	Color c = { 1.0f, 1.0f, 0.0f };
	DrawString("Hello", &v, &c);
	
	//Flush GPU
	glFlush();
	glutSwapBuffers();
}

//Updates everything, manages movement, camera and lighting
void GLScene::Update() 
{
	//resets modelview matrix
	glLoadIdentity();

	//camera lookat
	gluLookAt(camera->eye.x,
		camera->eye.y,
		camera->eye.z,
		camera->center.x,
		camera->center.y,
		camera->center.z,
		camera->up.x,
		camera->up.y,
		camera->up.z);

	//Lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(m_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(m_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(m_lightPosition->x));

	//Update Objects
	for (int i = 0; i < 50; i++)
		m_objects[i]->Update();
	for (int i = 50; i < 100; i++)
		m_objects[i]->Update();

	//Redisplay Screen
	glutPostRedisplay();
}

//Keyboard Handles all input from the keyboards alphanumeric keys
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

//Init Objects, initializes all the objects and textures and the camera, and makes sure that they are loaded and initialized
void GLScene::InitObjects() 
{
	//camera init
	camera = new Camera();

	//load objects
	Mesh* texturedCubeMesh = MeshLoader::Load((char*)"cubeTexturable.obj");
	Mesh* cowMesh = MeshLoader::Load((char*)"cow.obj");
	Mesh* teapotMesh = MeshLoader::Load((char*)"teapot.obj");

	//load textures
	Texture2D* penguinTexture = new Texture2D();
	penguinTexture->Load((char*)"penguins.raw", 512, 512);

	//make objects
	srand(time(NULL));
	for (int i = 0; i < 50; i++)
		m_objects[i] = new LitObject(
			texturedCubeMesh,
			penguinTexture,
			RAND_IN_RANGE(15, -15),
			RAND_IN_RANGE(15, -15),
			RAND_IN_RANGE(15, -15),
			true,
			false,
			true,
			0.1f);
	for (int i = 50; i < 100; i++)
		m_objects[i] = new UnlitObject(
			cowMesh,
			penguinTexture,
			RAND_IN_RANGE(15, -15),
			RAND_IN_RANGE(15, -15),
			RAND_IN_RANGE(15, -15),
			true,
			false,
			true,
			0.1f);

	//Camera initializing
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

//Initializes lighting
void GLScene::InitLighting() 
{
	
	//Direction of the light
	m_lightPosition = new Vector4();
	m_lightPosition->x = 0.0;
	m_lightPosition->y = 1.0;
	m_lightPosition->z = 0.0;
	m_lightPosition->w = 0.0;

	//Create lighting
	m_lightData = new Lighting();

	//Ambient: uniform ambient light over the object
	m_lightData->Ambient.x = 0.2;
	m_lightData->Ambient.y = 0.2;
	m_lightData->Ambient.z = 0.2;
	m_lightData->Ambient.w = 1.0;
	//Diffuse: what colour the object is
	m_lightData->Diffuse.x = 0.8;
	m_lightData->Diffuse.y = 0.8;
	m_lightData->Diffuse.z = 0.8;
	m_lightData->Diffuse.w = 1.0;
	//Specular: reflected light
	m_lightData->Specular.x = 0.2;
	m_lightData->Specular.y = 0.2;
	m_lightData->Specular.z = 0.2;
	m_lightData->Specular.w = 1.0;

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

	glEnable(GL_TEXTURE_2D);

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	//set correct perspective
	gluPerspective(45, 1, 0.1f, 1000); //ZNEAR MUST BE NON ZERO



	//set matrixmode back to modelview
	glMatrixMode(GL_MODELVIEW);




	//enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void GLScene::DrawString(const char* text, Vector3* position, Color* color) 
{
	glPushMatrix();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

//Destructor
GLScene::~GLScene(void) 
{
	delete camera;
	camera = nullptr;
}