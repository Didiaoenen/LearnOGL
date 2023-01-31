#pragma once

#include <LearnOGLMaterial.h>

class ssao_geometry_material : public OGL::LearnOGLMaterial
{
public:
	ssao_geometry_material();
	ssao_geometry_material(OGL::LearnOGLShader* shader);
	~ssao_geometry_material();

	virtual void Draw() override;

private:

};