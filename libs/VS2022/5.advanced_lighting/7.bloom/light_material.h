#pragma once

#include <LearnOGLMaterial.h>

class light_material : public OGL::LearnOGLMaterial
{
public:
	light_material();
	light_material(OGL::LearnOGLShader* shader);
	~light_material();

	virtual void Draw() override;

private:

};

