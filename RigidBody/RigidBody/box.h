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
	int n;						// �𼭸� ��ġ
	GVector3 corner[8];			// �𼭸�
	GVector3 contact;			// �浹 ��ġ

	float box_x, box_y, box_z;	// ũ��
	float m;					// ����
	GMatrix intertia;			// ���� ����

	GVector3 pos;			// ��ġ*
	GQuater q;
	GMatrix rot;			// ȸ�� ����*
	 	
	GVector3 v;				// ���ӵ�
	GVector3 p;				// �����*
	GVector3 force;			// ��
	 
	GVector3 w;				// ���ӵ�
	GVector3 l;				// �����*
	GVector3 torq;			// ȸ����
};

#endif
