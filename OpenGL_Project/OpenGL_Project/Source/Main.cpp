#include "..\Include\Main.h"

/*
* < 주의 >
* 1. 변수, 함수명
* 2. 구조
* 3. 주석
* 4. 클래스 기본요소
*	생성자(기본, 대입, 복사(const &)),
*	소멸자(virtual),
*   대입연산자(=, +=, -=, *=, /= (const &)),
*	단항연산자(+, - (const)),
*	첨자 연산자([] (const &))
*/

/*
* < 수정 >
* *. 재질과 텍스쳐가 모두 적용되는 점 방지
* *. 피킹 클래스 확장
* *. 모델의 이동/회전/확대축소 인터페이스 구현(교수님 코드 참고)
* *. 클래스 구조 재조정(쓰기 쉬운 코드, 무한반복이 필요한 코드와 아닌 코드 구분)
* ?. 게임 이식(분리) + 화면 분할
* ?. 강체 시뮬레이션 구현
* ?. 레이 트레이싱 구현
* ?. 증강현실 구현
* ?. 실행파일로 구현(최적화)
* ?. 쉐이더 구현(분리?)
*/

int main(int argc, char* argv[])
{
	// Initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(myCamera.getWidth(), myCamera.getHeight());
	glutInitWindowPosition(0, 0);

	// setup
	setupVariables();

	// Output
	glutCreateWindow("OpenGL_Project");
	glutReshapeFunc(reshapeScene);
	glutDisplayFunc(renderScene);
	
	// Input
	glutKeyboardFunc(keyPressFunc);
	//glutSpecialFunc(sKeyPressFunc);
	glutMouseFunc(mouseFunc);
	glutMouseWheelFunc(mouseWheelFunc);
	glutMotionFunc(mouseMotionFunc);
	//glutPassiveMotionFunc(mousePMotionFunc);
	//glutIdleFunc(idle);

	// Timer
	glutTimerFunc(msec, timer, 0);

	// Loop
	glutMainLoop();
	
	return 0;
}

void reshapeScene(int w, int h)
{
	glViewport(0, 0, w, h);
	myCamera.setWindowSize(w, h);
}


void renderScene()
{
	// setup Scene
	setupRC();

	// Light
	//glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Load
	ObjectModel testPlane;
	myFile.objFileLoad(testPlane, "../OpenGL_Project/Resource/test.obj");
	// render Model
	testPlane.renderObject();
	testPlane.renderVertNormal();
	testPlane.renderPlane();
		

	// floor
	mySimple.renderFloor(30);

	// Swap buffers
	glutSwapBuffers();
}

void setupVariables()
{
	
}

void setupRC()
{
	// set up background color
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // WHITE
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // BLACK

	// Clear Buffer(color, depth)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup
	setupViewVolume();
	setupViewTransform();
	glPushMatrix();

	// Depth
	glEnable(GL_DEPTH_TEST);
	
	// Lighting
	glEnable(GL_LIGHTING);
	
	// Shade
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	// Cull
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	
	// Blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Texture
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	
	// 환경맵에서 자동 텍스춰 좌표
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// 텍스춰 좌표의 확장옵션
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void setupViewVolume()
{
	// set up viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -100.0, 100.0);		// 직교투영
	gluPerspective(60.0, (double)myCamera.getWidth()/(double)myCamera.getHeight(), 0.1, 100.0);		// 원근투영
}

void setupViewTransform()
{	
	// set up view transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Pan
	glTranslatef(myCamera.getPanIdx(0), myCamera.getPanIdx(1), myCamera.getPanIdx(2));
	
	// Rotate
	glRotatef(myCamera.getAngle(), myCamera.getAxisIdx(0), myCamera.getAxisIdx(1), myCamera.getAxisIdx(2));
	glMultMatrixf(myCamera.getRotMat());
	glGetFloatv(GL_MODELVIEW_MATRIX, myCamera.getRotMat());
	myCamera.setRotMatIdx(12, 0);
	myCamera.setRotMatIdx(13, 0);
	myCamera.setRotMatIdx(14, 0); // T = 0
}

void keyPressFunc(unsigned char key, int x, int y)
{
	/*
	* key : ASCII
	* x, y : mouse coordinates (y is reversed)
	*/

	switch(key)
	{
	case '1' : 
		break;
	default :
		break;
	}
}

void sKeyPressFunc(int key, int x, int y)
{
	/*
	* key : GLUT_KEY_F1~12, GLUT_KEY_LEFT/UP/RIGHT/DOWN/PAGE_UP/PAGE_DOWN/HOME/END/INSERT
	* x, y : mouse coordinates (y is reversed)
	*/

	switch(key)
	{
	case GLUT_KEY_UP : 
		break;
	default :
		break;
	}
}

void mouseFunc(int button, int state, int x, int y)
{
	/*
	* button : GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
	* state : GLUT_UP, GLUT_DOWN
	* x, y : mouse coordinates (y is reversed)
	*/

	switch (button)
	{
	case GLUT_LEFT_BUTTON : 
		currManipulateMode = ROTATE;
		break;
	case GLUT_RIGHT_BUTTON : 
		currManipulateMode = PAN;
		break;
	default : 
		break;
	}

	if(state == GLUT_DOWN)
	{
		myCamera.setStartPt(x, y);
		myPickList.pickObject(myCamera, x, y);
	}
	else if(state == GLUT_UP)
	{
		myCamera.setStartPt(0, 0);
		myCamera.setAngle(0.0);
	}	
}

void mouseWheelFunc(int wheel, int direction, int x, int y)
{
	myCamera.calZoom(direction);
}

void mouseMotionFunc(int x, int y)
{
	/*
	* x, y : mouse coordinates (y is reversed)
	*/

	switch(currManipulateMode)
	{
	case PAN :
		{
			myCamera.calPan(x, y);
		}
		break;
	case ROTATE : 
		{
			myCamera.calRotate(x, y);
		}
		break;
	default : 
		break;
	}

	// Reset
	myCamera.setStartPt(x, y);
	glutPostRedisplay();
}

void mousePMotionFunc(int x, int y)
{
	/*
	* x, y : mouse position (y is reversed)
	*/
}

void idle()
{
	glutPostRedisplay();	// glutDisplayFunc() 강제 호출
}

void timer(int id)
{
	glutPostRedisplay();
	glutTimerFunc(msec, timer, 0);
}