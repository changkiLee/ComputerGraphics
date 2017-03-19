#include "..\Include\Camera.h"

Camera::Camera()
{
	// window size
	width = 1024;
	height = 768;

	startPt[0] = 0, startPt[1] = 0;
	
	// zoom, pan, rotation
	pan[0] = 0.0, pan[1] = 0.0, pan[2] = -20.0;
	angle = 0.0;
	axis[0] = 1.0, axis[1] = 0.0, axis[2] = 0.0;
	for(int i = 0; i < 16; i++)	// rotMat = I
	{
		if(i % 5 == 0)
			rotMat[i] = 1;
		else
			rotMat[i] = 0;
	}
}

Camera::~Camera()
{

}

int Camera::getWidth()
{
	return width;
}

int Camera::getHeight()
{
	return height;
}

float Camera::getAngle()
{
	return angle;
}

float Camera::getPanIdx(const int &idx)
{
	if(idx >= 0 && idx <= 2)
		return pan[idx];
	else
		return 0;
}

float Camera::getAxisIdx(const int &idx)
{
	if(idx >= 0 && idx <= 2)
		return axis[idx];
	else
		return 0;
}

float* Camera::getRotMat()
{
	return rotMat;
}

void Camera::setWindowSize(const int &w, const int &h)
{
	width = w;
	height = h;
}

void Camera::setStartPt(const int &x, const int &y)
{
	startPt[0] = x;
	startPt[1] = y;
}

void Camera::setAngle(const float &_angle)
{
	this->angle = _angle;
}

void Camera::setPan(const float &x, const float &y, const float &z)
{
	pan[0] = x;
	pan[1] = y;
	pan[2] = z;
}

void Camera::setAxis(const float &x, const float &y, const float &z)
{
	axis[0] = x;
	axis[1] = y;
	axis[2] = z;
}

void Camera::setRotMatIdx(const int &idx, const float &val)
{
	rotMat[idx] = val;
}

void Camera::calZoom(const int &dir)
{
	pan[2] += dir;
}

void Camera::calPan(const int &x, const int &y)
{
	pan[0] += (x - startPt[0]) * 0.01f;
	pan[1] += (startPt[1] - y) * 0.01f;
}

void Camera::calRotate(const int &x, const int &y)
{
	float px, py, pz, qx, qy, qz;
	getSphereCoord(startPt[0], startPt[1], &px, &py, &pz);	// previouse
	getSphereCoord(x, y, &qx, &qy, &qz);	// present

	axis[0] = (py * qz) - (pz * qy);
	axis[1] = (pz * qx) - (px * qz);
	axis[2] = (px * qy) - (py * qx);
	angle = acos((px * qx) + (py * qy) + (pz * qz)) * 180.0f / PI;
}

void Camera::getSphereCoord(const int &x, const int &y, float *px, float *py, float *pz)
{
	/*
	* x, y : mouse coordinates
	* px, py, pz : Arcball coordinates
	*/

	float r;
	*px = (2.0f * x - width) / width;
	*py = (-2.0f * y + height) / height;
	
	r = (*px)*(*px) + (*py)*(*py);
	if(r >= 1.0)
	{
		*px = *px / SQRT(r);
		*py = *py / SQRT(r);
		*pz = 0.0;
	}
	else
	{
		*pz = SQRT(1.0f - r);
	}
}
