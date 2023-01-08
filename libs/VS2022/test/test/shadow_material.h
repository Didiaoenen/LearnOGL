#pragma once

#include <LearnOGLMaterial.h>

class shadow_material : public OGL::LearnOGLMaterial
{
public:
	shadow_material();
	shadow_material(OGL::LearnOGLShader* shader);
	virtual ~shadow_material();

	virtual void Draw() override;

public:


private:

};

