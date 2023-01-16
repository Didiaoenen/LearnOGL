#pragma once

#include <LearnOGLMaterial.h>

class hdr_material : public OGL::LearnOGLMaterial
{
public:
	hdr_material();
	hdr_material(OGL::LearnOGLShader* shader);
	~hdr_material();

	virtual void Draw() override;

private:

};