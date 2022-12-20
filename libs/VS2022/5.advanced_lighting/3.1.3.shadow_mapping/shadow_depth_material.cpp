#include "shadow_depth_material.h"

shadow_depth_material::shadow_depth_material()
{
}

shadow_depth_material::shadow_depth_material(OGL::LearnOGLShader* shadow) :
	OGL::LearnOGLMaterial(shadow)
{
}

shadow_depth_material::~shadow_depth_material()
{
}

void shadow_depth_material::Draw()
{
	mShader->Use();
}
