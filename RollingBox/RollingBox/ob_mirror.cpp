#include "Ob_mirror.h"

Ob_mirror::Ob_mirror(IDirect3DDevice9* device)
{
	_device = device;
	size = 5.0f;

	//D3DXCreateBox(_device, size*2, size*2, size*2, &mirror, NULL);
	//mtrl = d3d::CYAN_MTRL;	
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


	MirrorMtrl = d3d::WHITE_MTRL;
	D3DXCreateTextureFromFile(_device, "ice.bmp", &MirrorTex);

}

Ob_mirror::~Ob_mirror()
{
	//d3d::Release<ID3DXMesh*>(mirror);
	d3d::Release<IDirect3DVertexBuffer9*>(VB);
	d3d::Release<IDirect3DIndexBuffer9*>(IB);
	d3d::Release<IDirect3DTexture9*>(MirrorTex);
}

bool Ob_mirror::render(D3DXVECTOR3 index_pos)
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
		_device->SetMaterial(&MirrorMtrl);
		_device->SetTexture(0, MirrorTex);
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

bool Ob_mirror::renderObj(D3DXVECTOR3 index_pos, User _user, ID3DXMesh *_obj)
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

		//
		// 반사된 거울 그리기
		//

		// 스텐실 테스트 활성화
		_device->SetRenderState(D3DRS_STENCILENABLE, true);

		// 비교 연산자 지정(항상 성공)
		_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

		// 스텐실 참조 값 설정
		_device->SetRenderState(D3DRS_STENCILREF, 0x1);

		// 스텐실 마스크 값 설정
		_device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);

		// 스텐실 쓰기 마스크 값 설정
		_device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

		// 깊이 테스트 실패 시  
		_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

		// 스텐실 테스트 실패 시
		_device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

		// 스텐실 테스트 성공 시
		_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

		// 깊이 버퍼 쓰기 비활성화
		_device->SetRenderState(D3DRS_ZWRITEENABLE, false);

		// 알파 블렌딩 활성화
		_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		// 블렌딩 인수 지정
		_device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 스텐실 버퍼에 거울 그리기
		_device->SetStreamSource(0, VB, 0, sizeof(d3d::Vertex));
		_device->SetIndices(IB);
		_device->SetFVF(d3d::Vertex::FVF);
		_device->SetMaterial(&MirrorMtrl);
		_device->SetTexture(0, MirrorTex);
		// 이동변환
		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, index_pos.x, index_pos.y, index_pos.z);
		_device->SetTransform(D3DTS_WORLD, &T);
		_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,                  
			0,                  
			24,
			0,
			12);

		// 깊이 버퍼 쓰기 활성화
		_device->SetRenderState(D3DRS_ZWRITEENABLE, true);

		// 비교 연산자 지정
		_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

		// 반사 행렬 설정
		D3DXMATRIX W, W_, W2, W2_, W3, W3_, T2, R, R_, R2, R2_, R3, R3_, scale;
		D3DXVECTOR3 user_pos, look, dir;
		_user.getPosition(&user_pos);
		_user.getLook(&look);
		dir = index_pos - user_pos;
		D3DXPLANE plane(0.0f, 0.0f, 1.0f, -index_pos.z+size); // xy plane
		D3DXPLANE plane_(0.0f, 0.0f, 1.0f, -index_pos.z-size); // xy plane
		D3DXPLANE plane2(0.0f, 1.0f, 0.0f, -index_pos.y+size); // xz plane
		D3DXPLANE plane2_(0.0f, 1.0f, 0.0f, -index_pos.y-size); // xz plane
		D3DXPLANE plane3(1.0f, 0.0f, 0.0f, -index_pos.x+size); // yz plane
		D3DXPLANE plane3_(1.0f, 0.0f, 0.0f, -index_pos.x-size); // yz plane
		//D3DXMatrixTranslation(&T2, user_pos.x, user_pos.y, user_pos.z);
		_user.getMatrix(&T2);
		D3DXMatrixReflect(&R, &plane);
		D3DXMatrixReflect(&R_, &plane_);
		D3DXMatrixReflect(&R2, &plane2);
		D3DXMatrixReflect(&R2_, &plane2_);
		D3DXMatrixReflect(&R3, &plane3);
		D3DXMatrixReflect(&R3_, &plane3_);
		D3DXMatrixScaling(&scale, 0.5f, 0.5f, 0.5f);
		W = scale * T2 * R;
		W_ = scale * T2 * R_;
		W2 = scale * T2 * R2;
		W2_ = scale * T2 * R2_;
		W3 = scale * T2 * R3;
		W3_ = scale * T2 * R3_;

		// 깊이 버퍼 지우기
		_device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		_device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_DESTCOLOR);
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		D3DXVec3Normalize(&look, &look);
		D3DXVec3Normalize(&dir, &dir);

		if(D3DXVec3Dot(&look, &dir) > 0.95 && D3DXVec3Length(&(index_pos - user_pos)) < 80){
			if(D3DXVec3Dot(&look, &D3DXVECTOR3(plane.a, plane.b, plane.c)) > 0.9){
				// 반사 물체 그리기
				_device->SetTransform(D3DTS_WORLD, &W);
				_device->SetMaterial(&d3d::BLACK_MTRL);
				_device->SetTexture(0, 0);
				_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				_obj->DrawSubset(0);
			}
			if(D3DXVec3Dot(&look, &D3DXVECTOR3(plane_.a, plane_.b, plane_.c)) < -0.9){
				// 반사 물체 그리기
				_device->SetTransform(D3DTS_WORLD, &W_);
				_device->SetMaterial(&d3d::BLACK_MTRL);
				_device->SetTexture(0, 0);
				_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				_obj->DrawSubset(0);
			}
			if(D3DXVec3Dot(&look, &D3DXVECTOR3(plane2.a, plane2.b, plane2.c)) > 0.9){
				// 반사 물체 그리기
				_device->SetTransform(D3DTS_WORLD, &W2);
				_device->SetMaterial(&d3d::BLACK_MTRL);
				_device->SetTexture(0, 0);
				_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				_obj->DrawSubset(0);
			}
			if(D3DXVec3Dot(&look, &D3DXVECTOR3(plane2_.a, plane2_.b, plane2_.c)) < -0.9){
				// 반사 물체 그리기
				_device->SetTransform(D3DTS_WORLD, &W2_);
				_device->SetMaterial(&d3d::BLACK_MTRL);
				_device->SetTexture(0, 0);
				_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				_obj->DrawSubset(0);
			}
			if(D3DXVec3Dot(&look, &D3DXVECTOR3(plane3.a, plane3.b, plane3.c)) > 0.9){
				// 반사 물체 그리기
				_device->SetTransform(D3DTS_WORLD, &W3);
				_device->SetMaterial(&d3d::BLACK_MTRL);
				_device->SetTexture(0, 0);
				_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				_obj->DrawSubset(0);
			}
			if(D3DXVec3Dot(&look, &D3DXVECTOR3(plane3_.a, plane3_.b, plane3_.c)) < -0.9){
				// 반사 물체 그리기
				_device->SetTransform(D3DTS_WORLD, &W3_);
				_device->SetMaterial(&d3d::BLACK_MTRL); 
				_device->SetTexture(0, 0);
				_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
				_obj->DrawSubset(0);
			}
		}

		// 렌더 상태 복원
		_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		_device->SetRenderState(D3DRS_STENCILENABLE, false);
		_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	

		return true;
	}
	else return false;
}