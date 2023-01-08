#pragma once

#include <LearnOGLMaterial.h>

class model_loading_material : public OGL::LearnOGLMaterial
{
public:
	model_loading_material();
	model_loading_material(OGL::LearnOGLShader* shader);
	~model_loading_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTexture;
	OGL::LearnOGLTexture* mNormalTexture;
	OGL::LearnOGLTexture* mRoughnessTexture;
	OGL::LearnOGLTexture* mSpecularTexture;

private:
	std::string mDiffuseLoc = "diffuseTex";
	std::string mNormalLoc = "normalTex";
	std::string mRoughnessLoc = "roughnessTex";
	std::string mSpecularLoc = "specularTex";
};

