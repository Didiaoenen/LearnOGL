#pragma once

#include <LearnOGLMaterial.h>

class point_shadow_depth_material : public OGL::LearnOGLMaterial
{
public:
	point_shadow_depth_material();
	point_shadow_depth_material(OGL::LearnOGLShader* shadow);
	~point_shadow_depth_material();

	virtual void Draw() override;

private:
};

