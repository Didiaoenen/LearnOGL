#pragma once

#include <LearnOGLMaterial.h>

class irradiance_material : public OGL::LearnOGLMaterial
{
public:
	irradiance_material();
	irradiance_material(OGL::LearnOGLShader* shader);
	~irradiance_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attrib) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

private:
	std::string mEnvironmentLoc = "environmentTex";

	GLuint mAttribID{ 0 };

};