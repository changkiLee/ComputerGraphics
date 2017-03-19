#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "..\Include\Common.h"

class Material
{
private :
	// ����
	float objEmission[3];		// ǥ�����
	float objAmbient[3];		// �ֺ���
	float objDiffuse[3];		// ���ݻ�
	float objSpecular[3];		// ���ݻ�
	float objShiness;			// �ݻ絵

public :
	Material();
	Material(const Material &cpy);
	virtual ~Material();

	// ����
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