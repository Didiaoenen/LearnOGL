
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLTools.h"

#include "test_material.h"

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

		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));

		mShader = new OGL::LearnOGLShader("test.vs.vert", "test.fs.frag");
		mMaterial = new test_material(mShader);
		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);

		mTools = OGL::LearnOGLTools::Instance();

		mPlane = mTools->MakePlane(0.3f);
		mPlane.mMaterials.push_back(mMaterial);

		mCube = mTools->MakeCube(0.3f);
		mCube.mMaterials.push_back(mMaterial);
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OGL::oglTransform transform;
		glm::mat4 projection = mCamera->GetPerspectiveProjection(glm::radians(mCamera->mZoom), (float)info.windowWidth / (float)info.windowHeight, 0.1f, 100.0f);
		glm::mat4 view = mCamera->GetViewMatrix();

		transform.position = glm::vec3(-1.0f, 0.0f, 0.0f);
		transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		transform.rotation = glm::vec3(45.0f, 45.0f, 0.0f);

		mPlane.SetProjection(projection);
		mPlane.SetCameraView(view);
		mPlane.SetTransform(transform);
		mPlane.Draw();

		transform.position = glm::vec3(1.0f, 0.0f, 0.0f);
		transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		transform.rotation = glm::vec3(45.0f, 45.0f, 0.0f);

		mCube.SetProjection(projection);
		mCube.SetCameraView(view);
		mCube.SetTransform(transform);
		mCube.Draw();
	}

	virtual void ShutDown() override
	{

	}

private:
	test_material* mMaterial;

	OGL::LearnOGLCamera* mCamera;
	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLTools* mTools;

	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLBatch mCube;
};

DECLARE_MAIN(test)