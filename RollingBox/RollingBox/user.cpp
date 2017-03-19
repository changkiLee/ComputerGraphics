#include "user.h"

User::User()
{
	_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 시작 위치
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	item = 0;	// 아이템 없음
	bullet = 0;	// 총 없음
	key = 0;	// 키 없음
}

User::~User()
{

}

void User::getPosition(D3DXVECTOR3* pos)
{
	*pos = _pos;
}

void User::setPosition(D3DXVECTOR3* pos)
{
	_pos = *pos;
}

void User::getRight(D3DXVECTOR3* right)
{
	*right = _right;
}

void User::getUp(D3DXVECTOR3* up)
{
	*up = _up;
}

void User::getLook(D3DXVECTOR3* look)
{
	*look = _look;
}

void User::setRight(D3DXVECTOR3* right)
{
	_right = *right;
}

void User::setUp(D3DXVECTOR3* up)
{
	_up = *up;
}

void User::setLook(D3DXVECTOR3* look)
{
	_look = *look;
}


void User::walk(float units)
{
	_pos += _look * units;
}

void User::yaw(float angle)
{
	D3DXMATRIX T;

	angle = angle * D3DX_PI / 180;
	// rotate around world y (0, 1, 0) always for land object
	D3DXMatrixRotationAxis(&T, &_up, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformNormal(&_right, &_right, &T);
	D3DXVec3TransformNormal(&_look, &_look, &T);
}

void User::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_right,	angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformNormal(&_up, &_up, &T);
	D3DXVec3TransformNormal(&_look,&_look, &T);
}


void User::getViewMatrix(D3DXMATRIX* V)
{
	D3DXVec3Normalize(&_look, &_look);

	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
	(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
	(*V)(2,0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}

void User::Nomal_rul()
{
	if(_look.x * _look.x < 0.5){
		_look.x = 0;
	}
	if(_look.y * _look.y < 0.5){
		_look.y = 0;
	}
	if(_look.z * _look.z < 0.5){
		_look.z = 0;
	}

	if(_right.x * _right.x < 0.5){
		_right.x = 0;
	}
	if(_right.y * _right.y < 0.5){
		_right.y = 0;
	}
	if(_right.z * _right.z < 0.5){
		_right.z = 0;
	}

	if(_up.x * _up.x < 0.5){
		_up.x = 0;
	}
	if(_up.y * _up.y < 0.5){
		_up.y = 0;
	}
	if(_up.z * _up.z < 0.5){
		_up.z = 0;
	}

	D3DXVec3Normalize(&_look, &_look);
	D3DXVec3Normalize(&_up, &_up);
	D3DXVec3Normalize(&_right, &_right);
}

void User::getMatrix(D3DXMATRIX* V)
{
	D3DXMATRIX R;
	if(_up.x > 0.5){	// 좌		
		(*V)(0,0) = -_up.x; (*V)(0, 1) = _right.x;   (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
		(*V)(1,0) = _up.y; (*V)(1, 1) = -_right.y;	(*V)(1, 2) = -_look.y; (*V)(1, 3) = 0.0f;
		(*V)(2,0) = _up.z; (*V)(2, 1) = -_right.z;	(*V)(2, 2) = -_look.z; (*V)(2, 3) = 0.0f;
		(*V)(3,0) = _pos.x;   (*V)(3, 1) = _pos.y;(*V)(3, 2) = _pos.z;  (*V)(3, 3) = 1.0f;
		D3DXMatrixRotationZ(&R, 90.0f * D3DX_PI / 180.0f);
		*V = R * (*V);
	}
	if(_up.x < -0.5){	// 우
		(*V)(0,0) = _up.x; (*V)(0, 1) = _right.x;   (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
		(*V)(1,0) = _up.y; (*V)(1, 1) = _right.y;	(*V)(1, 2) = -_look.y; (*V)(1, 3) = 0.0f;
		(*V)(2,0) = _up.z; (*V)(2, 1) = _right.z;	(*V)(2, 2) = -_look.z; (*V)(2, 3) = 0.0f;
		(*V)(3,0) = _pos.x;   (*V)(3, 1) = _pos.y;(*V)(3, 2) = _pos.z;  (*V)(3, 3) = 1.0f;
		D3DXMatrixRotationZ(&R, -90.0f * D3DX_PI / 180.0f);
		*V = R * (*V);
	}
	if(_up.y > 0.5){	// 하		
 		(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x;   (*V)(0, 2) = -_look.x; (*V)(0, 3) = 0.0f;
 		(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y;	(*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
 		(*V)(2,0) = -_right.z; (*V)(2, 1) = _up.z;	(*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
 		(*V)(3,0) = _pos.x;   (*V)(3, 1) = _pos.y;(*V)(3, 2) = _pos.z;  (*V)(3, 3) = 1.0f;
		D3DXMatrixRotationAxis(&R, &_up, 180.0f * D3DX_PI / 180.0f);
		*V = R * (*V);
	}
	if(_up.y < -0.5){	// 상
		(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
		(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y;  (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
		(*V)(2,0) = _right.z; (*V)(2, 1) = _up.z;  (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
		(*V)(3,0) = _pos.x;   (*V)(3, 1) = _pos.y; (*V)(3, 2) = _pos.z;  (*V)(3, 3) = 1.0f;
		D3DXMatrixRotationAxis(&R, &_up, 180.0f * D3DX_PI / 180.0f);
		*V = R * (*V);
	}
	if(_up.z > 0.5){	// 뒤
		(*V)(0,0) = -_right.x; (*V)(0, 1) = -_look.x;   (*V)(0, 2) = _up.x; (*V)(0, 3) = 0.0f;
		(*V)(1,0) = _right.y;  (*V)(1, 1) = _look.y;	(*V)(1, 2) = _up.y; (*V)(1, 3) = 0.0f;
		(*V)(2,0) = -_right.z; (*V)(2, 1) = -_look.z;	(*V)(2, 2) = _up.z; (*V)(2, 3) = 0.0f;
		(*V)(3,0) = _pos.x;   (*V)(3, 1) = _pos.y;(*V)(3, 2) = _pos.z;  (*V)(3, 3) = 1.0f;
		D3DXMatrixRotationX(&R, 90.0f * D3DX_PI / 180.0f);
		*V = R * (*V);
	}
	if(_up.z < -0.5){	// 앞
		(*V)(0,0) = -_right.x; (*V)(0, 1) = _look.x;   (*V)(0, 2) = _up.x; (*V)(0, 3) = 0.0f;
		(*V)(1,0) = _right.y; (*V)(1, 1) = -_look.y;	(*V)(1, 2) = _up.y; (*V)(1, 3) = 0.0f;
		(*V)(2,0) = -_right.z; (*V)(2, 1) = -_look.z;	(*V)(2, 2) = -_up.z; (*V)(2, 3) = 0.0f;
		(*V)(3,0) = _pos.x;   (*V)(3, 1) = _pos.y;(*V)(3, 2) = _pos.z;  (*V)(3, 3) = 1.0f;
		D3DXMatrixRotationX(&R, -90.0f * D3DX_PI / 180.0f);
		*V = R * (*V);
	}
}

void User::GetWeapon()		// 무기 획득
{
	item = 1;				// 아이템 있음
	bullet += 3;			// 총알 추가
}

void User::GetKey()			// 열쇠 획득
{
	item = 1;			// 아이템 있음
	key = 1;			// 총알 추가
}

void User::UseWeapon()
{
	bullet--;
	if(bullet <= 0){
		bullet = 0;
		item = 0;
	}
}

bool User::itemCheck()
{
	if(item == 0)
		return true;		// 아이템 없음
	else return false;		// 아이템 있음
}

bool User::haveKey()
{
	if(key == 1)
		return true;		// 열쇠 있음
	else return false;		// 열쇠 없음
}

int User::bulletNum()
{
	return bullet;
}

void User::initBullet()
{
	bullet = 0;
}

void User::initKey()
{
	key = 0;
}