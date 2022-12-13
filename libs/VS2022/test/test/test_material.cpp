#include "test_material.h"

test_material::test_material()
{
}

test_material::test_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
}

test_material::~test_material()
{
}

void test_material::Draw()
{
}
