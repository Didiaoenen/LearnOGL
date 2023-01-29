#include "g_buffer_material.h"

g_buffer_material::g_buffer_material()
{
}

g_buffer_material::g_buffer_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
}

g_buffer_material::~g_buffer_material()
{
}

void g_buffer_material::Draw()
{
	mShader->Use();
}
