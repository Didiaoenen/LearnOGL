#pragma once

#include "../LearnOGL/LearnOGLMaterial.h"

class debug_shadow_material : public OGL::LearnOGLMaterial
{
public:
	debug_shadow_material();
	debug_shadow_material(OGL::LearnOGLShader* shader);
	~debug_shadow_material();

private:
};

