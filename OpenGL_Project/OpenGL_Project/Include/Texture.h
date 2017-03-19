#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "..\Include\Common.h"

class Texture
{
private : 
	int width;
	int height;
	GLuint texId;

	unsigned char *pData; // The pointer to the memory zone in which we will load the texture

public :
	Texture();
	virtual ~Texture();

	bool loadBmpFile(const char *fname);
	void applyTexture();
};

#endif