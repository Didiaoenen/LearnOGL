#pragma once

#include <LearnOGLMaterial.h>

class equirectangular_material : public OGL::LearnOGLMaterial
{
public:
	equirectangular_material();
	equirectangular_material(OGL::LearnOGLShader* shader);
	~equirectangular_material();

	virtual void Draw() override;

public:
	OGL::LearnOGLTexture* mEquirectangularTex;

private:

};