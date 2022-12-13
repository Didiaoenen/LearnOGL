
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLModel.h"
#include "../LearnOGL/LearnOGLCamera.h"

#include "1.model_loading_material.h"

#include <iostream>

class model_loading : public OGL::LearnOGLApp
{
public:

	model_loading() :
		mMaterial(nullptr),
		mCamera(nullptr),
		mShader(nullptr),
		mModel(nullptr)
	{
	}

	virtual bool Init() override
	{
		return true;
	}

	virtual void Setup() override
	{
		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));

		mShader = new OGL::LearnOGLShader("1.model_loading.vs.vert", "1.model_loading.fs.frag");

		mMaterial = new model_loading_material(mShader);
		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/diffuse.jpg", OGL::TextureType::Diffuse);
		mMaterial->mNormalTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/normal.png", OGL::TextureType::Normal);
		mMaterial->mRoughnessTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/roughness.jpg", OGL::TextureType::Roughness);
		mMaterial->mSpecularTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/specular.jpg", OGL::TextureType::Specular);

		mModel = new OGL::LearnOGLModel("../../../resources/objects/backpack/backpack.obj");
		mModel->mMaterials.push_back(mMaterial);
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = mCamera->GetPerspectiveProjection(glm::radians(mCamera->mZoom), (float)info.windowWidth / (float)info.windowHeight, 0.1f, 100.0f);
		mModel->SetProjection(projection);

		glm::mat4 view = mCamera->GetViewMatrix();
		mModel->SetCameraView(view);

		OGL::oglTransform transform;
		transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
		transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
		transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		mModel->SetTransform(transform);

		mModel->Draw();
	}

private:
	model_loading_material* mMaterial;

	OGL::LearnOGLCamera* mCamera;
	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLModel* mModel;
};

DECLARE_MAIN(model_loading)