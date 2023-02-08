#pragma once

#include <LearnOGLMaterial.h>

class brdf_material : public OGL::LearnOGLMaterial
{
public:
	brdf_material();
	brdf_material(OGL::LearnOGLShader* shader);
	~brdf_material();

	virtual void Draw() override;

private:

};