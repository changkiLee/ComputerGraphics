#include <windows.h>
#include <iostream>
#include <time.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include "MSParticleSystem.h"
#include "define.h"

using namespace std;


/////// Utility Functions //////////
float ToRadian(float Degree);
float ToDegree(float Radian);

////////// global variables ////////
int g_ScrWidth = 600, g_ScrHeight = 600;
int g_WorldWidth = 100, g_WorldHeight = 100;

static float dTime = 0;

MSParticleSystem* g_pParticle = NULL;

/////////////////////////////////////

//////// Object ... ////////////////
void CreateObjects();

void ReleaseObjects();
////////////////////////////////////

//////// Transform Functions ////////
void SetupViewTransform();
void SetupViewVolume();
/////////////////////////////////////


float GetEngineTime();
/////////////////////////////////////

/////// Draw Functions //////////////

/////////////////////////////////////

////// Draw Option Functions ////////
/////////////////////////////////////

/////// call-back Functions /////////
void Keyboard_Func_Control(int key, int x, int y);
void Keyboard_Control(unsigned char key, int x, int y);
void MouseControl(int button, int state, int x, int y);
void Render();
void Reshape(int width, int height);
void ActionObjects();
/////////////////////////////////////


int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	srand( time(NULL) );

	glutInitWindowSize(g_ScrWidth, g_ScrHeight);
	glutInitWindowPosition(0,0);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Simple Particle System");

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseControl);
	glutKeyboardFunc(Keyboard_Control);
	glutSpecialFunc(Keyboard_Func_Control);
	glutIdleFunc(ActionObjects);

	glEnable(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	CreateObjects();
	
	glutMainLoop();

	ReleaseObjects();

	return 0;
}


void Render()
{
	glClearColor(0.6f, 0.85f, 0.92f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupViewTransform();
	SetupViewVolume();

	glMatrixMode(GL_MODELVIEW);
	
	if( g_pParticle !=NULL)
		g_pParticle->Render();

	/*
	char buf[256];
	sprintf_s(buf, sizeof(buf),"dTime : %.4f", dTime );

	glColor3f(0.0,0.0,0.0);
	glRasterPos2i(0, 90);
	for(int i=0; i<256; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
	}
	*/

	
	glutSwapBuffers();
}

void SetupViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// center 가 (0,0) 
	glOrtho(0, g_WorldWidth, 0, g_WorldHeight, -100.0, 100.0);
	
}

void Reshape(int width, int height)
{
	glViewport(0,0, width, height);
	g_ScrWidth = width;
	g_ScrHeight = height;

}
float ToRadian(float Degree)
{
	return (Degree * PI_)/180.0f;

}
float ToDegree(float Radian)
{
	return (Radian * 180.f)/(float)PI_;
}

void Keyboard_Func_Control(int key, int x, int y)
{
	switch(key)
	{
	
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
	glutPostRedisplay();
}




void Keyboard_Control(unsigned char key, int x, int y)
{
	MSImpulse *pImpulse = NULL;

	switch(key)
	{
	case 32: // space
		break;
	case '1':
		pImpulse = new MSImpulse(MSVector2(-20.0f,0), 1.0f);
		g_pParticle->AddForce(pImpulse);
		cout << "Create Impluse Dir(-20, 0)" << endl;
		break;
	case '2':
		pImpulse = new MSImpulse(MSVector2(20.0f,0), 1.0f);
		g_pParticle->AddForce(pImpulse);
		cout << "Create Impluse Dir(20, 0)" << endl;
		break;
	case '3':
		pImpulse = new MSImpulse(MSVector2(0.0f,-10.0f), 1.0f);
		g_pParticle->AddForce(pImpulse);
		cout << "Create Impluse Dir(0, -10.0f)" << endl;
		break;
	case '4':
		pImpulse = new MSImpulse(MSVector2(0.0f,10.0f), 1.0f);
		g_pParticle->AddForce(pImpulse);
		cout << "Create Impluse Dir(0, 10.0f)" << endl;
		break;
	}
	

	glutPostRedisplay();
}

void MouseControl(int button, int state, int x, int y)
{

}

void ActionObjects()
{
	dTime = GetEngineTime();

	if( g_pParticle != NULL)
		g_pParticle->Action(dTime);

	glutPostRedisplay();
}

float GetEngineTime()
{
	static int oldtime = GetTickCount();
	int nowtime = GetTickCount();
	float dTime = ((nowtime - oldtime) % 1000 ) * 0.001f;	
	oldtime = nowtime;	

	return dTime;
}

void CreateObjects()
{
	g_pParticle = new MSParticleSystem();

	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{

			MSParticle *pParticle = new MSParticle( (i == 0 || i == 8)? MSParticle::FIXED : MSParticle::NORMAL,
				MSVector2(j*10 + 10, 90 - i * 10), 1.0f );
			g_pParticle->AddParticle(pParticle);

		}
	}

	MSGravity *pGravity = new MSGravity(MSVector2(0, -0.5f) );
	g_pParticle->AddForce(pGravity);

	vector<MSParticle*> particles = g_pParticle->GetParticles();
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<9; j++)
		{	
			// | 방향 스프링
			MSParticle* p1 = particles[ i*9 + j];
			MSParticle* p2 = particles[ (i+1)*9 + j];
			MSSpring* pSpring = new MSSpring(p1, p2, (float(rand()%10))/10.0f, (float(rand()%10))/10.0f);
			g_pParticle->AddForce(pSpring);
		}
	}

	for(int i=0; i<8; i++)
	{
		// \ 방향 스프링
		for(int j=0; j<8; j++)
		{	
			MSParticle* p1 = particles[ i*9 + j];
			MSParticle* p2 = particles[ (i+1)*9 + j + 1];
			MSSpring* pSpring = new MSSpring(p1, p2, (float(rand()%10))/10.0f , (float(rand()%10))/10.0f);

			g_pParticle->AddForce(pSpring);
		}

		// / 방향 스프링
		for(int j=1; j<9; j++)
		{	
			MSParticle* p1 = particles[ i*9 + j];
			MSParticle* p2 = particles[ (i+1)*9 + j -1];
			MSSpring* pSpring = new MSSpring(p1, p2, (float(rand()%10))/10.0f, (float(rand()%10))/10.0f);

			g_pParticle->AddForce(pSpring);
		}
	}

	for(int i=0; i<9; i++)
	{
		for(int j=0; j<8; j++)
		{	
			// - 방향 스프링
			MSParticle* p1 = particles[ i*9 + j];
			MSParticle* p2 = particles[ i*9 + j + 1];
			MSSpring* pSpring = new MSSpring(p1, p2, (float(rand()%10))/10.0f, (float(rand()%10))/10.0f);

			g_pParticle->AddForce(pSpring);
		}
	}

}

void ReleaseObjects()
{
	delete g_pParticle;
}

