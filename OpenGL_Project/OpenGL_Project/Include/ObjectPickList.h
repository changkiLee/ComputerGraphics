#ifndef _OBJECTPICKLIST_H_
#define _OBJECTPICKLIST_H_

#include "..\Include\Common.h"
#include "..\Include\Camera.h"
#include "..\Include\ObjectModel.h"

class ObjectPickList
{
private :
	vector <ObjectModel*> objPickList;

	int selectObjectId;
	void setSelectObjectId(const int &id);

public :
	ObjectPickList();
	virtual ~ObjectPickList();

	void addObject(ObjectModel *obj);
	void pickObject(Camera &c, const int &x, const int &y);
	void renderPickList(GLenum mode);
};

#endif