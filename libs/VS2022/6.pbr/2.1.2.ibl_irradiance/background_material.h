#pragma once

#include <LearnOGLMaterial.h>

class background_material : public OGL::LearnOGLMaterial
{
public:
	background_material();
	background_material(OGL::LearnOGLShader* shader);
	~background_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attrib) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

private:
	std::string mEnviromentLoc = "environmentTex";

	GLuint mAttribID{ 0 };

};