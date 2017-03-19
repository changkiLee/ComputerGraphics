#ifndef __ob_holeH__
#define __ob_holeH__

#include "d3dUtility.h"
#include <vector>

class Ob_hole
{
public:
	Ob_hole(IDirect3DDevice9* device);
	~Ob_hole();

	bool render(D3DXVECTOR3 index_pos);

private:
	IDirect3DDevice9* _device;

	ID3DXMesh* hole;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	float size;
};

#endif