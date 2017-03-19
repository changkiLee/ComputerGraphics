#include "..\Include\ObjectPickList.h"

ObjectPickList::ObjectPickList()
{
	objPickList.clear();

	selectObjectId = -1;
}

ObjectPickList::~ObjectPickList()
{
	objPickList.clear();
}

void ObjectPickList::addObject(ObjectModel *obj)
{
	objPickList.push_back(obj);
}

void ObjectPickList::setSelectObjectId(const int &id)
{
	selectObjectId = id;
}

void ObjectPickList::pickObject(Camera &c, const int &x, const int &y)
{
	GLuint hits, selectBuf[256];
	int viewport[4];

	// 선택 버퍼 지정
	glSelectBuffer(256, selectBuf);
	// 뷰포트 변환 정보 얻기
	glGetIntegerv(GL_VIEWPORT, viewport);

	// 렌더링 모드 변경
	glRenderMode(GL_SELECT);

	// 네임스택 초기화 및 '0' 추가
	glInitNames();
	glPushName(0);

	// P = I * 선택행렬 * 관측행렬
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((double)x, (double)(viewport[3] - y), 10.0, 10.0, viewport);
	gluPerspective(60.0, (double)c.getWidth()/(double)c.getHeight(), 0.1, 100.0);

	// 객체 선택
	glMatrixMode(GL_MODELVIEW);
	renderPickList(GL_SELECT);

	// 원래대로...
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// 객체 그리기
	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);
	if(hits > 0)
		setSelectObjectId(selectBuf[3]);
	glutPostRedisplay();
}

void ObjectPickList::renderPickList(GLenum mode)
{
	for(int i = 0; i < (int)objPickList.size(); i++)
	{
		glPushMatrix();

		// 그리기
		if(mode == GL_SELECT)
			glLoadName(i);

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		objPickList[i]->renderObject();
		glEnable(GL_LIGHTING);
				
		// 선택 그리기
		if(selectObjectId == i)
		{
			objPickList[i]->renderVertNormal();
		}
		glPopMatrix();
	}
}