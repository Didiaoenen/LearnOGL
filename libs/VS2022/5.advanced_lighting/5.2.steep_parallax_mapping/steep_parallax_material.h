#pragma once

#include <LearnOGLMaterial.h>

class steep_parallax_material : public OGL::LearnOGLMaterial
{
public:
	steep_parallax_material();
	steep_parallax_material(OGL::LearnOGLShader* shader);
	~steep_parallax_material();
	
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

