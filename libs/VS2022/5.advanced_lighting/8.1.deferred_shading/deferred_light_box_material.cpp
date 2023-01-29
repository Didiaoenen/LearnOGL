#include "deferred_light_box_material.h"

deferred_light_box_material::deferred_light_box_material()
{
}

deferred_light_box_material::deferred_light_box_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
}

deferred_light_box_material::~deferred_light_box_material()
{
}

void deferred_light_box_material::Draw()
{
	mShader->Use();
}
