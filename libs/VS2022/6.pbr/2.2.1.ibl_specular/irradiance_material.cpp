#include "irradiance_material.h"

irradiance_material::irradiance_material()
{
}

irradiance_material::irradiance_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
}

irradiance_material::~irradiance_material()
{
}

void irradiance_material::Draw()
{
	mShader->Use();
}
