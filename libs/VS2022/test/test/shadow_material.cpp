#include "shadow_material.h"

shadow_material::shadow_material()
{
}

shadow_material::shadow_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
}

shadow_material::~shadow_material()
{
}

void shadow_material::Draw()
{
	mShader->Use();
}
