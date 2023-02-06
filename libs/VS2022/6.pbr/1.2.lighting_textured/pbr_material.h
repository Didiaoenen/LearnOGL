#pragma once

#include <LearnOGLMaterial.h>

class pbr_material : public OGL::LearnOGLMaterial
{
public:
	pbr_material();
	pbr_material(OGL::LearnOGLShader* shader);
	~pbr_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mAlbedoTex{ nullptr };
	OGL::LearnOGLTexture* mNormalTex{ nullptr };
	OGL::LearnOGLTexture* mMetallicTex{ nullptr };
	OGL::LearnOGLTexture* mRoughnessTex{ nullptr };
	OGL::LearnOGLTexture* mAOTex{ nullptr };

private:
	std::string mAlbedoLoc = "albedoTex";
	std::string mNormalLoc = "normalTex";
	std::string mMetallicLoc = "metallicTex";
	std::string mRoughnessLoc = "roughnessTex";
	std::string mAOLoc = "aoTex";

};