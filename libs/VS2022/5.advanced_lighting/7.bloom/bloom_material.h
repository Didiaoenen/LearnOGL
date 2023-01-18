#pragma once

#include <LearnOGLMaterial.h>

class bloom_material : public OGL::LearnOGLMaterial
{
public:
	bloom_material();
	bloom_material(OGL::LearnOGLShader* shader);
	~bloom_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{ nullptr };

	std::string mDiffuseTexLoc = "diffuseTex";

private:

};