#pragma once

#include <LearnOGLMaterial.h>

class lighting_material : public OGL::LearnOGLMaterial
{
public:
	lighting_material();
	lighting_material(OGL::LearnOGLShader* shader);
	~lighting_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{ nullptr };

	std::string mDiffuseTexLoc = "diffuseTex";

private:

};