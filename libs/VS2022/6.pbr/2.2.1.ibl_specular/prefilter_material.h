#pragma once

#include <LearnOGLMaterial.h>

class prefilter_material : public OGL::LearnOGLMaterial
{
public:
	prefilter_material();
	prefilter_material(OGL::LearnOGLShader* shader);
	~prefilter_material();

	virtual void Draw() override;

private:

};