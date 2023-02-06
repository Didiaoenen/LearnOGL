#pragma once

#include <LearnOGLMaterial.h>

class background_material : public OGL::LearnOGLMaterial
{
public:
	background_material();
	background_material(OGL::LearnOGLShader* shader);
	~background_material();

	virtual void Draw() override;

private:

};

