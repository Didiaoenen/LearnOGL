#include "background_material.h"

background_material::background_material()
{
}

background_material::background_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
}

background_material::~background_material()
{
}

void background_material::Draw()
{
	mShader->Use();
}
