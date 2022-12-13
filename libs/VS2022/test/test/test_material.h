#pragma once

#include "../LearnOGL/LearnOGLMaterial.h"

class test_material : public OGL::LearnOGLMaterial
{
public:
	test_material();
	test_material(OGL::LearnOGLShader* shader);
	virtual ~test_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTexture;

private:
	std::string mDiffuseLoc = "diffuseTex";

};

