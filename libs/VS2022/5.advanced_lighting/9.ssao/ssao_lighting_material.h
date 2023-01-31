#pragma once

#include <LearnOGLMaterial.h>

class ssao_lighting_material : public OGL::LearnOGLMaterial
{
public:
	ssao_lighting_material();
	ssao_lighting_material(OGL::LearnOGLShader* shader);
	~ssao_lighting_material();

	virtual void Draw() override;

private:
	std::string mPosLoc = "gPos";
	std::string mNormalLoc = "gNormal";
	std::string mAlbedoLoc = "gAlbedo";
	std::string mSSAOLoc = "ssao";

};