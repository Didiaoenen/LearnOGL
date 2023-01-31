#pragma once

#include <LearnOGLMaterial.h>

#include <map>

class ssao_lighting_material : public OGL::LearnOGLMaterial
{
public:
	ssao_lighting_material();
	ssao_lighting_material(OGL::LearnOGLShader* shader);
	~ssao_lighting_material();

	virtual void Draw() override;
	virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0) override;
	virtual void SetAttribID(GLuint attrib) override;

	void CommandDrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);

private:
	std::string mPosLoc = "gPos";
	std::string mNormalLoc = "gNormal";
	std::string mAlbedoLoc = "gAlbedo";
	std::string mSSAOLoc = "ssao";

	std::map<GLuint, bool> mAttribMap;
	std::map<uint32_t, OGL::LearnOGLFBO*> mDrawTexMap;
};