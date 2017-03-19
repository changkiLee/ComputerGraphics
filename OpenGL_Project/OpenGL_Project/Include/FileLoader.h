#ifndef _FILELOADER_H_
#define _FILELOADER_H_
#include "..\Include\Common.h"
#include "..\Include\ObjectModel.h"
#include "..\Include\Texture.h"

class FileLoader
{
private : 

public :
	FileLoader();
	virtual ~FileLoader();

	// File Load
	void objFileLoad(ObjectModel &objModel, const char* fileName);
	void txtFileLoad(ObjectModel &txtModel, const char* fileName);
	void bmpFileLoad(Texture &bmp, const char* fileName);
};

#endif