#pragma once

#include <LearnOGLMaterial.h>

class g_buffer_material : public OGL::LearnOGLMaterial
{
public:
	g_buffer_material();
	g_buffer_material(OGL::LearnOGLShader* shader);
	~g_buffer_material();

	virtual void Draw() override;

private:

};

