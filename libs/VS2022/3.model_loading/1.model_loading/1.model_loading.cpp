
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLModel.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLPipeline.h"

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
		OGL::LearnOGLApp::Init();

		mCameraType = OGL::CameraType::Perspective;
		mPersInfo.fov = 45.0f;
		mPersInfo.width = info.windowWidth;
		mPersInfo.height = info.windowHeight;
		mPersInfo.zFar = 100.0f;
		mPersInfo.zNear = 0.1f;

		return true;
	}

	virtual void Setup() override
	{
		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 10.0f));
		mCamera->SetCameraInfo(mCameraType, &mPersInfo);

		mShader = new OGL::LearnOGLShader("1.model_loading.vs.vert", "1.model_loading.fs.frag");
		mMaterial = new model_loading_material(mShader);
		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/diffuse.jpg", OGL::TextureType::Diffuse);
		mMaterial->mNormalTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/normal.png", OGL::TextureType::Normal);
		mMaterial->mRoughnessTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/roughness.jpg", OGL::TextureType::Roughness);
		mMaterial->mSpecularTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/specular.jpg", OGL::TextureType::Specular);

		mModel = new OGL::LearnOGLModel("../../../resources/objects/backpack/backpack.obj");
		mModel->mMaterial = mMaterial;
	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderModel();
	}

	void RenderModel()
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mShader->Use();
		mShader->SetMat4("projection", pipeline.GetCameraProjection());
		mShader->SetMat4("view", pipeline.GetCameraView());

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mModel->SetTransform(pipeline.GetTransform());
		mModel->Draw();
	}

private:
	model_loading_material* mMaterial;

	OGL::LearnOGLCamera* mCamera;
	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLModel* mModel;
};

DECLARE_MAIN(model_loading)