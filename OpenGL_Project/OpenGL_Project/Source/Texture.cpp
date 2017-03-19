#include "..\Include\Texture.h"

Texture::Texture()
{
	width = 0;
	height = 0;
	texId = 0;
	pData = NULL;
}

Texture::~Texture()
{
	delete [] pData;
}

bool Texture::loadBmpFile(const char *fname)
{
	FILE *fp;
	fopen_s(&fp, fname, "rb");

	if(fp == NULL)
		return false;

	// windows.h gives us these types to work with the Bitmap files
	BITMAPFILEHEADER fileheader; 
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	// Read the fileheader
	fread(&fileheader, sizeof(fileheader), 1, fp);
	fseek(fp, sizeof(fileheader), SEEK_SET); // Jump the fileheader
	fread(&infoheader, sizeof(infoheader), 1, fp); // and read the infoheader

	width = infoheader.biWidth;
	height = infoheader.biHeight;
	int size = infoheader.biWidth * infoheader.biHeight;

	// Now we need to allocate the memory for our image (width * height * color deep)
	pData = new byte [size * 4];
	
	// And fill it with zeros
	memset(pData, 0, size * 4);

	// 픽셀 저장
	for (int i = 0, j = 0; i < size; ++i)
	{            
		fread(&rgb, sizeof(rgb), 1, fp); // load RGB value
		pData[j + 0] = rgb.rgbtRed; 
		pData[j + 1] = rgb.rgbtGreen; 
		pData[j + 2] = rgb.rgbtBlue; 
		pData[j + 3] = 255; // Alpha value
		j += 4; 
	}

	fclose(fp);

	return true;
}

void Texture::applyTexture()
{
	if(pData != NULL) 
	{
		// 텍스쳐 셋팅
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pData);

		// Binding
		glBindTexture(GL_TEXTURE_2D, texId);
	}
	else{
		// Binding
		glBindTexture(GL_TEXTURE_2D, texId);
	}
}