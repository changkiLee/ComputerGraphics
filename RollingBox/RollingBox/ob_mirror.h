#ifndef __ob_mirrorH__
#define __ob_mirrorH__

#include "d3dUtility.h"
#include "user.h"

class Ob_mirror
{
public:
	Ob_mirror(IDirect3DDevice9* device);
	~Ob_mirror();

	bool render(D3DXVECTOR3 index_pos);
	bool renderObj(D3DXVECTOR3 index_pos, User _user, ID3DXMesh *_obj);

private:
	IDirect3DDevice9* _device;

	//ID3DXMesh* mirror;
	//D3DMATERIAL9 mtrl;
	float size;
	IDirect3DVertexBuffer9 *VB;
	IDirect3DIndexBuffer9 *IB;
	IDirect3DTexture9 *MirrorTex;
	D3DMATERIAL9 MirrorMtrl;
};

#endif