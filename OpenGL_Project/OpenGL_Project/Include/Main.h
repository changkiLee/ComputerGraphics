#include "..\Include\Common.h"
#include "..\Include\FileLoader.h"
#include "..\Include\Camera.h"
#include "..\Include\DirectionLight.h"
#include "..\Include\PointLight.h"
#include "..\Include\SpotLight.h"
#include "..\Include\Material.h"
#include "..\Include\Texture.h"
#include "..\Include\SimpleModel.h"
#include "..\Include\ObjectModel.h"
#include "..\Include\ObjectPickList.h"

/* -------------------------------------------------
@ Main Functions
-------------------------------------------------*/
// Output
void reshapeScene(int w, int h);
void renderScene();
// Setup
void setupVariables();
void setupRC();
void setupViewVolume();
void setupViewTransform();
// Input
void keyPressFunc(unsigned char key, int x, int y);
void sKeyPressFunc(int key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseWheelFunc(int wheel, int direction, int x, int y);
void mouseMotionFunc(int x, int y);
void mousePMotionFunc(int x, int y);
void idle();
// Timer
void timer(int id);

/* -------------------------------------------------
@ Constant
-------------------------------------------------*/
enum ManipulateMode
{
	NONE = -1,
	PAN = 0,
	ROTATE = 1,
	ZOOM = 2,
};
ManipulateMode currManipulateMode = NONE;

float degree = 0.0f;
const int msec = 50;

/* -------------------------------------------------
@ Objects
-------------------------------------------------*/
// file
FileLoader myFile;

// camera
Camera myCamera;

// object
SimpleModel mySimple;
ObjectModel bigman, bunny;
ObjectPickList myPickList;

// light
DirectionLight dLight;
PointLight pLight;
SpotLight sLight;

// material
Material matBigman, matBunny, matTeapot;
Material matSun;

// texture
Texture texBigman, texBunny, texTeapot;
Texture texSun, texEarth, texMoon;
