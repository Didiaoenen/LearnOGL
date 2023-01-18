#pragma once

#include <LearnOGLMaterial.h>

class blur_material : public OGL::LearnOGLMaterial
{
public:
	blur_material();
	blur_material(OGL::LearnOGLShader* shader);
	~blur_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mImageTex{ nullptr };

	std::string mImageTexLoc = "imageTex";

private:

};