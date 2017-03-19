#include "d3dUtility.h"
#include "terrain.h"
#include "medicine.h"
#include "ob_move.h"
#include "ob_fire.h"
#include "ob_hole.h"
#include "ob_mirror.h"
#include "weapon.h"
#include "key.h"
#include "exitGate.h"
#include "user.h"
#include "timer.h"
#include "drawText.h"
#include "pSystem.h"
#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <vector>

HINSTANCE g_hInst;
HWND hWndMain;
LPSTR lpszClass="DSound";
//사운드 관련 라이브러리 읽기
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
//사운드 관련 외부 변수
LPDIRECTSOUND8 lpds;
LPDIRECTSOUNDBUFFER lpdsBuffer[15];


int loadsnd(int index, char *FileName)
{
	WAVEFORMATEX wfx; 
	DSBUFFERDESC dsbdesc;

	HMMIO hWAV;
	MMCKINFO Parent, Child;

	UCHAR *WholeSndBuff, *PrimaryBuff = NULL, *SecondaryBuff = NULL; 
	DWORD PrimaryLength = 0, SecondaryLength = 0;

	Parent.ckid             = (FOURCC)0;
	Parent.cksize			= 0;
	Parent.fccType			= (FOURCC)0;
	Parent.dwDataOffset		= 0;
	Parent.dwFlags			= 0;
	Child					= Parent;

	hWAV = mmioOpen(FileName, NULL, MMIO_READ | MMIO_ALLOCBUF);

	if( !hWAV ) return 0;
	Parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if( mmioDescend(hWAV, &Parent, NULL, MMIO_FINDRIFF) )
	{
		mmioClose(hWAV, 0);
		return 0;
	}

	Child.ckid = mmioFOURCC('f', 'm', 't', ' ');

	if( mmioDescend(hWAV, &Child, &Parent, 0) )
	{
		mmioClose(hWAV, 0);
		return 0;  
	}

	if( mmioRead(hWAV, (char *)&wfx, sizeof(wfx)) != sizeof(wfx) )
	{
		mmioClose(hWAV, 0);
		return 0;
	}

	if( wfx.wFormatTag != WAVE_FORMAT_PCM )
	{
		mmioClose(hWAV, 0);
		return 0; 
	}

	if( mmioAscend(hWAV, &Child, 0) )
	{
		mmioClose(hWAV, 0);
		return 0;  
	}

	Child.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if( mmioDescend(hWAV, &Child, &Parent, MMIO_FINDCHUNK) )
	{
		mmioClose(hWAV, 0);
		return 0;  
	}

	WholeSndBuff = new UCHAR[ Child.cksize ];
	mmioRead(hWAV, (char *)WholeSndBuff, Child.cksize);
	mmioClose(hWAV, 0);

	memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
	wfx.wFormatTag = WAVE_FORMAT_PCM; 
	wfx.nChannels = 2; 
	wfx.nSamplesPerSec = 44100; 
	wfx.wBitsPerSample = 16; 
	wfx.nBlockAlign = (wfx.nChannels*wfx.wBitsPerSample)/8; 
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = 0;

	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
	dsbdesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_STICKYFOCUS | DSBCAPS_GETCURRENTPOSITION2; 
	dsbdesc.dwBufferBytes = Child.cksize; 
	dsbdesc.lpwfxFormat = &wfx; 

	if (FAILED(lpds->CreateSoundBuffer(&dsbdesc, &lpdsBuffer[index], NULL))) 
	{ 
		delete[] WholeSndBuff;
		return 0;
	}

	lpdsBuffer[index]->Lock(0, Child.cksize, (LPVOID*)&PrimaryBuff, &PrimaryLength, (LPVOID*)&SecondaryBuff, &SecondaryLength, DSBLOCK_FROMWRITECURSOR);
	memcpy(PrimaryBuff, WholeSndBuff, PrimaryLength);
	memcpy(SecondaryBuff, (WholeSndBuff+PrimaryLength), SecondaryLength);
	lpdsBuffer[index]->Unlock(PrimaryBuff, PrimaryLength, SecondaryBuff, SecondaryLength);
	delete[] WholeSndBuff;

	return 1;
}


//
// Globals
//

IDirect3DDevice9* Device = 0; 

// 화면 크기
const int Width  = 1024;
const int Height = 768;

// 지형
Terrain* TheTerrain_b = 0;
Terrain* TheTerrain_u = 0;
Terrain* TheTerrain_l = 0;
Terrain* TheTerrain_r = 0;
Terrain* TheTerrain_n = 0;
Terrain* TheTerrain_f = 0;

// 지형 위의 개체
// 0 : bottom
// 1 : up
// 2 : left
// 3 : right
// 4 : near
// 5 : far
int map[6][31][31];
Medicine *ob_med = 0;
Ob_move *ob_move = 0;
Ob_fire *ob_fire = 0;
Ob_hole *ob_hole = 0;
Ob_mirror *ob_mirror = 0;
Weapon *ob_weapon = 0;
Key *ob_key = 0;
exitGate *ob_exit = 0;

// 사용자
User	 TheUser;
ID3DXMesh* user_Object = 0;
std::vector<D3DMATERIAL9>       Mtrls(0);
std::vector<IDirect3DTexture9*> Textures(0);

// 총
psys::PSystem* Gun = 0;

// 시간 제어
TimerCounter* timer = 0;

// 텍스트
drawText* text = 0;

// 화면
IDirect3DVertexBuffer9* Quad = 0;
IDirect3DTexture9*      Tex1  = 0;
IDirect3DTexture9*      Tex2  = 0;
IDirect3DTexture9*      Tex3  = 0;
IDirect3DTexture9*      Tex4  = 0;
IDirect3DTexture9*      Tex5  = 0;
IDirect3DTexture9*      Tex6  = 0;
IDirect3DTexture9*      Tex7  = 0;
IDirect3DTexture9*      Tex8  = 0;
IDirect3DTexture9*      Tex9  = 0;
IDirect3DTexture9*      Tex10  = 0;
IDirect3DTexture9*      Tex11  = 0;

// 회전, 점프 제어
int roll = 0;
int jump = 0;
int check = 0;
int vk_check = 0;
D3DXVECTOR3 user_height(0.0f, 0.0f, 0.0f);

// 화면 상수
enum View{
	LOGO = 0,
	MENU = 1,
	MENUAL = 2,
	STORY = 3,
	GAME = 4,
	GAMEOVER = 5,
	ENDING = 6
};
int state = LOGO;
int stateCount = 0;
int stateOver = 0;
float logotime = 0;
float overtime = 0;
float l_angle = 0;
float r_angle = 0;
float w_angle = 0;

// 개체 속성
const int map_size = 32;
const float user_spead = 50.0f;
const float rad = 3.0f;
const int index_size = 10;
float jump_value = 20.0f;
// 개체의 개수
int obstacle_move = 16*6;	// 1
int obstacle_fire = 16*6;	// 2
int obstacle_hole = 16*6;	// 3
int obstacle_mirror = 8*6;	// 4
int weapon = 3*6;			// 5
int medicine = 128*6;		// 6
							// 7 : key
							// 8 : out

// 인덱스를 좌표로 반환하는 함수
D3DXVECTOR3 TransXYZ(int i, int j, int k);
D3DXVECTOR3 TransHoleXYZ(int i, int j, int k);
D3DXVECTOR3 TransMoveXYZ(int i, int j, int k, float timeDelta);

D3DLIGHT9 Spot;

//
// Framework Functions
//
bool Setup()
{
	//
	// Create the terrain.
	//

	TheTerrain_b = new Terrain(Device, "coastMountain64.raw", map_size, map_size, 10, 0.1f);
	TheTerrain_b->loadTexture("red.bmp");
	
	TheTerrain_u = new Terrain(Device, "coastMountain64.raw", map_size, map_size, 10, 0.1f);
	TheTerrain_u->loadTexture("red.bmp");

	TheTerrain_l = new Terrain(Device, "coastMountain64.raw", map_size, map_size, 10, 0.1f);
	TheTerrain_l->loadTexture("green.bmp");

	TheTerrain_r = new Terrain(Device, "coastMountain64.raw", map_size, map_size, 10, 0.1f);
	TheTerrain_r->loadTexture("green.bmp");

	TheTerrain_n = new Terrain(Device, "coastMountain64.raw", map_size, map_size, 10, 0.1f);
	TheTerrain_n->loadTexture("blue.bmp");

	TheTerrain_f = new Terrain(Device, "coastMountain64.raw", map_size, map_size, 10, 0.1f);
	TheTerrain_f->loadTexture("blue.bmp");

	//
	// Create the User.
	//

	HRESULT hr = 0;

	//
	// Load the XFile data.
	//

	ID3DXBuffer* adjBuffer  = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls   = 0;

	hr = D3DXLoadMeshFromX(  
		"bigship.x",
		D3DXMESH_MANAGED,
		Device,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&user_Object);

	if(FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
		return false;
	}

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
					Device,
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

	hr = user_Object->OptimizeInplace(		
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT  |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0);

	d3d::Release<ID3DXBuffer*>(adjBuffer); // done w/ buffer

	if(FAILED(hr))
	{
		::MessageBox(0, "OptimizeInplace() - FAILED", 0, 0);
		return false;
	}

	// 사용자 초기화
	TheUser.setPosition(&D3DXVECTOR3(-150.0f, rad, -150.0f));
	TheUser.setRight(&D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	TheUser.setUp(&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	TheUser.setLook(&D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	TheUser.initBullet();
	TheUser.initKey();

	// 상태 초기화
	int roll = 0;
	int jump = 0;
	int check = 0;
	l_angle = 0;
	r_angle = 0;
	w_angle = 0;
	overtime = 0;
	D3DXVECTOR3 user_height(0.0f, 0.0f, 0.0f);

	//
	// Create Objects on the map
	//

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 31; j++){
			for(int k = 0; k < 31; k++){
				map[i][j][k] = 0;
			}
		}
	}

	// 랜덤 변수
	int rand_t;
	int rand_y;
	int rand_x;

	srand((unsigned int)time(NULL));
	
	// 장애물_move
	for(int i = 0; i < obstacle_move; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 29 + 1;
		rand_x = rand() % 29 + 1;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 1;
		}			
		else{
			i--;
		}
	}
	// 장애물_불
	for(int i = 0; i < obstacle_fire; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 29 + 1;
		rand_x = rand() % 29 + 1;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 2;
		}			
		else{
			i--;
		}
	}
	// 장애물_구덩이
	for(int i = 0; i < obstacle_hole; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 29 + 1;
		rand_x = rand() % 29 + 1;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 3;
		}			
		else{
			i--;
		}
	}
	// 장애물_거울
	for(int i = 0; i < obstacle_mirror; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 29 + 1;
		rand_x = rand() % 29 + 1;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 4;
		}			
		else{
			i--;
		}
	}
	// 무기
	for(int i = 0; i < weapon; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 29 + 1;
		rand_x = rand() % 29 + 1;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 5;
		}			
		else{
			i--;
		}
	}
	// 약
	for(int i = 0; i < medicine; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 29 + 1;
		rand_x = rand() % 29 + 1;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 6;
		}			
		else{
			i--;
		}
	}
	// 열쇠
	for(int i = 0; i < 1; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 31;
		rand_x = rand() % 31;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 7;
		}			
		else{
			i--;
		}
	}
	// 탈출구
	for(int i = 0; i < 1; i++){
		rand_t = rand() % 6;
		rand_y = rand() % 31;
		rand_x = rand() % 31;
		if(map[rand_t][rand_y][rand_x] == 0){
			map[rand_t][rand_y][rand_x] = 8;
		}			
		else{
			i--;
		}
	}

	// 실질적인 생성
	ob_med = new Medicine(Device);
	ob_move = new Ob_move(Device);
	ob_fire = new Ob_fire(Device);
	ob_hole = new Ob_hole(Device);
	ob_mirror = new Ob_mirror(Device);
	ob_weapon = new Weapon(Device);
	ob_key = new Key(Device);
	ob_exit = new exitGate(Device);

	Gun = new psys::ParticleGun( &TheUser );
	Gun->init(Device, "flare_alpha.dds");

	//
	// Create the font.
	//

	timer = new TimerCounter(Device);
	text = new drawText(Device);

	//
	// 각 화면 생성
	//

	//
	// Create the quad vertex buffer and fill it with the
	// quad geoemtry.
	//

	Device->CreateVertexBuffer(
		6 * sizeof(d3d::Vertex), 
		D3DUSAGE_WRITEONLY,
		d3d::Vertex::FVF,
		D3DPOOL_MANAGED,
		&Quad,
		0);

	d3d::Vertex* v;
	Quad->Lock(0, 0, (void**)&v, 0);

	// quad built from two triangles, note texture coordinates:
	v[0] = d3d::Vertex(-4.0f, -3.0f, 7.2f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = d3d::Vertex(-4.0f,  3.0f, 7.2f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = d3d::Vertex( 4.0f,  3.0f, 7.2f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = d3d::Vertex(-4.0f, -3.0f, 7.2f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = d3d::Vertex( 4.0f,  3.0f, 7.2f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = d3d::Vertex( 4.0f, -3.0f, 7.2f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	Quad->Unlock();

	D3DXCreateTextureFromFile(
		Device,
		"logo.jpg",
		&Tex1);
	D3DXCreateTextureFromFile(
		Device,
		"menu1.jpg",
		&Tex2);
	D3DXCreateTextureFromFile(
		Device,
		"menu2.jpg",
		&Tex3);
	D3DXCreateTextureFromFile(
		Device,
		"menu3.jpg",
		&Tex4);
	D3DXCreateTextureFromFile(
		Device,
		"menual.jpg",
		&Tex5);
	D3DXCreateTextureFromFile(
		Device,
		"story.jpg",
		&Tex6);
	D3DXCreateTextureFromFile(
		Device,
		"fireOver.jpg",
		&Tex7);
	D3DXCreateTextureFromFile(
		Device,
		"holeOver.jpg",
		&Tex8);
	D3DXCreateTextureFromFile(
		Device,
		"mirrorOver.jpg",
		&Tex9);
	D3DXCreateTextureFromFile(
		Device,
		"timeOver.jpg",
		&Tex10);
	D3DXCreateTextureFromFile(
		Device,
		"ending.jpg",
		&Tex11);

	//
	// Set lighting related render states.
	//

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);

	//
	// Set texture filters.
	//

	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//
	// Set camera
	//

	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	Device->SetTransform(D3DTS_VIEW, &I);

	//
	// Set projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.25f, // 45 - degree
		(float)Width / (float)Height,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// Create the texture and set filters.
	//
	Device->SetRenderState(D3DRS_LIGHTING, false);

	return true;
}

void Cleanup()
{
	d3d::Delete<Terrain*>(TheTerrain_b);
	d3d::Delete<Terrain*>(TheTerrain_u);
	d3d::Delete<Terrain*>(TheTerrain_l);
	d3d::Delete<Terrain*>(TheTerrain_r);
	d3d::Delete<Terrain*>(TheTerrain_n);
	d3d::Delete<Terrain*>(TheTerrain_f);
	d3d::Release<ID3DXMesh*>(user_Object);
	d3d::Delete<TimerCounter*>(timer);
	d3d::Delete<psys::PSystem*>( Gun );
	for(int i = 0; i < Textures.size(); i++)
		d3d::Release<IDirect3DTexture9*>( Textures[i] );
	d3d::Release<IDirect3DVertexBuffer9*>(Quad);
	d3d::Release<IDirect3DTexture9*>(Tex1);
	d3d::Release<IDirect3DTexture9*>(Tex2);
	d3d::Release<IDirect3DTexture9*>(Tex3);
	d3d::Release<IDirect3DTexture9*>(Tex4);
	d3d::Release<IDirect3DTexture9*>(Tex5);
	d3d::Release<IDirect3DTexture9*>(Tex6);
	d3d::Release<IDirect3DTexture9*>(Tex7);
	d3d::Release<IDirect3DTexture9*>(Tex8);
	d3d::Release<IDirect3DTexture9*>(Tex9);
	d3d::Release<IDirect3DTexture9*>(Tex10);
	d3d::Release<IDirect3DTexture9*>(Tex11);
}

bool Display(float timeDelta)
{
	//
	// Update the scene:
	//

	if( Device )
	{
		if(state == LOGO){			
			lpdsBuffer[0]->Play(0,0,0);
			Device->SetTexture(0, Tex1);

			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			Device->BeginScene();

			Device->SetStreamSource(0, Quad, 0, sizeof(d3d::Vertex));
			Device->SetFVF(d3d::Vertex::FVF);
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

			logotime += timeDelta;
			if(logotime >= 2){
				state = MENU;
			}

			Device->EndScene();
			Device->Present(0, 0, 0, 0);
		}
		if(state == MENU){
			lpdsBuffer[0]->Stop();
			lpdsBuffer[2]->Stop();
			lpdsBuffer[12]->Stop();
			lpdsBuffer[13]->Stop();
			lpdsBuffer[1]->Play(0,0,1);
			
			if(stateCount == 0){				
				Device->SetTexture(0, Tex2);
			}
			if(stateCount == 1){
				Device->SetTexture(0, Tex3);
			}
			if(stateCount == 2){				
				Device->SetTexture(0, Tex4);
			}

			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			Device->BeginScene();

			Device->SetStreamSource(0, Quad, 0, sizeof(d3d::Vertex));
			Device->SetFVF(d3d::Vertex::FVF);
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

			Device->EndScene();
			Device->Present(0, 0, 0, 0);
		}
		if(state == MENUAL){
			Device->SetTexture(0, Tex5);
			
			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			Device->BeginScene();

			Device->SetStreamSource(0, Quad, 0, sizeof(d3d::Vertex));
			Device->SetFVF(d3d::Vertex::FVF);
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

			Device->EndScene();
			Device->Present(0, 0, 0, 0);
		}
		if(state == STORY){
			lpdsBuffer[1]->Stop();
			lpdsBuffer[2]->Play(0,0,1);
			Device->SetTexture(0, Tex6);

			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			Device->BeginScene();

			Device->SetStreamSource(0, Quad, 0, sizeof(d3d::Vertex));
			Device->SetFVF(d3d::Vertex::FVF);
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

			Device->EndScene();
			Device->Present(0, 0, 0, 0);
		}
		if(state == GAME)
		{
			//
			// 사용자 이동
			//
			if( vk_check == 0)
			{
				TheUser.walk(user_spead * timeDelta);
			}
			// 왼쪽
			if( vk_check == 1 )
			{
				l_angle -= 200.0f*timeDelta;
				TheUser.yaw(-200.0f*timeDelta);
				timer->plusTime(timeDelta);			// 시간증가
				if(l_angle <= -90.0f){
					l_angle = 0;
					vk_check = 0;
					TheUser.Nomal_rul();
				}
			}
			// 오른쪽
			if( vk_check == 2 )
			{
				r_angle += 200.0f*timeDelta;
				TheUser.yaw(200.0f*timeDelta);
				timer->plusTime(timeDelta);			// 시간증가
				if(r_angle >= 90.0f){
					r_angle = 0;
					vk_check = 0;
					TheUser.Nomal_rul();
				}
			}
			// 벽타기
			if( vk_check == 3)
			{
				w_angle -= 200.0f*timeDelta;
				TheUser.pitch(-200.0f*timeDelta*D3DX_PI / 180.0f);
				timer->plusTime(timeDelta);			// 시간증가
				if(w_angle <= -90.0f){
					w_angle = 0;
					vk_check = 0;
					TheUser.Nomal_rul();
				}

			}

			//
			// 사용자 위치 설정
			//
 			D3DXVECTOR3 user_pos, up;
 			TheUser.getPosition(&user_pos);		

			// 사용자 이동 범위 제한
			if(user_pos.x > 5*(map_size-1) - rad){	// 우
				roll = 1;
				user_pos.x = 5*(map_size-1) - rad;
			}
			if(user_pos.x < -5*(map_size-1) + rad){	// 좌
				roll = 1;
				user_pos.x = -5*(map_size-1) + rad;
			}
			if(user_pos.y > 10*(map_size-1) - rad){	// 상
				roll = 1;
				user_pos.y = 10*(map_size-1) - rad;
			}
			if(user_pos.y < rad){					// 하
				roll = 1;
				user_pos.y = rad;
			}
			if(user_pos.z > 5*(map_size-1) - rad){	// 앞
				roll = 1;
				user_pos.z = 5*(map_size-1) - rad;
			}
			if(user_pos.z < -5*(map_size-1) + rad){	// 뒤
				roll = 1;
				user_pos.z = -5*(map_size-1) + rad;
			}		

			//
			// 점프
			//
			if(jump == 1){
				TheUser.getUp(&up);
				user_height -= up * 0.25f;			
				if(D3DXVec3Length(&user_height) < 0.3){
					check = 0;
					user_height = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				else{
					user_pos = user_pos - up * 0.25f;
				}
			}
			if(jump == 2){
				TheUser.getUp(&up);
				user_height += up * 0.25f;
				user_pos = user_pos + up * 0.25f;
				if(D3DXVec3Length(&user_height) > jump_value){
					jump = 1;
					check = 1;
					roll = 0;
				}
			}

 			TheUser.setPosition(&user_pos);

			//
			// 카메라 위치 설정
			//
 			D3DXMATRIX T, W;
 			TheUser.getViewMatrix(&W);
			D3DXMatrixTranslation(&T, 0.0f, -10.0f, 40.0f);	// 물체로부터의 카메라 위치
 			W = W*T;
 			// 카메라 지정
			Device->SetTransform(D3DTS_VIEW, &W);

			//
			// TestView
 			//
	//  	D3DXMATRIX V;
	//  	D3DXMatrixTranslation(&V, 0, -70, 500);
	//  	Device->SetTransform(D3DTS_VIEW, &V);
	 		

			//
			// Setup a directional light.
			//
			D3DXVECTOR3 light_pos;
			D3DXVECTOR3 light_look, light_up;
			TheUser.getPosition(&light_pos);
			TheUser.getLook(&light_look);
			TheUser.getUp(&light_up);
			D3DXCOLOR   c = d3d::WHITE;
			Spot = d3d::InitSpotLight(&(light_pos - light_look*40 + light_up*60), &(light_look - light_up), &c);

			//
			// Set and Enable the light.
			//

			Device->SetLight(0, &Spot);
			Device->LightEnable(0, true);
			Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
			Device->SetRenderState(D3DRS_SPECULARENABLE, true);

			//
			// Draw the scene:
			//

			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xff000000, 1.0f, 0L);
			Device->BeginScene();

			//
			// 지형 그리기
			//
			D3DXMATRIX t_bottom, t_up, t_left, t_right, t_near, t_far;
			D3DXMATRIX rot_x, rot_x2, rot_z, rot_z2;
			D3DXMatrixRotationX(&rot_x, 90*D3DX_PI/180);
			D3DXMatrixRotationX(&rot_x2, -90*D3DX_PI/180);
			D3DXMatrixRotationZ(&rot_z, 90*D3DX_PI/180);
			D3DXMatrixRotationZ(&rot_z2, -90*D3DX_PI/180);
			D3DXMatrixIdentity(&t_bottom);
			D3DXMatrixTranslation(&t_up, 0.0f, 10.0f*(map_size-1), 0.0f);
			t_up = rot_x * rot_x * t_up;
			D3DXMatrixTranslation(&t_left, -5.0f*(map_size-1), 5.0f*(map_size-1), 0.0f);
			t_left = rot_z2 * t_left;
			D3DXMatrixTranslation(&t_right, 5.0f*(map_size-1), 5.0f*(map_size-1), 0.0f);
			t_right = rot_z * t_right;
			D3DXMatrixTranslation(&t_near, 0.0f, 5.0f*(map_size-1), -5.0f*(map_size-1));
			t_near = rot_x * t_near;
			D3DXMatrixTranslation(&t_far, 0.0f, 5.0f*(map_size-1), 5.0f*(map_size-1));
			t_far = rot_x2 * t_far;

			// 지형
			if( TheTerrain_b )
				TheTerrain_b->draw(&t_bottom, true);
			if( TheTerrain_u )
				TheTerrain_u->draw(&t_up, true);
 			if( TheTerrain_l )
				TheTerrain_l->draw(&t_left, true);
 			if( TheTerrain_r )
				TheTerrain_r->draw(&t_right, true);
 			if( TheTerrain_n )
 				TheTerrain_n->draw(&t_near, true);
 			if( TheTerrain_f )
 				TheTerrain_f->draw(&t_far, true);

			//
			// 화면의 개체 그리기
			//
			for(int i = 0; i < 6; i++){
				for(int j = 0; j < 31; j++){
					for(int k = 0; k < 31; k++){
						if(map[i][j][k] == 1){					// 움직이는 화염
							ob_move->render(TransMoveXYZ(i, j, k, timeDelta));	// 그리기
							if(D3DXVec3Length(&(TransMoveXYZ(i, j, k, timeDelta) - Gun->getPosition(timeDelta))) < 7.0){
								map[i][j][k] = 0;				// 장애물 파괴
							}
							if(D3DXVec3Length(&(TransMoveXYZ(i, j, k, timeDelta) - user_pos)) < 3.5 + rad){	// 충돌 체크
								lpdsBuffer[5]->Play(0,0,0);
								stateOver = 1;
								state = GAMEOVER;				// 충돌시 게임오버
							}
						}
						if(map[i][j][k] == 2){					// 화염
							ob_fire->render(TransXYZ(i, j, k));	// 그리기
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - Gun->getPosition(timeDelta))) < 7.0){
								lpdsBuffer[11]->Play(0,0,0);
								map[i][j][k] = 0;				// 장애물 파괴
							}
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - user_pos)) < 3.5 + rad){	// 충돌 체크
								lpdsBuffer[5]->Play(0,0,0);
								stateOver = 1;
								state = GAMEOVER;				// 충돌시 게임오버
							}					
						}
						if(map[i][j][k] == 3){					// 구덩이
							ob_hole->render(TransHoleXYZ(i, j, k));// 그리기
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - Gun->getPosition(timeDelta))) < 7.0){
								lpdsBuffer[11]->Play(0,0,0);
								map[i][j][k] = 0;				// 장애물 파괴
							}
							if(D3DXVec3Length(&(TransHoleXYZ(i, j, k) - user_pos)) < 4.5 + rad){// 충돌 체크
								lpdsBuffer[5]->Play(0,0,0);
								stateOver = 2;
								state = GAMEOVER;				// 충돌시 게임오버
							}
						}
						if(map[i][j][k] == 4){					// 거울
							ob_mirror->render(TransXYZ(i, j, k));	// 그리기
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - Gun->getPosition(timeDelta))) < 7.0){
								map[i][j][k] = 0;				// 장애물 파괴
							}
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - user_pos)) < 3.5 + rad){// 충돌 체크
								lpdsBuffer[5]->Play(0,0,0);
								stateOver = 3;
								state = GAMEOVER;				// 충돌시 게임오버
							}
						}
						if(map[i][j][k] == 5){					// 무기
							ob_weapon->render(TransXYZ(i, j, k));	// 그리기
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - user_pos)) < 3.5 + rad){// 충돌 체크
								if(!TheUser.haveKey()){			// 열쇠를 가지고 있지 않은 경우
									lpdsBuffer[6]->Play(0,0,0);
									map[i][j][k] = 0;			// 충돌시 소멸
									TheUser.GetWeapon();		// 무기획득
								}
							}
						}
						if(map[i][j][k] == 6){					// 시간약
							ob_med->render(TransXYZ(i, j, k));	// 그리기
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - user_pos)) < 3.5 + rad){	// 충돌 체크
								lpdsBuffer[7]->Play(0,0,0);
								map[i][j][k] = 0;				// 충돌시 소멸
								timer->plusTime(1.0);			// 시간증가
							}
						}
						if(map[i][j][k] == 7){					// 열쇠
							ob_key->render(TransXYZ(i, j, k));	// 그리기
							if(D3DXVec3Length(&(TransXYZ(i, j, k) - user_pos)) < 3.5 + rad){	// 충돌 체크
								if(TheUser.bulletNum() == 0){	// 무기가 없는 경우
									lpdsBuffer[8]->Play(0,0,0);
									map[i][j][k] = 0;			// 충돌시 소멸
									TheUser.GetKey();			// 열쇠 획득
								}
							}
						}
						if(map[i][j][k] == 8){						// 탈출구
							if(TheUser.haveKey()){					// 열쇠가 있는 경우
								ob_exit->render(TransXYZ(i, j, k));	// 그리기
								if(D3DXVec3Length(&(TransXYZ(i, j, k) - user_pos)) < 3.5 + rad){	// 충돌 체크
									state = ENDING;					// 엔딩
								}
							}
						}
					}
				}
			}			
	
			// 반사된 물체 그리기
			for(int i = 0; i < 6; i++){
				for(int j = 0; j < 31; j++){
					for(int k = 0; k < 31; k++){
						if(map[i][j][k] == 4){					// 거울
							ob_mirror->renderObj(TransXYZ(i, j, k), TheUser, user_Object);	// 그리기						
						}
					}
				}
			}

			//
			// 사용자 그리기
			//
			D3DXMATRIX Move, Scale;
			TheUser.getMatrix(&Move);
			D3DXMatrixScaling(&Scale, 0.5f, 0.5f, 0.5f);
			Move = Scale * Move;
			Device->SetTransform(D3DTS_WORLD, &Move);
			// 사용자
			for(int i = 0; i < Mtrls.size(); i++)
			{
				Device->SetMaterial( &Mtrls[i] );
				Device->SetTexture(0, Textures[i]);
				user_Object->DrawSubset(i);
			}

			//
			// 총알 그리기
			//
			Gun->update(timeDelta);
			D3DXMATRIX I;
			D3DXMatrixIdentity(&I);
			Device->SetTransform(D3DTS_WORLD, &I);
			Gun->render();

			//
			// Timer 그리기
			//
			if( timer ){
				//
				// 시간 소모로 게임오버 된 경우
				//
				float temp = timer->render(0xffffffff, timeDelta);
				
				if(temp <= 4)
				{
					lpdsBuffer[14]->Play(0,0,0);
				}
				else
				{
					lpdsBuffer[14]->Stop();
				}
				if(temp <= 0)
				{
					stateOver = 4;
					state = GAMEOVER;
				}
			}

			if( text ){
				text->renderBullet(0xffffffff, TheUser.bulletNum());
				text->renderKey(0xffffffff, TheUser.haveKey());
			}			

			Device->EndScene();
			Device->Present(0, 0, 0, 0);
		}
		if(state == GAMEOVER){
			lpdsBuffer[2]->Stop();
			lpdsBuffer[14]->Stop();
			lpdsBuffer[12]->Play(0,0,0);
			D3DXMATRIX I;
			D3DXMatrixIdentity(&I);
			Device->SetTransform(D3DTS_VIEW, &I);
			Device->SetRenderState(D3DRS_LIGHTING, false);

 			overtime += timeDelta;
 			if(overtime >= 0.5){
				if(stateOver == 1){
					Device->SetTexture(0, Tex7);
				}
				if(stateOver == 2){					
					Device->SetTexture(0, Tex8);
				}
				if(stateOver == 3){
					Device->SetTexture(0, Tex9);
				}
				if(stateOver == 4){					
					Device->SetTexture(0, Tex10);
				}

				Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
				Device->BeginScene();

				Device->SetStreamSource(0, Quad, 0, sizeof(d3d::Vertex));
				Device->SetFVF(d3d::Vertex::FVF);
				Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

				Device->EndScene();
				Device->Present(0, 0, 0, 0);
 			}			
		}
		if(state == ENDING){
			lpdsBuffer[2]->Stop();
			lpdsBuffer[13]->Play(0,0,0);

			D3DXMATRIX I;
			D3DXMatrixIdentity(&I);
			Device->SetTransform(D3DTS_VIEW, &I);
			Device->SetRenderState(D3DRS_LIGHTING, false);

			Device->SetTexture(0, Tex11);

			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			Device->BeginScene();

			Device->SetStreamSource(0, Quad, 0, sizeof(d3d::Vertex));
			Device->SetFVF(d3d::Vertex::FVF);
			Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

			Device->EndScene();
			Device->Present(0, 0, 0, 0);
		}
	}
	return true;
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_CREATE:   
		//다이렉트 사운드 초기화
		DirectSoundCreate8(NULL, &lpds, NULL);
		lpds->SetCooperativeLevel(hwnd, DSSCL_NORMAL );

		//파일 로딩
		loadsnd(0,"sound\\logo.wav");
		loadsnd(1,"sound\\menu.wav");
		loadsnd(2,"sound\\game.wav");
		loadsnd(3,"sound\\roll.wav");
		loadsnd(4,"sound\\jump.wav");
		loadsnd(5,"sound\\bomb.wav");
		loadsnd(6,"sound\\getWeap.wav");
		loadsnd(7,"sound\\getMed.wav");
		loadsnd(8,"sound\\getKey.wav");
		loadsnd(9,"sound\\botton.wav");
		loadsnd(10,"sound\\misile.wav");
		loadsnd(11,"sound\\broken.wav");
		loadsnd(12,"sound\\over.wav");
		loadsnd(13,"sound\\clear.wav");
		loadsnd(14,"sound\\clock.wav");
		
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE ){
			lpdsBuffer[9]->Play(0,0,0);
			Setup();
			state = MENU;
			stateCount = 0;
			break;
		}

		// 로고에서 메뉴로
		if( state == LOGO ){			
			if( wParam == VK_RETURN){
				lpdsBuffer[9]->Play(0,0,0);
				state = MENU;
				stateCount = 0;
				break;
			}
		}

		// 메뉴상 인터페이스
		if( state == MENU ){
			if( wParam == VK_LEFT || wParam == VK_UP){
				lpdsBuffer[9]->Play(0,0,0);
				stateCount--;
				if(stateCount < 0){
					stateCount = 0;
				}
			}
			if( wParam == VK_RIGHT || wParam == VK_DOWN){
				lpdsBuffer[9]->Play(0,0,0);
				stateCount++;
				if(stateCount > 2){
					stateCount = 2;
				}
			}
			if( wParam == VK_RETURN){
				lpdsBuffer[9]->Play(0,0,0);
				if(stateCount == 0){
					state = STORY;
					break;
				}
				if(stateCount == 1){
					state = MENUAL;
					break;
				}
				if(stateCount == 2){
					::PostQuitMessage(0);
				}
			}
		}
			
		// 메뉴얼
		if( state == MENUAL){
			if(wParam == VK_RETURN){
				lpdsBuffer[9]->Play(0,0,0);
				state = MENU;
				stateCount = 0;
				break;
			}
		}

		// 시놉시스
		if( state == STORY ){
			if(wParam == VK_RETURN){
				lpdsBuffer[9]->Play(0,0,0);
				// 상태 초기화
				Setup();
				int roll = 0;
				int jump = 0;
				int check = 0;
				D3DXVECTOR3 user_height(0.0f, 0.0f, 0.0f);

				state = GAME;
				break;
			}
		}

		// 게임상 인터페이스
		if( state == GAME){
			if( wParam == VK_LEFT && vk_check == 0 )
			{
				lpdsBuffer[3]->Play(0,0,0);
				vk_check = 1;
				roll = 0;
			}
			if(  wParam == VK_RIGHT && vk_check == 0 )
			{
				lpdsBuffer[3]->Play(0,0,0);
				vk_check = 2;
				roll = 0;
			}
			if(  wParam == 'W' && roll == 1 && D3DXVec3Length(&user_height) < 0.1 && vk_check == 0)
			{
				lpdsBuffer[3]->Play(0,0,0);
				vk_check = 3;
				roll = 0;
			}
			if(  wParam == VK_SPACE && check == 0)
			{
				lpdsBuffer[4]->Play(0,0,0);
				jump = 2;
			}
			if(  wParam == 'E' && TheUser.bulletNum() > 0)
			{
				lpdsBuffer[10]->Play(0,0,0);
				TheUser.UseWeapon();
				Gun->addParticle();
			}
		}

		// 게임오버
		if( state == GAMEOVER ){
			if(wParam == VK_RETURN){
				lpdsBuffer[9]->Play(0,0,0);
				state = MENU;
				stateCount = 0;
				break;
			}
		}

		// 엔딩 크레딧
		if( state == ENDING ){
			if(wParam == VK_RETURN){
				lpdsBuffer[9]->Play(0,0,0);
				state = MENU;
				stateCount = 0;
				break;
			}
		}
 
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

D3DXVECTOR3 TransXYZ(int i, int j, int k)
{
	D3DXVECTOR3 index_pos;
	if( i == 0 ){	// bottom
		index_pos.x = -5.0f*(map_size-1) + index_size/2 + index_size*k;
		index_pos.y = index_size/2;
		index_pos.z = 5.0f*(map_size-1) - index_size/2 - index_size*j;
	}
	if( i == 1 ){	// up
		index_pos.x = 5.0f*(map_size-1) - index_size/2 - index_size*k;
		index_pos.y = 10.0f*(map_size-1) - index_size/2;
		index_pos.z = -5.0f*(map_size-1) + index_size/2 + 10*j;
	}
	if( i == 2 ){	// left
		index_pos.x = -5.0f*(map_size-1) + index_size/2;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = -5.0f*(map_size-1) + index_size/2 + 10*k;
	}
	if( i == 3 ){	// right
		index_pos.x = 5.0f*(map_size-1) - index_size/2;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = 5.0f*(map_size-1) - index_size/2 - 10*k;
	}
	if( i == 4 ){	// near
		index_pos.x = 5.0f*(map_size-1) - index_size/2 - 10*k;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = -5.0f*(map_size-1) + index_size/2;
	}
	if( i == 5 ){	// far
		index_pos.x = -5.0f*(map_size-1) + index_size/2 + 10*k;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = 5.0f*(map_size-1) - index_size/2;
	}	
	return index_pos;
}

D3DXVECTOR3 TransHoleXYZ(int i, int j, int k)
{
	D3DXVECTOR3 index_pos;
	if( i == 0 ){	// bottom
		index_pos.x = -5.0f*(map_size-1) + index_size/2 + index_size*k;
		index_pos.y = -index_size/4;
		index_pos.z = 5.0f*(map_size-1) - index_size/2 - index_size*j;
	}
	if( i == 1 ){	// up
		index_pos.x = 5.0f*(map_size-1) - index_size/2 - index_size*k;
		index_pos.y = 10.0f*(map_size-1) + index_size/4;
		index_pos.z = -5.0f*(map_size-1) + index_size/2 + 10*j;
	}
	if( i == 2 ){	// left
		index_pos.x = -5.0f*(map_size-1) - index_size/4;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = -5.0f*(map_size-1) + index_size/2 + 10*k;
	}
	if( i == 3 ){	// right
		index_pos.x = 5.0f*(map_size-1) + index_size/4;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = 5.0f*(map_size-1) - index_size/2 - 10*k;
	}
	if( i == 4 ){	// near
		index_pos.x = 5.0f*(map_size-1) - index_size/2 - 10*k;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = -5.0f*(map_size-1) - index_size/4;
	}
	if( i == 5 ){	// far
		index_pos.x = -5.0f*(map_size-1) + index_size/2 + 10*k;
		index_pos.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_pos.z = 5.0f*(map_size-1) + index_size/4;
	}	
	return index_pos;
}


// 위치
D3DXVECTOR3 index_movepos_b(0.0f, index_size/2, 0.0f);
D3DXVECTOR3 index_movepos_u(0.0f, 10.0f*(map_size-1) - index_size/2, 0.0f);
D3DXVECTOR3 index_movepos_l(-5.0f*(map_size-1) + index_size/2, 0.0f, 0.0f);
D3DXVECTOR3 index_movepos_r(5.0f*(map_size-1) - index_size/2, 0.0f, 0.0f);
D3DXVECTOR3 index_movepos_n(0.0f, 0.0f, -5.0f*(map_size-1) + index_size/2);
D3DXVECTOR3 index_movepos_f(0.0f, 0.0f, 5.0f*(map_size-1) - index_size/2);
// 방향&속도
float dir_b = 1.0f;
float dir_u = 1.5f;
float dir_l = 0.5f;
float dir_r = 1.2f;
float dir_n = 0.8f;
float dir_f = 1.0f;
D3DXVECTOR3 TransMoveXYZ(int i, int j, int k, float timeDelta)
{
	if( i == 0 ){	// bottom
		index_movepos_b.x = -5.0f*(map_size-1) + index_size/2 + index_size*k;
		index_movepos_b.y += dir_b * timeDelta;
		index_movepos_b.z = 5.0f*(map_size-1) - index_size/2 - index_size*j;
		
		if( index_movepos_b.y >= 40.0f)
			dir_b = -1.0f;
		if( index_movepos_b.y <= index_size/2 )
			dir_b = 1.0f;

		return index_movepos_b;
	}
	if( i == 1 ){	// up
		index_movepos_u.x = 5.0f*(map_size-1) - index_size/2 - index_size*k;
		index_movepos_u.y += dir_u * timeDelta;
		index_movepos_u.z = -5.0f*(map_size-1) + index_size/2 + 10*j;

		if( index_movepos_u.y <= 10.0f*(map_size-1) - index_size/2 - 40.0f)
			dir_u = 1.5f;
		if( index_movepos_u.y >= 10.0f*(map_size-1) - index_size/2 )
			dir_u = -1.5f;

		return index_movepos_u;
	}
	if( i == 2 ){	// left
		index_movepos_l.x += dir_l * timeDelta;
		index_movepos_l.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_movepos_l.z = -5.0f*(map_size-1) + index_size/2 + 10*k;

		if( index_movepos_l.x >= -5.0f*(map_size-1) + index_size/2 + 40)
			dir_l = -0.5f;
		if( index_movepos_l.x <= -5.0f*(map_size-1) + index_size/2 )
			dir_l = 0.5f;	

		return index_movepos_l;
	}
	if( i == 3 ){	// right
		index_movepos_r.x += dir_r * timeDelta;
		index_movepos_r.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_movepos_r.z = 5.0f*(map_size-1) - index_size/2 - 10*k;

		if( index_movepos_r.x <= 5.0f*(map_size-1) - index_size/2 - 40)
			dir_r = 1.2f;
		if( index_movepos_r.x >= 5.0f*(map_size-1) - index_size/2 )
			dir_r = -1.2f;

		return index_movepos_r;
	}
	if( i == 4 ){	// near
		index_movepos_n.x = 5.0f*(map_size-1) - index_size/2 - 10*k;
		index_movepos_n.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_movepos_n.z += dir_n * timeDelta;

		if( index_movepos_n.z >= -5.0f*(map_size-1) + index_size/2 + 40)
			dir_n = -0.8f;
		if( index_movepos_n.z <= -5.0f*(map_size-1) + index_size/2 )
			dir_n = 0.8f;	

		return index_movepos_n;
	}
	if( i == 5 ){	// far
		index_movepos_f.x = -5.0f*(map_size-1) + index_size/2 + 10*k;
		index_movepos_f.y = 10.0f*(map_size-1) - index_size/2 - 10*j;
		index_movepos_f.z += dir_f * timeDelta;

		if( index_movepos_f.z <= 5.0f*(map_size-1) - index_size/2 - 40)
			dir_f = 1.0f;
		if( index_movepos_f.z >= 5.0f*(map_size-1) - index_size/2 )
			dir_f = -1.0f;

		return index_movepos_f;
	}
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}
