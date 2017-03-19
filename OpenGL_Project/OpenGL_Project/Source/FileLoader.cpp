#include "..\Include\FileLoader.h"

FileLoader::FileLoader()
{

}

FileLoader::~FileLoader()
{

}

// File Load
void FileLoader::objFileLoad(ObjectModel &objModel, const char* fileName)
{
	if(!objModel.loadObjModel(fileName))
	{
		cout << " Not Find to obj files "<<endl;
		exit(0);
	}
}

void FileLoader::txtFileLoad(ObjectModel &txtModel, const char* fileName)
{
	if(!txtModel.loadTxtModel(fileName))
	{
		cout << " Not Find to txt files "<<endl;
		exit(0);
	}
}

void FileLoader::bmpFileLoad(Texture &bmp, const char* fileName)
{
	if(!bmp.loadBmpFile(fileName))
	{
		cout << " Not Find to bmp files "<<endl;
		exit(0);
	}
}