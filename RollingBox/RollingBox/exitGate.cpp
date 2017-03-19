#include "exitGate.h"

exitGate::exitGate(IDirect3DDevice9* device)
{
	_device = device;
	size = 5.0f;
// 	D3DXCreateBox(_device, size*2, size*2, size*2, &exit, NULL);
// 	mtrl = d3d::BLACK_MTRL;
	_device->CreateVertexBuffer(
		24 * sizeof(d3d::Vertex),
		0, // usage
		d3d::Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);

	_device->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);


	ExitMtrl = d3d::WHITE_MTRL;
	D3DXCreateTextureFromFile(_device, "exit.bmp", &ExitTex);
}

exitGate::~exitGate()
{
	//d3d::Release<ID3DXMesh*>(exit);
	d3d::Release<IDirect3DVertexBuffer9*>(VB);
	d3d::Release<IDirect3DIndexBuffer9*>(IB);
	d3d::Release<IDirect3DTexture9*>(ExitTex);
}

bool exitGate::render(D3DXVECTOR3 index_pos)
{
	if( VB )
	{		
		d3d::Vertex *v = 0;
		VB->Lock(0, 0, (void**)&v, 0);
		// build box

		// fill in the front face d3d::Vertex data
		v[0] = d3d::Vertex(-size, -size, -size, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[1] = d3d::Vertex(-size,  size, -size, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[2] = d3d::Vertex( size,  size, -size, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
		v[3] = d3d::Vertex( size, -size, -size, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

		// fill in the back face d3d::Vertex data
		v[4] = d3d::Vertex(-size, -size, size, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		v[5] = d3d::Vertex( size, -size, size, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		v[6] = d3d::Vertex( size,  size, size, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		v[7] = d3d::Vertex(-size,  size, size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

		// fill in the top face d3d::Vertex data
		v[8]  = d3d::Vertex(-size, size, -size, 0.0f, size, 0.0f, 0.0f, 0.0f);
		v[9]  = d3d::Vertex(-size, size,  size, 0.0f, size, 0.0f, 0.0f, 1.0f);
		v[10] = d3d::Vertex( size, size,  size, 0.0f, size, 0.0f, 1.0f, 1.0f);
		v[11] = d3d::Vertex( size, size, -size, 0.0f, size, 0.0f, 1.0f, 0.0f);

		// fill in the bottom face d3d::Vertex data
		v[12] = d3d::Vertex(-size, -size, -size, 0.0f, -size, 0.0f, 0.0f, 0.0f);
		v[13] = d3d::Vertex( size, -size, -size, 0.0f, -size, 0.0f, 0.0f, 1.0f);
		v[14] = d3d::Vertex( size, -size,  size, 0.0f, -size, 0.0f, 1.0f, 1.0f);
		v[15] = d3d::Vertex(-size, -size,  size, 0.0f, -size, 0.0f, 1.0f, 0.0f);

		// fill in the left face d3d::Vertex data
		v[16] = d3d::Vertex(-size, -size,  size, -size, 0.0f, 0.0f, 0.0f, 0.0f);
		v[17] = d3d::Vertex(-size,  size,  size, -size, 0.0f, 0.0f, 0.0f, 1.0f);
		v[18] = d3d::Vertex(-size,  size, -size, -size, 0.0f, 0.0f, 1.0f, 1.0f);
		v[19] = d3d::Vertex(-size, -size, -size, -size, 0.0f, 0.0f, 1.0f, 0.0f);

		// fill in the right face d3d::Vertex data
		v[20] = d3d::Vertex( size, -size, -size, size, 0.0f, 0.0f, 0.0f, 0.0f);
		v[21] = d3d::Vertex( size,  size, -size, size, 0.0f, 0.0f, 0.0f, 1.0f);
		v[22] = d3d::Vertex( size,  size,  size, size, 0.0f, 0.0f, 1.0f, 1.0f);
		v[23] = d3d::Vertex( size, -size,  size, size, 0.0f, 0.0f, 1.0f, 0.0f);

		VB->Unlock();

		WORD* i = 0;
		IB->Lock(0, 0, (void**)&i, 0);

		// fill in the front face index data
		i[0] = 0; i[1] = 1; i[2] = 2;
		i[3] = 0; i[4] = 2; i[5] = 3;

		// fill in the back face index data
		i[6] = 4; i[7]  = 5; i[8]  = 6;
		i[9] = 4; i[10] = 6; i[11] = 7;

		// fill in the top face index data
		i[12] = 8; i[13] =  9; i[14] = 10;
		i[15] = 8; i[16] = 10; i[17] = 11;

		// fill in the bottom face index data
		i[18] = 12; i[19] = 13; i[20] = 14;
		i[21] = 12; i[22] = 14; i[23] = 15;

		// fill in the left face index data
		i[24] = 16; i[25] = 17; i[26] = 18;
		i[27] = 16; i[28] = 18; i[29] = 19;

		// fill in the right face index data
		i[30] = 20; i[31] = 21; i[32] = 22;
		i[33] = 20; i[34] = 22; i[35] = 23;

		IB->Unlock();

		// 이동변환
		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, index_pos.x, index_pos.y, index_pos.z);
		_device->SetTransform(D3DTS_WORLD, &T);

		// 버텍스 정보 불러오기
		_device->SetStreamSource(0, VB, 0, sizeof(d3d::Vertex));
		_device->SetIndices(IB);
		_device->SetFVF(d3d::Vertex::FVF);

		// 거울 그리기(재질, 텍스쳐)
		_device->SetMaterial(&ExitMtrl);
		_device->SetTexture(0, ExitTex);
		_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST, 
			0,                  
			0,                  
			24,
			0,
			12);

		//_device->SetMaterial(&mtrl);
		//mirror->DrawSubset(0);	

		return true;
	}
	else return false;
}