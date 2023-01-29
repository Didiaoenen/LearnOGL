#pragma once

#include <LearnOGLMaterial.h>

class deferred_shading_material : public OGL::LearnOGLMaterial
{
public:
	deferred_shading_material();
	deferred_shading_material(OGL::LearnOGLShader* shader);
	~deferred_shading_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index) override;
	virtual void SetAttribID(GLuint attrib) override;

	void CommandDrawByIndex(GLuint index);

private:
	std::string mPosLoc = "gPos";
	std::string mNormalLoc = "gNormal";
	std::string mAlbedoLoc = "gAlbedo";

	GLuint mAttribID{ 0 };
};

