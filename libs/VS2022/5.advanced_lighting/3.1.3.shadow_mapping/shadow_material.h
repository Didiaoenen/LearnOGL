#pragma once

#include "../LearnOGL/LearnOGLMaterial.h"

#include <string>

class shadow_material : public OGL::LearnOGLMaterial
{
public:
	shadow_material();
	shadow_material(OGL::LearnOGLShader* shadow);
	~shadow_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex{nullptr};

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mShadowMapLoc = "depthMap";

private:
	GLuint mDepthAttribID{0};

};

