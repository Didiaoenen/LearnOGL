#pragma once

#include <LearnOGLMaterial.h>

class irradiance_material : public OGL::LearnOGLMaterial
{
public:
	irradiance_material();
	irradiance_material(OGL::LearnOGLShader* shader);
	~irradiance_material();

	virtual void Draw() override;

private:

};