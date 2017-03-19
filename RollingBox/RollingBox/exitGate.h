#ifndef __exitGateH__
#define __exitGateH__

#include "d3dUtility.h"

class exitGate
{
public:
	exitGate(IDirect3DDevice9* device);
	~exitGate();

	bool render(D3DXVECTOR3 index_pos);

private:
	IDirect3DDevice9* _device;
// 	ID3DXMesh* exit;
// 	D3DMATERIAL9 mtrl;
	float size;
	IDirect3DVertexBuffer9 *VB;
	IDirect3DIndexBuffer9 *IB;
	IDirect3DTexture9 *ExitTex;
	D3DMATERIAL9 ExitMtrl;
};

#endif