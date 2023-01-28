#pragma once

#include <LearnOGLMaterial.h>

class final_material : public OGL::LearnOGLMaterial
{
public:
	final_material();
	final_material(OGL::LearnOGLShader* shader);
	~final_material();

	virtual void Draw() override;
	virtual void SetAttribID(GLuint attribID) override;

public:
	OGL::LearnOGLTexture* mSceneTex{ nullptr };
	OGL::LearnOGLTexture* mBloomBlurTex{ nullptr };

	std::string mSceneTexLoc = "sceneTex";
	std::string mBloomBlurTexLoc = "bloomBlurTex";

	std::string mTexLoc = "bloomBlurTex";
private:
	GLuint mSceneTexAttribID{ 0 };
	GLuint mAttribID{ 0 };
};
