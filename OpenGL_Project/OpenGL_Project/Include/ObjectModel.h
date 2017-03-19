#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

#include "..\Include\Common.h"
#include "..\Include\PVector3.h"
#include "..\Include\Material.h"
#include "..\Include\Texture.h"

class ObjectModel
{
private :
	// 인덱스 저장용 구조체
	typedef struct PIdx3 {
		int idx[3];
	}PIdx3;

	// 모델
	float objPosition[3];	// 모델의 위치
	int vNum;	// 정점 배열의 개수
	int fNum;	// 면 배열의 개수
	vector <PVector3> vVertList;		// 정점의 좌표 배열
	vector <PVector3> vNormalList;		// 법선의 좌표 배열
	vector <PVector3> vTexCoordList;	// 텍스쳐의 좌표 배열
	vector <PIdx3> vFaceList;			// 면의 인덱스 배열
	vector <PIdx3> vNormIdxList;		// 법선의 인덱스 배열
	vector <PIdx3> vTexIdxList;			// 텍스쳐의 인덱스 배열

public : 
	ObjectModel();
	virtual ~ObjectModel();

	// 모델
	void clearModel();
	void setPosition(const float pos[3]);
	void setPosition(const float &x, const float &y, const float &z);
	bool loadObjModel(const char* fName);
	bool loadTxtModel(const char* fName);
	void renderObject();
	void renderVertNormal();
	void renderPlane();
};

#endif