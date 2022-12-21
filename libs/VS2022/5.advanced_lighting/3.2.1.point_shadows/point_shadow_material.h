#pragma once

#include "../LearnOGL/LearnOGLMaterial.h"

class point_shadow_material : public OGL::LearnOGLMaterial
{
public:
	point_shadow_material();
	point_shadow_material(OGL::LearnOGLShader* shader);
	~point_shadow_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mDiffuseTex;

	std::string mDiffuseTexLoc = "diffuseTex";
	std::string mShadowMapLoc = "depthMap";

private:
	GLuint mDepthAttribID;

};

