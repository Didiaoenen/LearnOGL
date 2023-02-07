#pragma once

#include <LearnOGLMaterial.h>

class cubemap_material : public OGL::LearnOGLMaterial
{
public:
	cubemap_material();
	cubemap_material(OGL::LearnOGLShader* shader);
	~cubemap_material();

	virtual void Draw() override;
	virtual void SetTexture(OGL::LearnOGLTexture* texture) override;
	virtual void BindTextures(uint32_t count) override;

public:
	OGL::LearnOGLTexture* mEquirectangularTex{ nullptr };

private:
	std::string mEquirectangularLoc = "equirectangularTex";

	std::vector<OGL::LearnOGLTexture*> mTexVec;

	uint32_t mTexCount{ 0 };

};

