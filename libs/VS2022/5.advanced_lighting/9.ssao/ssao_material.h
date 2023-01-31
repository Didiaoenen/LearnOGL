#pragma once

#include <LearnOGLMaterial.h>

class ssao_material : public OGL::LearnOGLMaterial
{
public:
	ssao_material();
	ssao_material(OGL::LearnOGLShader* shader);
	~ssao_material();

	virtual void Draw() override;

private:
	std::string mPosLoc = "gPos";
	std::string mNormalLoc = "gNormal";
	std::string mTexNoiseLoc = "texNoise";

};