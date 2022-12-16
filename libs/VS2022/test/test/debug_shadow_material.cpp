#include "debug_shadow_material.h"

debug_shadow_material::debug_shadow_material()
{
}

debug_shadow_material::debug_shadow_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)

{
	mShader->Use();
	mShader->SetTexUnit(mDepthMapLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

debug_shadow_material::~debug_shadow_material()
{
}

void debug_shadow_material::Draw()
{
	mShader->Use();
}
