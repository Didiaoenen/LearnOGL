#pragma once

#include <LearnOGLMaterial.h>

class steep_normal_material : public OGL::LearnOGLMaterial
{
public:
	steep_normal_material();
	steep_normal_material(OGL::LearnOGLShader* shader);
	~steep_normal_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{ nullptr };
	OGL::LearnOGLTexture* mNormalTex{ nullptr };

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mNormalTexLoc = "normalTex";

private:

};

