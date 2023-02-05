#include "pbr_material.h"

pbr_material::pbr_material()
{
}

pbr_material::pbr_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
}

pbr_material::~pbr_material()
{
}

void pbr_material::Draw()
{
	mShader->Use();

}
