
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

#include "parallax_material.h"

class parallax_mapping : public OGL::LearnOGLApp
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
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mShader = new OGL::LearnOGLShader("5.1.parallax_mapping.vs.vert", "5.1.parallax_mapping.fs.frag");
		mMaterial = new parallax_material(mShader);
		mMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2.jpg", false, OGL::TextureType::Diffuse);
		mMaterial->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_normal.jpg", false, OGL::TextureType::Normal);
		mMaterial->mDepthTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_disp.jpg", false, OGL::TextureType::Parallax);

		mTools = new OGL::LearnOGLTools();
		mQuad = mTools->MakeQuad(1.0f, true, true);
		mQuad.mMaterial = mMaterial;
	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->SetViewport(0.0f, 0.0f, info.windowWidth, info.windowHeight);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mShader->Use();
		mShader->SetMat4("projection", pipeline.GetCameraProjection());
		mShader->SetMat4("view", pipeline.GetCameraView());
		mShader->SetVec3("lightPos", mLightPos);
		mShader->SetVec3("lightColor", mLightColor);
		mShader->SetVec3("viewPos", mCamera->mPosition);
		mShader->SetFloat("heightScale", mheightScale);

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(mLastTime * -10.0f, 0.0f, mLastTime * -10.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);

		mQuad.SetTransform(pipeline.GetTransform());
		mQuad.Draw();
	}

	virtual void ShutDown() override
	{

	}

	virtual void Input() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLShader* mShader;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mQuad;

	parallax_material* mMaterial;

	glm::vec3 mLightPos = glm::vec3(0.5f, 1.0f, 0.3f);
	glm::vec3 mLightColor = glm::vec3(0.2f, 0.2f, 0.2f);

	float mheightScale = 0.1f;
};

DECLARE_MAIN(parallax_mapping)