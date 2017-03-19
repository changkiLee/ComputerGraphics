
///< User-defined header files
#include "dvVolumeData.h"
#include "dvMarchingCube.h"
#include "dvTrackball.h"

/*------------------------------------------------------------------------------
		Global Variables
------------------------------------------------------------------------------*/
///< Volume
DvVolume<BYTE>				gVolume;
DvMarchingCube<BYTE>		*gMarchingCube;
BYTE						gIsoValue	= 100;

///< OpenGL View
static GLuint				gWidth		= 512;
static GLuint				gHeight		= 512;
static GLfloat				gFOV		= 40.0f;

///< Ete
GLint						gObjID;
GLboolean					gIsWireframe = false;
DvTrackball					gTrackball;
DvVertex					gCenterPos;

///< File Information
///< 1. bighead(256x256x225)  , 2. Engine(256x256x110)
#define FILESEQUENCE	2
#if   FILESEQUENCE == 1
	const int    gVolumeSize[3] = { 256, 256, 225 };
	const char	*gVolumeFileName = "../Data/bighead.raw"; 
#elif FILESEQUENCE == 2
	const int    gVolumeSize[3] = { 256, 256, 110 };
	const char	*gVolumeFileName = "../Data/Engine.raw"; 
#endif

/*------------------------------------------------------------------------------
		Proto-type
------------------------------------------------------------------------------*/
///< Initialize
void InitializeGLUT( int argc, char *argv[] );
void InitializeGLEW();

///< GLUT callback functions
void Display();
void Idle();
void Reshape(int width, int heght);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);

///< Handle volume data
void LoadVolumeData(const char *filename);
void MarchingCube();


/*!
	\brief
		main function
*/
int main(int argc, char *argv[])
{
	/* Initialize glut, glew */
	InitializeGLUT(argc, argv);
	InitializeGLEW();

	/* Load volume data from raw file */
	LoadVolumeData(gVolumeFileName);

	/* Marching Cube */
	MarchingCube();

	glutMainLoop();

	return 0;
}

/*!
	\brief
		Initialize GLUT
*/
void InitializeGLUT( int argc, char *argv[] )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(gWidth, gHeight);
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("Volume Rendering - Marching Cube");

	/* Use depth buffering for hidden surface elimination */
 	glEnable( GL_DEPTH_TEST );
 
 	glFrontFace( GL_CW );
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	/* Lighting */
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Trackball */
	gTrackball.SetTrackballCanvasSize(gWidth, gHeight);
 
	/* Register callback */
	glutDisplayFunc( Display );
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( Mouse );
	glutMotionFunc( Motion );
	glutReshapeFunc( Reshape );
	glutIdleFunc( Idle );
}

/*!
	\brief
		Initialize GLEW
*/
void InitializeGLEW()
{
	GLenum error = glewInit();

	if( error != GLEW_OK ) {
		cerr << "Error in OpenGL extension initialization." << endl;
		exit(0);
	}

	if( glewGetExtension("GL_ARB_fragment_shader")		!= GL_TRUE || 
		glewGetExtension("GL_ARB_vertex_shader")		!= GL_TRUE ||
		glewGetExtension("GL_ARB_shader_objects")		!= GL_TRUE ||
		glewGetExtension("GL_ARB_shading_language_100")	!= GL_TRUE ) 
	{

		cerr << "Driver does not support OpenGL Shading Language." << endl;
		exit(0);
	}
}
/*!
	\brief
		Display callback function
*/
void Display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	float mat[4][4];
	glPushMatrix();
	{
		gTrackball.GetMatrix(mat);
		glMultMatrixf(&mat[0][0]);	

		///> Draw Object
		//glTranslatef(-gCenterPos.P[0], -gCenterPos.P[1], -gCenterPos.P[2]);
		if(gIsWireframe) {
//			cout << "Checked" << endl;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glCallList(gObjID);
	}
	glPopMatrix();

	glutSwapBuffers();
}

/*!
	\brief
		Reshape callback function
*/
void Reshape(int width, int heght)
{
	glViewport(0, 0, width, heght);

	gWidth  = width;
	gHeight = heght;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200.0f, 200.0f, -200.0f, 200.0f, -200.0f, 200.0f);
	//gluPerspective(gFOV, (float)width/heght, -1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
}

/*!
	\brief
		Idle callback function
*/
void Idle()
{
	glutPostRedisplay();
}

/*!
	\brief
		Load volume data
*/
void LoadVolumeData(const char *filename)
{
	///< Load volume data 
	gVolume.Init(gVolumeSize[0], gVolumeSize[1], gVolumeSize[2], 1);
	gVolume.ReadRawFile(filename);
}

/*!
	\brief
		Complement marching cube algorithm
*/
void MarchingCube()
{
	///< Allocate
	gMarchingCube = new DvMarchingCube<BYTE>( &gVolume );

	gMarchingCube->March(gIsoValue);				///< Marching cube 

	gObjID = gMarchingCube->GetDisplayList();		///< Get object id
}

/*!
	\brief
		Mouse callback function
*/
void Mouse(int button, int state, int x, int y)
{
	switch(button) {
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN) {
			gTrackball.SetPreviousPosition(x, y);
		}
		break;
	default:
		break;
	}
}

/*!
	\brief
		Mouse motion callback function
*/
void Motion(int x, int y)
{
	gTrackball.SetTrackballUpdate(x, y);
}

/*!
	\brief
		Keyboard callback function
*/
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) {
	case 27:
	case 'Q':
	case 'q':
		if(gMarchingCube != NULL) delete gMarchingCube;
		cout << "[App Control] : Exit the program !" << endl;
		exit(0);
		break;
	case 'W':
	case 'w':
		gIsWireframe ^= 1;
		break;
	}
}