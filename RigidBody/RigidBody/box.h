#ifndef _BOX_H
#define _BOX_H

#include "gmath.h"

class Box
{
public:
	Box();
	Box(float x, float y, float z);
	Box(float x, float y, float z, float _m);
	Box(Box &r);
	~Box();

	void addForce(GVector3 _f);

	void ForceApply(float dt);
	void RotApply(float dt);

	void find_all_collisions();
	bool colliding();
	GVector3 pt_velocity(GVector3 contact_pos);
	void collision(double _eps);

	void RenderBox();

	void setPos(GVector3 p);
	void setType(int _n);
	//void replaceIntertia();

public:
	int n;						// 모서리 위치
	GVector3 corner[8];			// 모서리
	GVector3 contact;			// 충돌 위치

	float box_x, box_y, box_z;	// 크기
	float m;					// 질량
	GMatrix intertia;			// 관성 질량

	GVector3 pos;			// 위치*
	GQuater q;
	GMatrix rot;			// 회전 정보*
	 	
	GVector3 v;				// 선속도
	GVector3 p;				// 선운동량*
	GVector3 force;			// 힘
	 
	GVector3 w;				// 각속도
	GVector3 l;				// 각운동량*
	GVector3 torq;			// 회전력
};

#endif
