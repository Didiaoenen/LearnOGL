#pragma once

#include <LearnOGLMaterial.h>

class pbr_material : public OGL::LearnOGLMaterial
{
public:
	pbr_material();
	pbr_material(OGL::LearnOGLShader* shader);
	~pbr_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attrib) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

private:
	std::string mIrradianceLoc = "irradianceTex";

	GLuint mAttribID{ 0 };
};