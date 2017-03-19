#ifndef __weaponH__
#define __weaponH__

#include "d3dUtility.h"
#include <vector>

class Weapon
{
public:
	Weapon(IDirect3DDevice9* device);
	~Weapon();

	bool render(D3DXVECTOR3 index_pos);
	bool bullet_render(D3DCOLOR color, float timeDelta);

private:
	IDirect3DDevice9* _device;

	ID3DXMesh* weapon;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
	float size;
};

#endif