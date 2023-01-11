
#include <LearnOGLApp.h>
#include <LearnOGLTools.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLMaterial.h>

#include "normal_material.h"

class normal_mapping : public OGL::LearnOGLApp
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

		mShader = new OGL::LearnOGLShader("4.normal_mapping.vs.vert", "4.normal_mapping.fs.frag");

		mMaterial = new normal_material(mShader);
		mMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/brickwall.jpg", false, OGL::TextureType::Diffuse);
		mMaterial->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/brickwall_normal.jpg", false, OGL::TextureType::Normal);

		mTools = new OGL::LearnOGLTools();
		mQuad = mTools->MakeQuad(1.0f, true, true);
		mQuad.mMaterial = mMaterial;
	}

	virtual void Input() override
	{

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

private:
	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mQuad;
	OGL::LearnOGLCommand* mCommand;

	OGL::LearnOGLShader* mShader;

	normal_material* mMaterial;
	
	glm::vec3 mLightPos = glm::vec3(0.5f, 1.0f, 0.3f);
	glm::vec3 mLightColor = glm::vec3(0.2f, 0.2f, 0.2f);
};

DECLARE_MAIN(normal_mapping)