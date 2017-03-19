#ifndef __ob_moveH__
#define __ob_moveH__

#include "d3dUtility.h"
#include <vector>


class Ob_move
{
public:
	Ob_move(IDirect3DDevice9* device);
	~Ob_move();

	bool render(D3DXVECTOR3 index_pos);

private:
	IDirect3DDevice9* _device;

	ID3DXMesh* move;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	float size;
};

#endif