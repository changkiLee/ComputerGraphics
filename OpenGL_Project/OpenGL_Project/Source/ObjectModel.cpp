#include "..\Include\ObjectModel.h"

ObjectModel::ObjectModel()
{
	// 모델
	objPosition[0] = objPosition[1] = objPosition[2] = 0.0f;
	vNum = 0;
	fNum = 0;
	vVertList.clear();
	vNormalList.clear();
	vTexCoordList.clear();
	vFaceList.clear();
	vNormIdxList.clear();
	vTexCoordList.clear();
}

ObjectModel::~ObjectModel()
{
	vVertList.clear();
	vNormalList.clear();
	vTexCoordList.clear();
	vFaceList.clear();
	vNormIdxList.clear();
	vTexCoordList.clear();
}

void ObjectModel::clearModel()
{
	// 모델
	objPosition[0] = objPosition[1] = objPosition[2] = 0.0f;
	vNum = 0;
	fNum = 0;
	vVertList.clear();
	vNormalList.clear();
	vTexCoordList.clear();
	vFaceList.clear();
	vNormIdxList.clear();
	vTexCoordList.clear();
}

void ObjectModel::setPosition(const float pos[3])
{
	for(int i = 0; i < 3; i++)
		this->objPosition[i] = pos[i];
}

void ObjectModel::setPosition(const float &x, const float &y, const float &z)
{
	this->objPosition[0] = x;
	this->objPosition[1] = y;
	this->objPosition[2] = z;
}

bool ObjectModel::loadObjModel(const char* fName)
{
	clearModel();

	ifstream readStream(fName);
	if(!readStream.is_open())
		return false;
	
	//
	string tmpStr;		// 읽은 값(readStream) -> readString
	string properties;	// 속성(v, vn, vt, f) 읽은 값
	string faceLine;	// 면 읽은 값
	PVector3 tmpData;
	PIdx3 tmpFaceIdx;
	PIdx3 tmpNormIdx;
	PIdx3 tmpTexIdx;

	// Load object file
	while(getline(readStream, tmpStr))
	{
		istringstream readString(tmpStr);
		readString >> properties;

		// Load vertex
		if(properties == "v") {
			readString >> tmpData[0] >> tmpData[1] >> tmpData[2];
			vVertList.push_back(tmpData);
		}
		// Load vertex normal
		if(properties == "vn") {
			readString >> tmpData[0] >> tmpData[1] >> tmpData[2];
			vNormalList.push_back(tmpData);
		}

		// Load vertex texture coordinate
		if(properties == "vt") {
			readString >> tmpData[0] >> tmpData[1];
			vTexCoordList.push_back(tmpData);
		}

		//  v/vt/vn or v//vn or v/vt  : Load Face Idx
		if(properties == "f") { 
			for(int i = 0; i < 3; i++){
				readString >> faceLine;

				// "/" -> " " 로 변환
				while(faceLine.find("/") != string::npos)		// "/"가 없을때 까지
				{
					int pos = faceLine.find("/");
					faceLine.erase(pos, 1);
					faceLine.insert(pos, " ");
				}

				// 변환된 문자열을 다시 읽어들이기
				istringstream faceString(faceLine);
				
				faceString >> tmpData[0] >> tmpData[1] >> tmpData[2];
				
				if(i == 0) {
					tmpFaceIdx.idx[0] = (int)tmpData[0] - 1;
					tmpTexIdx.idx[0]  = (int)tmpData[1] - 1;
					tmpNormIdx.idx[0] = (int)tmpData[2] - 1;
				} else if(i == 1) {
					tmpFaceIdx.idx[1] = (int)tmpData[0] - 1;
					tmpTexIdx.idx[1]  = (int)tmpData[1] - 1;
					tmpNormIdx.idx[1] = (int)tmpData[2] - 1;
				} else if(i == 2) {
					tmpFaceIdx.idx[2] = (int)tmpData[0] - 1;
					tmpTexIdx.idx[2]  = (int)tmpData[1] - 1;
					tmpNormIdx.idx[2] = (int)tmpData[2] - 1;
				}
			}
			vFaceList.push_back(tmpFaceIdx);
			vNormIdxList.push_back(tmpNormIdx);
			vTexIdxList.push_back(tmpTexIdx);
		}
	}
	readStream.close();

	vNum = vVertList.size();
	fNum = vFaceList.size();

	return true;
}

bool ObjectModel::loadTxtModel(const char* fName)
{
	clearModel();

	FILE *fp;
	fopen_s(&fp, fName, "r");

	if(fp == NULL)
		return false;

	fscanf_s(fp, "%d", &vNum);
	fscanf_s(fp, "%d", &fNum);

	for (int i = 0; i < vNum; i++)
	{
		PVector3 tmpVertex;
		PVector3 tmpNormal(0.0, 0.0, 0.0);
		fscanf_s(fp, "%lf%lf%lf", &tmpVertex[0], &tmpVertex[1], &tmpVertex[2]);
		vVertList.push_back(tmpVertex);
		vNormalList.push_back(tmpNormal);
	}

	for (int i = 0; i < fNum; i++)
	{
		PIdx3 tmpFace;
		fscanf_s(fp, "%d%d%d", &tmpFace.idx[0], &tmpFace.idx[1], &tmpFace.idx[2]);
		vFaceList.push_back(tmpFace);

		// 노말계산
		PVector3 p0;
		PVector3 p1;
		PVector3 p2;
		
		p0 = vVertList[tmpFace.idx[0]];
		p1 = vVertList[tmpFace.idx[1]];
		p2 = vVertList[tmpFace.idx[2]];

		PVector3 pa;
		PVector3 pb;
		PVector3 pn;
		
		pa = p1 - p0;
		pb = p2 - p0;

		pn = pa ^ pb;
		
		vNormalList[tmpFace.idx[0]] += pn;
		vNormalList[tmpFace.idx[1]] += pn;
		vNormalList[tmpFace.idx[2]] += pn;
	}

	for (int i = 0; i < vNum; i++)
	{
		vNormalList[i].normalize();
	}

	fclose(fp);

	return true;
}

void ObjectModel::renderObject()
{
	glPushMatrix();
	{
		glTranslatef(this->objPosition[0], this->objPosition[1], this->objPosition[2]);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < fNum; i++)
		{
			int idx0, idx1, idx2;
			idx0 = vFaceList[i].idx[0];
			idx1 = vFaceList[i].idx[1];
			idx2 = vFaceList[i].idx[2];

 			glNormal3d(vNormalList[idx0][0], vNormalList[idx0][1], vNormalList[idx0][2]);
 			glVertex3d(vVertList[idx0][0], vVertList[idx0][1], vVertList[idx0][2]);
	 
 			glNormal3d(vNormalList[idx1][0], vNormalList[idx1][1], vNormalList[idx1][2]);
 			glVertex3d(vVertList[idx1][0], vVertList[idx1][1], vVertList[idx1][2]);
	 
 			glNormal3d(vNormalList[idx2][0], vNormalList[idx2][1], vNormalList[idx2][2]);
 			glVertex3d(vVertList[idx2][0], vVertList[idx2][1], vVertList[idx2][2]);
		}
		glEnd();
	}
	glPopMatrix();
}

void ObjectModel::renderVertNormal()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(objPosition[0], objPosition[1], objPosition[2]);

	for (int i = 0; i < vNum; ++i)
	{
		PVector3 p0 = vVertList[i];
		PVector3 p1 = p0 + (vNormalList[i]);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(p0[0], p0[1], p0[2]);
		glVertex3f(p1[0], p1[1], p1[2]);
		glEnd();
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void ObjectModel::renderPlane()
{
	glDisable(GL_LIGHTING);
	
	float rotMat[16];
	for(int i = 0; i < 16; i++)	// rotMat = I
	{
		if(i % 5 == 0)
			rotMat[i] = 1;
		else
			rotMat[i] = 0;
	}

	for(int i = 0; i < vNum; i++){
		glPushMatrix();
		{
			glTranslatef(vVertList[i][0], vVertList[i][1], vVertList[i][2]);
			
			PVector3 axis_x(0.0, 0.0, 0.0);
			PVector3 axis_y(vNormalList[i]);
			PVector3 axis_z(0.0, 0.0, 1.0);
			axis_x = axis_z ^ axis_y;
			axis_x.normalize();
			axis_z = axis_x ^ axis_y;
			axis_z.normalize();
			
			rotMat[0] = axis_x[0];
			rotMat[4] = axis_x[1];
			rotMat[8] = axis_x[2];
			
			rotMat[1] = axis_y[0];
			rotMat[5] = axis_y[1];
			rotMat[9] = axis_y[2];

			rotMat[2] = axis_z[0];
			rotMat[6] = axis_z[1];
			rotMat[10] = axis_z[2];
			glMultMatrixf(rotMat);
			
			glColor3f(0.0, 1.0, 0.5);
			glBegin(GL_TRIANGLES);
			glVertex3f(1.0, 0.0, 1.0);
			glVertex3f(-1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, -1.0);
			glVertex3f(-1.0, 0.0, 1.0);
			glVertex3f(-1.0, 0.0, -1.0);
			glVertex3f(1.0, 0.0, -1.0);
			glEnd();
		}
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
}