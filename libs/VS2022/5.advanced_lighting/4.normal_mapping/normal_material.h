#pragma once

#include <LearnOGLMaterial.h>

class normal_material : OGL::LearnOGLMaterial
{
public:
	normal_material();
	normal_material(OGL::LearnOGLShader* shader);
	~normal_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{ nullptr };
	OGL::LearnOGLTexture* mNormalTex{ nullptr };

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mNormalTexLoc = "normalTex";

private:

};

