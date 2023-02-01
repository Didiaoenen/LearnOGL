#pragma once

#include <LearnOGLDefine.h>
#include <LearnOGLMaterial.h>

class blur_material : public OGL::LearnOGLMaterial
{
public:
	blur_material();
	blur_material(OGL::LearnOGLShader* shader);
	~blur_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attribID) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

public:
	std::string mImageTexLoc = "imageTex";

private:
	GLuint mAttribID{ 0 };

};