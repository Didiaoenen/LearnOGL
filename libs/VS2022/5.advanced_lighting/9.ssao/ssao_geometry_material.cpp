#include "ssao_geometry_material.h"

ssao_geometry_material::ssao_geometry_material()
{
}

ssao_geometry_material::ssao_geometry_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();

}

ssao_geometry_material::~ssao_geometry_material()
{

}

void ssao_geometry_material::Draw()
{
	mShader->Use();
}
