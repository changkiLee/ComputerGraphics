#include "..\Include\Material.h"

Material::Material()
{
	// ÀçÁú
	for(int i = 0; i < 3; i++)
	{
		objEmission[i] = 0.0f;
		objAmbient[i] = 0.2f;
		objDiffuse[i] = 0.8f;
		objSpecular[i] = 0.0f;
	}
	objShiness = 0.0f;
}

Material::Material(const Material &cpy)
{
	for(int i = 0; i < 3; i++)
	{
		objEmission[i] = cpy.objEmission[i];
		objAmbient[i] = cpy.objAmbient[i];
		objDiffuse[i] = cpy.objDiffuse[i];
		objSpecular[i] = cpy.objSpecular[i];
	}
	objShiness = cpy.objShiness;
}

Material::~Material()
{

}

void Material::setEmission(const float emission[3])
{
	for(int i = 0; i < 3; i++)
	{
		objEmission[i] = emission[i];
	}
}

void Material::setEmission(const float &emissionR, const float &emissionG, const float &emissionB)
{
	objEmission[0] = emissionR;
	objEmission[1] = emissionG;
	objEmission[2] = emissionB;
}

void Material::setAmbient(const float ambient[3])
{
	for(int i = 0; i < 3; i++)
	{
		objAmbient[i] = ambient[i];
	}
}

void Material::setAmbient(const float &ambientR, const float &ambientG, const float &ambientB)
{
	objAmbient[0] = ambientR;
	objAmbient[1] = ambientG;
	objAmbient[2] = ambientB;
}

void Material::setDiffuse(const float diffuse[3])
{
	for(int i = 0; i < 3; i++)
	{
		objDiffuse[i] = diffuse[i];
	}
}

void Material::setDiffuse(const float &diffuseR, const float &diffuseG, const float &diffuseB)
{
	objDiffuse[0] = diffuseR;
	objDiffuse[1] = diffuseG;
	objDiffuse[2] = diffuseB;
}

void Material::setSpecular(const float specular[3])
{
	for(int i = 0; i < 3; i++)
	{
		objSpecular[i] = specular[i];
	}
}

void Material::setSpecular(const float &specularR, const float &specularG, const float &specularB)
{
	objSpecular[0] = specularR;
	objSpecular[1] = specularG;
	objSpecular[2] = specularB;
}

void Material::setShiness(const float &shiness)
{
	objShiness = shiness;
}

void Material::applyMaterial()
{
	glMaterialfv(GL_FRONT, GL_EMISSION, objEmission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, objAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, objShiness);
}

void Material::initMaterial()
{
	for(int i = 0; i < 3; i++)
	{
		objEmission[i] = 0.0f;
		objAmbient[i] = 0.2f;
		objDiffuse[i] = 0.8f;
		objSpecular[i] = 0.0f;
	}
	objShiness = 0.0f;
}