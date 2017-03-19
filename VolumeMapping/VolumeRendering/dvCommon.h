
/* -------------------------------------
	Associated linking library
 -------------------------------------*/
#pragma once
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")

/* -------------------------------------
	Include System header files
 -------------------------------------*/
#include <Windows.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>
#include <cmath>
#include <map>
#include <xutility>

/* -------------------------------------
	Include Graphics & Vision Library
-------------------------------------*/
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>

/* -------------------------------------
	Using Name space
-------------------------------------*/
using namespace std;
using std::vector;
using std::pair;

// User define & macro for math
#define TRACKBALLSIZE	(0.8f)							// Size of Trackball 
#define DG_SQRT(x)		sqrt((x))						// sqrt X^2
#define DG_SQR(x)		((x) * (x))						// X^2
#define DG_DEG2RAD(x)	(x * 3.141592 / 180.0)			// Degree to Radian
#define DG_RAD2DEG(x)	(x * 180.0 / 3.141592)			// Radian to Degree
#define DG_MIN(x, y)	( x > y ? y : x )				// Minimum value
#define DG_MAX(x, y)	( x > y ? x : y )				// Maximum value
#define DG_ABS(x)		( x > 0.0 ? x : (-1.0 * x))		// Absolute
