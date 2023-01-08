#pragma once

#include <LearnOGLMaterial.h>

class shadow_material : public OGL::LearnOGLMaterial
{
public:
	shadow_material();
	shadow_material(OGL::LearnOGLShader* shadow);
	~shadow_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex;

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mShadowMapLoc = "depthMap";

private:
	GLuint mDepthAttribID;

};

