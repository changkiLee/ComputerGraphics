#ifndef __ob_fireH__
#define __ob_fireH__

#include "d3dUtility.h"
#include <vector>

class Ob_fire
{
public:
	Ob_fire(IDirect3DDevice9* device);
	~Ob_fire();

	bool render(D3DXVECTOR3 index_pos);

private:
	IDirect3DDevice9* _device;

	ID3DXMesh* fire;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	float size;
};

#endif