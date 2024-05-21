#include "GLScene.h"

#include "MeshLoader.h"
#include "Utils.h"

#include <time.h>
#include <random>
#include <string>
#include <iostream>

#define OBJ_NUM 5

//GLScene Constructor calls initialization and the glut mainloop
GLScene::GLScene(int argc, char* argv[]) 
{	
	
	for (int i = 0; i < OBJ_NUM; i++) 
	{
		m_objMoving[i] = false;
	}
	
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
	for (int i = 0; i < OBJ_NUM; i++)
		m_objects[i]->Draw();

	//Drawing Text
	Vector3 v = { camera->center.x + 2.5f, camera->center.y + 7.5f, camera->center.z};
	Vector3 v2 = { camera->center.x + 2.5f, camera->center.y + 5.5f, camera->center.z };
	Vector3 v3 = { camera->center.x + 2.5f, camera->center.y + 3.5f, camera->center.z };
	Color c = { 0.0f, 1.0f, 0.0f };
	DrawString("Press 1-5 to move the objects", &v, &c);
	DrawString("WASD to move, Mouse to rotate", &v2, &c);
	DrawString("Press E to Centre camera on bunny", &v3, &c);

	for (int i = 0; i < OBJ_NUM; i++) 
	{
		Vector3 v4 = { m_objects[i]->GetPosition().x,m_objects[i]->GetPosition().y - 3.0f,m_objects[i]->GetPosition().z };
		if (m_objects[i]->spinning == true) 
		{
			DrawString("^ SPINNING!!", &v4, &c);
		}
		else 
		{
			DrawString(" ^ NO SPINNING :(" ,&v4, &c);
		}
			
	}
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
	for (int i = 0; i < OBJ_NUM; i++)
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
		camera->eye.z += 0.5f;
		camera->center.z += 0.5f;
		break;
	case 's':
		camera->eye.z -= 0.5f;
		camera->center.z -= 0.5f;
		break;
	//left/right
	case 'a':
		camera->eye.x += 0.5f;
		camera->center.x += 0.5f;
		break;
	case 'd':
		camera->eye.x -= 0.5f;
		camera->center.x -= 0.5f;
		break;
	case 'e':
		camera->center = m_objects[2]->GetPosition();
		break;
	case '1':
		if (m_objects[0]->spinning == false)
		{
			m_objects[0]->spinning = true;
		}
		else
		{
			m_objects[0]->spinning = false;
		}
		break;
	case '2':
		if (m_objects[1]->spinning == false)
		{
			m_objects[1]->spinning = true;
		}
		else
		{
			m_objects[1]->spinning = false;
		}
		break;
	case '3':
		if (m_objects[2]->spinning == false)
		{
			m_objects[2]->spinning = true;
		}
		else
		{
			m_objects[2]->spinning = false;
		}
		break;
	case '4':
		if (m_objects[3]->spinning == false)
		{
			m_objects[3]->spinning = true;
		}
		else
		{
			m_objects[3]->spinning = false;
		}
		break;
	case '5':
		if (m_objects[4]->spinning == false)
		{
			m_objects[4]->spinning = true;
		}
		else
		{
			m_objects[4]->spinning = false;
		}
		break;
	default:
		break;
	}



}

void GLScene::PassiveMotion(int x, int y) 
{
	camera->center.x = ((float)x - 400) / 90.0f;
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
	Mesh* bunnyMesh = MeshLoader::Load((char*)"bunny.obj");
	
	//load textures
	Texture2D* noTexture = new Texture2D();
	Texture2D* penguinTexture = new Texture2D();
	penguinTexture->Load((char*)"penguins.raw", 512, 512);
	Texture2D* starsTexture = new Texture2D();
	starsTexture->Load((char*)"stars.raw", 512, 512);
	//make objects
		
		m_objects[0] = new UnlitObject(
			teapotMesh,
			noTexture,
			10.0f,
			0,
			0.0f,
			true,
			false,
			true,
			0.1f,
			0.8f);
		m_objects[1] = new UnlitObject(
			cowMesh,
			noTexture,
			5.0f,
			0,
			0.0f,
			true,
			false,
			true,
			0.1f,
			0.4f);
		m_objects[2] = new UnlitObject(
			bunnyMesh,
			noTexture,
			0.0f,
			-0.25f,
			0.0f,
			true,
			false,
			true,
			0.1f,
			15.0f);
		m_objects[3] = new LitObject(
			texturedCubeMesh,
			penguinTexture,
			starsTexture,
			-5.0f,
			0,
			0.0f,
			true,
			true,
			true,
			0.1f);
		m_objects[4] = new LitObject(
			texturedCubeMesh,
			penguinTexture,
			starsTexture,
			-10.0f,
			0,
			0.0f,
			true,
			true,
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

	//glut init functions
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The Museum");

	//glut callback settings
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutPassiveMotionFunc(GLUTCallbacks::PassiveMotion);

	//set matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport to be entire window
	glViewport(0, 0, 800, 800);
	
	//Enable texturing
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
//Draw text at location 
void GLScene::DrawString(const char* text, Vector3* position, Color* color) 
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslatef(position->x, position->y, position->z);
	glColor3f(color->r, color->g, color->b);
	glRasterPos2f(0.0f,0.0f);
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