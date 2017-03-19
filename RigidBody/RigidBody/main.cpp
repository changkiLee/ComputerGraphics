#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <time.h>
#include <windows.h>
#include <gl/glut.h>
#include "rigidSystem.h"

// 화면의 크기
int Width = 800, Height = 800;

// delta t
static float dTime = 0;

/////////////////////////////////////
RigidSystem rig;
Box* r_box = new Box(5, 2, 3, 1);	// x, y, z, m
/////////////////////////////////////

enum ManipuatedMode
{
	NONE = -1,
	PAN = 0,
	ROTATE = 1,
	ZOOM = 2,
};

ManipuatedMode CurrManipulateMode = NONE;

// 관측변환을 위한 변수
int StartPt[2];
float Axis[3] = {1.0, 0.0, 0.0};
float Angle = 0.0;
float RotMat[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
float Pan[2] = {0.0f, 0.0f};
float Zoom = 1.0f;

// Forward declaration of functions
void Reshape(int w, int h);
void Render();
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);

void GetSphereCoord(int x, int y, float *px, float *py, float *pz);

// 개체를 그리는 함수
void CreateObject();
void RenderFloor();
void RenderBox();
void ActionObjects();

int main(int argc, char **argv)
{
	// Initialize OpenGL.
	glutInit(&argc, argv);

	// Initialize window size and its position when it is created.
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);

	// Initialize OpenGL display modes for double buffering, RGB color, depth buffer enabling.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create OpenGL window.
	glutCreateWindow("RigidBody");

	// Register call back functions.
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(ActionObjects);

	CreateObject();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	

	// Enter the message loop.
	glutMainLoop();
	return 0;
}

void Reshape(int w, int h)
{
	// View-port transformation
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void Keyboard(unsigned char key, int x, int y)
{
	External *external_force = NULL;

	switch (key)
	{
	case 'q':
		CurrManipulateMode = PAN;
		break;
	case'w':
		CurrManipulateMode = ROTATE;
		break;
	case 'e':
		CurrManipulateMode = ZOOM;
		break;

	case '1':
		{
			rig.init();
			external_force = new External(GVector3(0.0f, 10.0f, 0.0f), 1, 1.0f);
			rig.addForce(external_force);
			break;
		}
	case '2':
		{
			rig.init();
			external_force = new External(GVector3(0.0f, 10.0f, -3.0f), 2, 1.0f);
			rig.addForce(external_force);
			break;
		}
	case '3':
		{
			rig.init();
			external_force = new External(GVector3(0.0f, 10.0f, 3.0f), 3, 1.0f);
			rig.addForce(external_force);
			break;
		}
	case '4':
		{
			rig.init();
			external_force = new External(GVector3(3.0f, 10.0f, -3.0f), 4, 1.0f);
			rig.addForce(external_force);
			break;
		}
	case '5':
		{
			rig.init();
			GVector3 pt(0.0f, 20.0f, 0.0f);
			r_box->setPos(pt);
			rig.addBox(r_box);
		}
		break;
	}
}

void SetupViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, -10.0f, -30.0f);		// 카메라 위치 조절

	glTranslatef(Pan[0], Pan[1], 0.0f);	
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

	glMultMatrixf(RotMat);
	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);	
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0*Zoom, 1.0f, 5.0f, 100.0f);
}

void Render()
{
	// Clear color buffer with specified clear color (R, G, B, A)
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up view transformation
	SetupViewTransform();

	// Set up viewing volume and choose camera lens
	SetupViewVolume();	

	glMatrixMode(GL_MODELVIEW);
	// 바닥 그리기
	RenderFloor();

	// 박스 그리기
	rig.rigidRender();

	// Swap buffers for double buffering.
	glutSwapBuffers();
}

void RenderFloor()
{
	glDisable(GL_LIGHTING);

	for (int i = 0; i < 100; ++i)
	{
		float x, z;
		x = z = (double)i / 39 * 50.0 - 50.0;

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(x, 0.0, -50.0f);
		glVertex3f(x, 0.0, 50.0f);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(-50.0f, 0.0, z);
		glVertex3f(50.0f, 0.0, z);
		glEnd();

	}
	glEnable(GL_LIGHTING);
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x;
		StartPt[1] = y;
	}

	if (state == GLUT_UP)
	{
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void MouseMove(int x, int y)
{
	switch (CurrManipulateMode)
	{
	case PAN:
		Pan[0] += (x - StartPt[0]) * 0.01f;
		Pan[1] += (StartPt[1] - y) * 0.01f;
		break;
	case ROTATE:
		{
			float px, py, pz, qx, qy, qz;
			GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
			GetSphereCoord(x, y, &qx, &qy, &qz);
			Axis[0] = py * qz - pz * qy;
			Axis[1] = pz * qx - px * qz;
			Axis[2] = px * qy - py * qx;
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
		}
		break;
	case ZOOM:
		{
			float dy = (StartPt[1] - y) * 0.01f;
			Zoom += dy;
		}
		break;
	}
	StartPt[0] = x;
	StartPt[1] = y;

	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	float r;
	*px = (2.0 * x - Width) / Width;
	*py = (-2.0 * y + Height) / Height;

	r = *px * *px + *py * *py;
	if (r >= 1.0)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0;
	}
	else
	{
		*pz = sqrt(1.0 - r);
	}
}

float GetEngineTime()
{
	static int oldtime = GetTickCount();
	int nowtime = GetTickCount();
	float dTime = ((nowtime - oldtime) % 1000 ) * 0.001f;	
	oldtime = nowtime;	

	return dTime;
}

// 박스 생성
void CreateObject()
{
	// 바닥의 중심 좌표는 (0, 0, 0)
	// 박스의 위치를 여기서 p만큼 이동	
	GVector3 p(0.0f, 20.0f, 0.0f);
	r_box->setPos(p);
	rig.addBox(r_box);

	// 중력 적용
	rig.init();
	Gravity *gra = new Gravity(GVector3(0.0, -5.0, 0.0));
	rig.addForce(gra);
}

void ActionObjects()
{
	dTime = GetEngineTime();

	rig.Action(dTime);

	glutPostRedisplay();
}