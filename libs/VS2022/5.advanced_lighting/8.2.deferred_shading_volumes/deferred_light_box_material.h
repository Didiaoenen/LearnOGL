#pragma once

#include <LearnOGLMaterial.h>

class deferred_light_box_material : public OGL::LearnOGLMaterial
{
public:
	deferred_light_box_material();
	deferred_light_box_material(OGL::LearnOGLShader* shader);
	~deferred_light_box_material();

	virtual void Draw() override;

private:

};