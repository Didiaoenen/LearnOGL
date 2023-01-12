#pragma once

#include <LearnOGLMaterial.h>

class parallax_material : public OGL::LearnOGLMaterial
{
public:
	parallax_material();
	parallax_material(OGL::LearnOGLShader* shader);
	~parallax_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{ nullptr };
	OGL::LearnOGLTexture* mNormalTex{ nullptr };
	OGL::LearnOGLTexture* mDepthTex{ nullptr };

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mNormalTexLoc = "normalTex";
	std::string mDepthTexLoc = "depthTex";

private:

};

