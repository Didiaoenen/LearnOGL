#pragma once

#include <LearnOGLMaterial.h>

class ssao_blur_material : public OGL::LearnOGLMaterial
{
public:
	ssao_blur_material();
	ssao_blur_material(OGL::LearnOGLShader* shader);
	~ssao_blur_material();

private:
	std::string mSSAOLoc = "ssaoInput";

};