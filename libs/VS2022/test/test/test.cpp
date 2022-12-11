
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLShader.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLMaterial.h"
#include "../LearnOGL/LearnOGLTools.h"

#include <iostream>

class test : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{
		return true;
	}

	virtual void Setup() override
	{
		glEnable(GL_DEPTH_TEST);

		oglCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));

		oglShader = new OGL::LearnOGLShader("test.vs.vert", "test.fs.frag");
		oglMaterial = new OGL::LearnOGLMaterial(oglShader);
		oglMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);

		oglTools = OGL::LearnOGLTools::Instance();

		oglPlane = oglTools->MakePlane(0.3f);
		oglPlane.mMaterials.push_back(*oglMaterial);

		oglCube = oglTools->MakeCube(0.3f);
		oglCube.mMaterials.push_back(*oglMaterial);
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OGL::oglTransform transform;
		glm::mat4 projection = oglCamera->GetPerspectiveProjection(glm::radians(oglCamera->mZoom), (float)info.windowWidth / (float)info.windowHeight, 0.1f, 100.0f);
		glm::mat4 view = oglCamera->GetViewMatrix();

		transform.position = glm::vec3(-1.0f, 0.0f, 0.0f);
		transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		transform.rotation = glm::vec3(45.0f, 45.0f, 0.0f);

		oglPlane.SetProjection(projection);
		oglPlane.SetCameraView(view);
		oglPlane.SetTransform(transform);
		oglPlane.Draw();

		transform.position = glm::vec3(1.0f, 0.0f, 0.0f);
		transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		transform.rotation = glm::vec3(45.0f, 45.0f, 0.0f);

		oglCube.SetProjection(projection);
		oglCube.SetCameraView(view);
		oglCube.SetTransform(transform);
		oglCube.Draw();
	}

	virtual void ShutDown() override
	{

	}

private:

	OGL::LearnOGLBatch oglPlane;
	OGL::LearnOGLBatch oglCube;

	OGL::LearnOGLTools* oglTools;
	OGL::LearnOGLShader* oglShader;
	OGL::LearnOGLMaterial* oglMaterial;
	OGL::LearnOGLCamera* oglCamera;
};

DECLARE_MAIN(test)