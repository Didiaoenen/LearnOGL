
#include <LearnOGLApp.h>
#include <LearnOGLModel.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>

#include "model_loading_material.h"

class model_loading : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{
		OGL::LearnOGLApp::Init();

		mPersInfo.fov = 60.0f;
		mPersInfo.width = info.windowWidth;
		mPersInfo.height = info.windowHeight;
		mPersInfo.zFar = 100.0f;
		mPersInfo.zNear = 0.1f;

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mShader = new OGL::LearnOGLShader("1.model_loading.vs.vert", "1.model_loading.fs.frag");
		mMaterial = new model_loading_material(mShader);
		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/diffuse.jpg", false, OGL::TextureType::Diffuse);
		mMaterial->mNormalTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/normal.png", false, OGL::TextureType::Normal);
		mMaterial->mRoughnessTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/roughness.jpg", false, OGL::TextureType::Roughness);
		mMaterial->mSpecularTexture = new OGL::LearnOGLTexture("../../../resources/objects/backpack/specular.jpg", false, OGL::TextureType::Specular);

		mModel = new OGL::LearnOGLModel("../../../resources/objects/backpack/backpack.obj");
		mModel->mMaterial = mMaterial;
	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		mContext->ExecuteCommand(mCommand);

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

	OGL::LearnOGLCommand* mCommand;

	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLModel* mModel;
};

DECLARE_MAIN(model_loading)