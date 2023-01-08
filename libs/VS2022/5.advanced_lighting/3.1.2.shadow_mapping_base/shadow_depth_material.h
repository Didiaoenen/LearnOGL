#pragma once

#include <LearnOGLMaterial.h>

class shadow_depth_material : public OGL::LearnOGLMaterial
{
public:
	shadow_depth_material();
	shadow_depth_material(OGL::LearnOGLShader* shadow);
	~shadow_depth_material();

	virtual void Draw() override;

private:
};

