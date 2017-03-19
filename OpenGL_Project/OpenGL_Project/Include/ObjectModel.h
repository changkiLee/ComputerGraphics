#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

#include "..\Include\Common.h"
#include "..\Include\PVector3.h"
#include "..\Include\Material.h"
#include "..\Include\Texture.h"

class ObjectModel
{
private :
	// �ε��� ����� ����ü
	typedef struct PIdx3 {
		int idx[3];
	}PIdx3;

	// ��
	float objPosition[3];	// ���� ��ġ
	int vNum;	// ���� �迭�� ����
	int fNum;	// �� �迭�� ����
	vector <PVector3> vVertList;		// ������ ��ǥ �迭
	vector <PVector3> vNormalList;		// ������ ��ǥ �迭
	vector <PVector3> vTexCoordList;	// �ؽ����� ��ǥ �迭
	vector <PIdx3> vFaceList;			// ���� �ε��� �迭
	vector <PIdx3> vNormIdxList;		// ������ �ε��� �迭
	vector <PIdx3> vTexIdxList;			// �ؽ����� �ε��� �迭

public : 
	ObjectModel();
	virtual ~ObjectModel();

	// ��
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