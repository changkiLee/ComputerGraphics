#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "..\Include\Common.h"

class Camera
{
private : 
	// 윈도우 크기
	int width;
	int height;

	// 관측변환을 위한 변수
	int startPt[2];
	float angle;
	float pan[3];
	float axis[3];
	float rotMat[16];

public :
	Camera();
	virtual ~Camera();
	
	// Get
	int getWidth();
	int getHeight();
	float getAngle();
	float getPanIdx(const int &idx);
	float getAxisIdx(const int &idx);
	float* getRotMat();

	// Set
	void setWindowSize(const int &w, const int &h);
	void setStartPt(const int &x, const int &y);
	void setAngle(const float &_angle);
	void setPan(const float &x, const float &y, const float &z);
	void setAxis(const float &x, const float &y, const float &z);
	void setRotMatIdx(const int &idx, const float &val);

	// Calculate
	void calZoom(const int &y);
	void calPan(const int &x, const int &y);
	void calRotate(const int &x, const int &y);

	void getSphereCoord(const int &x, const int &y, float *px, float *py, float *pz);
};

#endif