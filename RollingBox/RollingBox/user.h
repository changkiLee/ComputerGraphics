#ifndef User_H
#define User_H

#include <d3dx9.h>

class User
{
public:
	User();
	~User();

	void getViewMatrix(D3DXMATRIX* V); 
	void getMatrix(D3DXMATRIX* V);
	void getPosition(D3DXVECTOR3* pos); 
	void setPosition(D3DXVECTOR3* pos);

	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);
	void setRight(D3DXVECTOR3* right);
	void setUp(D3DXVECTOR3* up);
	void setLook(D3DXVECTOR3* look);
	void Nomal_rul();

	void walk(float units);   // forward/backward
	void yaw(float angle);    // rotate on up vector
	void pitch(float angle);

	bool itemCheck();
	bool haveKey();
	int bulletNum();
	void initBullet();
	void initKey();

	void GetKey();
	void GetWeapon();
	void UseWeapon();
	
private:
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;
	int item;
	int bullet;
	int key;
};

#endif