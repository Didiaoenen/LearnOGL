#pragma once

#include <LearnOGLMaterial.h>

class ssao_blur_material : public OGL::LearnOGLMaterial
{
public:
	ssao_blur_material();
	ssao_blur_material(OGL::LearnOGLShader* shader);
	~ssao_blur_material();

	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attrib) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

private:
	std::string mSSAOLoc = "ssaoInput";

	GLuint mAttribID{ 0 };
};