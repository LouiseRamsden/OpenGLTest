#include "GLScene.h"

Vertex GLScene::vertices[] = {
	1, 1, 1, -1, 1, 1, -1,-1, 1,	// v0-v1-v2 (front)
	-1,-1, 1, 1,-1, 1, 1, 1, 1,		// v2-v3-v0
	1, 1, 1, 1,-1, 1, 1,-1,-1,		// v0-v3-v4 (right)
	1,-1,-1, 1, 1,-1, 1, 1, 1,		// v4-v5-v0
	1, 1, 1, 1, 1,-1, -1, 1,-1,		// v0-v5-v6 (top)
	-1, 1,-1, -1, 1, 1, 1, 1, 1,	// v6-v1-v0
	-1, 1, 1, -1, 1,-1, -1,-1,-1,	// v1-v6-v7 (left)
	-1,-1,-1, -1,-1, 1, -1, 1, 1,	// v7-v2-v1
	-1,-1,-1, 1,-1,-1, 1,-1, 1,		// v7-v4-v3 (bottom)
	1,-1, 1, -1,-1, 1, -1,-1,-1,	// v3-v2-v7
	1,-1,-1, -1,-1,-1, -1, 1,-1,	// v4-v7-v6 (back)
	-1, 1,-1, 1, 1,-1, 1,-1,-1		// v6-v5-v4
}; 

Color GLScene::colors[] = { 
	1, 1, 1, 1, 1, 0, 1, 0, 0, // v0-v1-v2 (front)
	1, 0, 0, 1, 0, 1, 1, 1, 1, // v2-v3-v0
	1, 1, 1, 1, 0, 1, 0, 0, 1, // v0-v3-v4 (right)
	0, 0, 1, 0, 1, 1, 1, 1, 1, // v4-v5-v0
	1, 1, 1, 0, 1, 1, 0, 1, 0, // v0-v5-v6 (top)
	0, 1, 0, 1, 1, 0, 1, 1, 1, // v6-v1-v0
	1, 1, 0, 0, 1, 0, 0, 0, 0, // v1-v6-v7 (left)
	0, 0, 0, 1, 0, 0, 1, 1, 0, // v7-v2-v1
	0, 0, 0, 0, 0, 1, 1, 0, 1, // v7-v4-v3 (bottom)
	1, 0, 1, 1, 0, 0, 0, 0, 0, // v3-v2-v7
	0, 0, 1, 0, 0, 0, 0, 1, 0, // v4-v7-v6 (back)
	0, 1, 0, 0, 1, 1, 0, 0, 1 // v6-v5-v4 
}; 

Vertex GLScene::indexedVertices[] = { 
	1, 1, 1, -1, 1, 1,	// v0,v1,
	-1,-1, 1, 1,-1, 1,	// v2,v3
	1,-1,-1, 1, 1,-1,	// v4,v5
	-1, 1,-1, -1,-1,-1	// v6,v7 
}; 

Color GLScene::indexedColors[] = { 
	1, 1, 1, 1, 1, 0,	// v0,v1,
	1, 0, 0, 1, 0, 1,	// v2,v3
	0, 0, 1, 0, 1, 1,	// v4,v5
	0, 1, 0, 0, 0, 0	//v6,v7 
}; 

GLushort GLScene::indices[] = { 
	0, 1, 2, 2, 3, 0,	// front
	0, 3, 4, 4, 5, 0,	// right
	0, 5, 6, 6, 1, 0,	// top
	1, 6, 7, 7, 2, 1,	// left
	7, 4, 3, 3, 2, 7,	// bottom
	4, 7, 6, 6, 5, 4	// back
}; 

//GLScene Constructor containing all GLUT init functions
GLScene::GLScene(int argc, char* argv[]) 
{

	rotation = 0.0f;
	rotationSpeedMult = 10.0f;
	
	//camera init
	camera = new Camera();

	//camera->eye.x = 0.0f;
	//camera->eye.y = 0.0f;
	//camera->eye.z = 1.0f;
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;//Temp

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
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw Polygon
	//DrawPolygon();
	//DrawCubeArray();
	DrawCubeArrayAlt();
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

void GLScene::DrawCube() 
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	
	// face v0-v1-v2

	glColor3f(1, 1, 1);

	glVertex3f(1, 1, 1);

	glColor3f(1, 1, 0);

	glVertex3f(-1, 1, 1);

	glColor3f(1, 0, 0);

	glVertex3f(-1, -1, 1);

	// face v2-v3-v0

	glColor3f(1, 0, 0);

	glVertex3f(-1, -1, 1);

	glColor3f(1, 0, 1);

	glVertex3f(1, -1, 1);

	glColor3f(1, 1, 1);

	glVertex3f(1, 1, 1);

	// face v0-v3-v4

	glColor3f(1, 1, 1);

	glVertex3f(1, 1, 1);

	glColor3f(1, 0, 1);

	glVertex3f(1, -1, 1);

	glColor3f(0, 0, 1);

	glVertex3f(1, -1, -1);

	// face v4-v5-v0

	glColor3f(0, 0, 1);

	glVertex3f(1, -1, -1);

	glColor3f(0, 1, 1);

	glVertex3f(1, 1, -1);

	glColor3f(1, 1, 1);

	glVertex3f(1, 1, 1);

	// face v0-v5-v6

	glColor3f(1, 1, 1);

	glVertex3f(1, 1, 1);

	glColor3f(0, 1, 1);

	glVertex3f(1, 1, -1);

	glColor3f(0, 1, 0);

	glVertex3f(-1, 1, -1);

	// face v6-v1-v0

	glColor3f(0, 1, 0);

	glVertex3f(-1, 1, -1);

	glColor3f(1, 1, 0);

	glVertex3f(-1, 1, 1);

	glColor3f(1, 1, 1);

	glVertex3f(1, 1, 1);

	// face v1-v6-v7

	glColor3f(1, 1, 0);

	glVertex3f(-1, 1, 1);

	glColor3f(0, 1, 0);

	glVertex3f(-1, 1, -1);

	glColor3f(0, 0, 0);

	glVertex3f(-1, -1, -1);

	// face v7-v2-v1

	glColor3f(0, 0, 0);

	glVertex3f(-1, -1, -1);

	glColor3f(1, 0, 0);

	glVertex3f(-1, -1, 1);

	glColor3f(1, 1, 0);

	glVertex3f(-1, 1, 1);

	// face v7-v4-v3

	glColor3f(0, 0, 0);

	glVertex3f(-1, -1, -1);

	glColor3f(0, 0, 1);

	glVertex3f(1, -1, -1);

	glColor3f(1, 0, 1);

	glVertex3f(1, -1, 1);

	// face v3-v2-v7

	glColor3f(1, 0, 1);

	glVertex3f(1, -1, 1);

	glColor3f(1, 0, 0);

	glVertex3f(-1, -1, 1);

	glColor3f(0, 0, 0);

	glVertex3f(-1, -1, -1);

	// face v4-v7-v6

	glColor3f(0, 0, 1);

	glVertex3f(1, -1, -1);

	glColor3f(0, 0, 0);

	glVertex3f(-1, -1, -1);

	glColor3f(0, 1, 0);

	glVertex3f(-1, 1, -1);

	// face v6-v5-v4

	glColor3f(0, 1, 0);

	glVertex3f(-1, 1, -1);

	glColor3f(0, 1, 1);

	glVertex3f(1, 1, -1);

	glColor3f(0, 0, 1);

	glVertex3f(1, -1, -1);

	glEnd();
	glPopMatrix();
}

void GLScene::DrawCubeArray() 
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++) 
	{
		glColor3fv(&colors[i].r);
		glVertex3fv(&vertices[i].x);
	}
	glEnd();
	glPopMatrix();
}
void GLScene::DrawCubeArrayAlt() 
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glPushMatrix();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void GLScene::DrawIndexedCube() 
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++) 
	{
		glColor3f(indexedColors[indices[i]].r, indexedColors[indices[i]].g, indexedColors[indices[i]].b);
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
	}
	glEnd();
	glPopMatrix();
}

void GLScene::DrawIndexedCubeAlt() 
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
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
		rotation = rotation - 360.0f;
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
	//rotate object
	case 'q':
		rotation -= 5.0f;
		break;
	case 'e':
		rotation += 5.0f;
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