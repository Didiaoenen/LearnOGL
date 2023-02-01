#pragma once

#include <LearnOGLMaterial.h>

class ssao_material : public OGL::LearnOGLMaterial
{
public:
	ssao_material();
	ssao_material(OGL::LearnOGLShader* shader);
	~ssao_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attrib) override;
	virtual void SetTexture(OGL::LearnOGLTexture* texture) override;
	virtual void BindTextures(uint32_t count) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

private:
	std::string mPosLoc = "gPos";
	std::string mNormalLoc = "gNormal";
	std::string mTexNoiseLoc = "texNoise";

	GLuint mAttribID{ 0 };
	uint32_t mTexCount{ 0 };

	std::vector<OGL::LearnOGLTexture*> mTexVec;
};