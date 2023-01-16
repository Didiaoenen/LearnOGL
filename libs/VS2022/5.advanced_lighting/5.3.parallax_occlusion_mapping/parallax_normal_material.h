#pragma once

#include <LearnOGLMaterial.h>

class parallax_normal_material : public OGL::LearnOGLMaterial
{
public:
	parallax_normal_material();
	parallax_normal_material(OGL::LearnOGLShader* shader);
	~parallax_normal_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{ nullptr };
	OGL::LearnOGLTexture* mNormalTex{ nullptr };

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mNormalTexLoc = "normalTex";

private:
};