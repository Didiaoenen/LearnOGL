#pragma once

#include <LearnOGLMaterial.h>

class hdr_material : public OGL::LearnOGLMaterial
{
public:
	hdr_material();
	hdr_material(OGL::LearnOGLShader* shader);
	~hdr_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mHDRTex{ nullptr };

	std::string mHDRTexLoc = "hdrTex";

private:
	GLuint mHDRAttribID{ 0 };

};