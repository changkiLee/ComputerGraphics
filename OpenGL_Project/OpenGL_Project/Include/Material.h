#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "..\Include\Common.h"

class Material
{
private :
	// 재질
	float objEmission[3];		// 표면방출
	float objAmbient[3];		// 주변광
	float objDiffuse[3];		// 난반사
	float objSpecular[3];		// 전반사
	float objShiness;			// 반사도

public :
	Material();
	Material(const Material &cpy);
	virtual ~Material();

	// 재질
	void setEmission(const float emission[3]);
	void setEmission(const float &emissionR, const float &emissionG, const float &emissionB);
	void setAmbient(const float ambient[3]);
	void setAmbient(const float &ambientR, const float &ambientG, const float &ambientB);
	void setDiffuse(const float diffuse[3]);
	void setDiffuse(const float &diffuseR, const float &diffuseG, const float &diffuseB);
	void setSpecular(const float specular[3]);
	void setSpecular(const float &specularR, const float &specularG, const float &specularB);
	void setShiness(const float &shiness);
	
	void applyMaterial();
	void initMaterial();
};

#endif