#include "weapon.h"

Weapon::Weapon(IDirect3DDevice9* device)
{
	_device = device;
	size = 5.0f;
// 	D3DXCreateBox(_device, size*2, size*2, size*2, &weapon, NULL);
// 	mtrl = d3d::YELLOW_MTRL;
	HRESULT hr = 0;

	//
	// Load the XFile data.
	//

	ID3DXBuffer* adjBuffer  = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls   = 0;

	hr = D3DXLoadMeshFromX(  
		"weapon.x",
		D3DXMESH_MANAGED,
		_device,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&weapon);

	//
	// Extract the materials, and load textures.
	//

	if( mtrlBuffer != 0 && numMtrls != 0 )
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for(int i = 0; i < numMtrls; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now:
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material
			Mtrls.push_back( mtrls[i].MatD3D );

			// check if the ith material has an associative texture
			if( mtrls[i].pTextureFilename != 0 )
			{
				// yes, load the texture for the ith subset
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					_device,
					mtrls[i].pTextureFilename,
					&tex);

				// save the loaded texture
				Textures.push_back( tex );
			}
			else
			{
				// no texture for the ith subset
				Textures.push_back( 0 );
			}
		}
	}
	d3d::Release<ID3DXBuffer*>(mtrlBuffer); // done w/ buffer

	//
	// Optimize the mesh.
	//

	hr = weapon->OptimizeInplace(		
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT  |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0);

	d3d::Release<ID3DXBuffer*>(adjBuffer); // done w/ buffer
}

Weapon::~Weapon()
{
	d3d::Release<ID3DXMesh*>(weapon);
	for(int i = 0; i < Textures.size(); i++)
		d3d::Release<IDirect3DTexture9*>( Textures[i] );
}

bool Weapon::render(D3DXVECTOR3 index_pos)
{
	if( weapon )
	{
		D3DXMATRIX T;

		D3DXMatrixTranslation(&T, index_pos.x, index_pos.y, index_pos.z);		

		_device->SetTransform(D3DTS_WORLD, &T);
		for(int i = 0; i < Mtrls.size(); i++)
		{
			_device->SetMaterial( &Mtrls[i] );
			_device->SetTexture(0, Textures[i]);
			weapon->DrawSubset(i);
		}

		return true;
	}
	else return false;
}