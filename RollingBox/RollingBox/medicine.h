#ifndef __medicineH__
#define __medicineH__

#include "d3dUtility.h"
#include <vector>

class Medicine
{
public:
	Medicine(IDirect3DDevice9* device);
	~Medicine();

	bool render(D3DXVECTOR3 index_pos);
	
private:
	IDirect3DDevice9* _device;

	ID3DXMesh* med;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	float size;
};

#endif