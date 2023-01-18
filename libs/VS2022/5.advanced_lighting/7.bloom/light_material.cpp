#include "light_material.h"

light_material::light_material()
{
}

light_material::light_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
}

light_material::~light_material()
{
}

void light_material::Draw()
{
}
