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

	// ���� ���� ����
	glSelectBuffer(256, selectBuf);
	// ����Ʈ ��ȯ ���� ���
	glGetIntegerv(GL_VIEWPORT, viewport);

	// ������ ��� ����
	glRenderMode(GL_SELECT);

	// ���ӽ��� �ʱ�ȭ �� '0' �߰�
	glInitNames();
	glPushName(0);

	// P = I * ������� * �������
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((double)x, (double)(viewport[3] - y), 10.0, 10.0, viewport);
	gluPerspective(60.0, (double)c.getWidth()/(double)c.getHeight(), 0.1, 100.0);

	// ��ü ����
	glMatrixMode(GL_MODELVIEW);
	renderPickList(GL_SELECT);

	// �������...
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// ��ü �׸���
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

		// �׸���
		if(mode == GL_SELECT)
			glLoadName(i);

		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.0f, 0.0f);
		objPickList[i]->renderObject();
		glEnable(GL_LIGHTING);
				
		// ���� �׸���
		if(selectObjectId == i)
		{
			objPickList[i]->renderVertNormal();
		}
		glPopMatrix();
	}
}