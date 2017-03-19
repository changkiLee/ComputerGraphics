#ifndef __keyH__
#define __keyH__

#include "d3dUtility.h"
#include <vector>

class Key
{
public:
	Key(IDirect3DDevice9* device);
	~Key();

	bool render(D3DXVECTOR3 index_pos);

private:
	IDirect3DDevice9* _device;

	ID3DXMesh* key;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	float size;
};

#endif