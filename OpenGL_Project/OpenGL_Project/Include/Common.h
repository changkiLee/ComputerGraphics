#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iomanip>
#include <vector>
#include <string>
#include <gl/glut.h>
#include <gl/freeglut.h>

using namespace std;

#define PI			3.14159265359f
#define PI_2		1.57079632679489661923
#define PI_4		0.785398163397448309616
#define SQRT(X)		sqrt((X))
#define SQR(x)		((x) * (x))					// X^2
#define DEG2RAD(x)	(x * PI / 180.0)			// Degree to Radian
#define RAD2DEG(x)	(x * 180.0 / PI)			// Radian to Degree
#define SWAP(type, x, y) { type temp = (x); (x) = (y); (y) = temp; }
#define MIN(x, y)	( x > y ? y : x )			// 최소값 
#define MAX(x, y)	( x > y ? x : y )			// 최대값
#define ABS(x)		( x > 0.0 ? x : (-1.0 * x)) // 절대값

#define SIGN(a)		((a) > 0.0 ? (1.0) : (-1.0))
#define SIGN1(a, b) ((b) > 0.0 ? ABS(a) : -ABS(a))
#define SIGN2(a, b)	((b) >= 0.0 ? fabs(a) : -fabs(a))
#define PYTHAG(a, b) SQRT((SQR(a) + SQR(b)))
#define EQ(X, Y, EPS)	(ABS((X) - (Y)) < EPS)
#define EQ_ZERO(X, EPS) (ABS(X) < EPS)
#define ARR_ZERO(A, N) memset((A), 0, sizeof(A[0]) * (N))
#define ARR_COPY(D, S, N) memmove((D), (S), sizeof(S[0]) * (N))
#define ARR_ALLOC(D, TYPE, N) D = new TYPE [(N)]
#define ARR_ALLOC_2D(D, TYPE, M, N) \
	D = new TYPE *[(M)]; \
	for (int i = 0; i < (M); D[i] = new TYPE [(N)], ++i);
#define ARR_FREE(D) \
	delete [] D; \
	D = NULL
#define ARR_FREE_2D(D, M) \
	for (int i = 0; i < (M); delete [] D[i], ++i); \
	delete [] D; \
	D = NULL
#define MTYPE_EPS	1.0e-15