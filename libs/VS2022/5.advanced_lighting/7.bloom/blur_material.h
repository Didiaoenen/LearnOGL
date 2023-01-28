#pragma once

#include <LearnOGLDefine.h>
#include <LearnOGLMaterial.h>

class blur_material : public OGL::LearnOGLMaterial
{
public:
	blur_material();
	blur_material(OGL::LearnOGLShader* shader);
	~blur_material();

	void FirstDraw();
	uint32_t DrawByIndex(uint32_t index);
	virtual void Draw() override;

	virtual void SetAttribID(GLuint attribID) override;

public:
	OGL::LearnOGLTexture* mImageTex{ nullptr };

	std::string mImageTexLoc = "imageTex";

private:
	GLuint mAttribID{ 0 };

};