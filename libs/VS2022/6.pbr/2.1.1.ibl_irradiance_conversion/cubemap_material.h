#pragma once

#include <LearnOGLMaterial.h>

class cubemap_material : public OGL::LearnOGLMaterial
{
public:
	cubemap_material();
	cubemap_material(OGL::LearnOGLShader* shader);
	~cubemap_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mEquirectangularTex;

private:
	std::string mEquirectangularLoc;

};

