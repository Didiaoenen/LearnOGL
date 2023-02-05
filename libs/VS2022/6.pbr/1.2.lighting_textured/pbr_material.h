#pragma once

#include <LearnOGLMaterial.h>

class pbr_material : public OGL::LearnOGLMaterial
{
public:
	pbr_material();
	pbr_material(OGL::LearnOGLShader* shader);
	~pbr_material();

	virtual void Draw() override;

private:


};