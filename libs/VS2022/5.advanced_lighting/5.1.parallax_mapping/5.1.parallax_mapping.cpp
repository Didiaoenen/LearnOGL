
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

#include "normal_material.h"
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

		mNormalShader = new OGL::LearnOGLShader("5.1.parallax_mapping.vs.vert", "5.1.parallax_mapping.fs.frag");
		mNormalMaterial = new normal_material(mNormalShader);
		mNormalMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2.jpg", false, OGL::TextureType::Diffuse);
		mNormalMaterial->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_normal.jpg", false, OGL::TextureType::Normal);

		mParallaxShader = new OGL::LearnOGLShader("5.1.parallax_mapping.vs.vert", "5.1.parallax_mapping.fs.frag");
		mParallaxMaterial = new parallax_material(mParallaxShader);
		mParallaxMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2.jpg", false, OGL::TextureType::Diffuse);
		mParallaxMaterial->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_normal.jpg", false, OGL::TextureType::Normal);
		mParallaxMaterial->mDepthTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_disp.jpg", false, OGL::TextureType::Parallax);

		mTools = new OGL::LearnOGLTools();
		mNormalQuad = mTools->MakeQuad(1.0f, true, true);
		mNormalQuad.mMaterial = mNormalMaterial;

		mParallaxQuad = mTools->MakeQuad(1.0f, true, true);
		mParallaxQuad.mMaterial = mParallaxMaterial;
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

		mNormalShader->Use();
		mNormalShader->SetMat4("projection", pipeline.GetCameraProjection());
		mNormalShader->SetMat4("view", pipeline.GetCameraView());
		mNormalShader->SetVec3("lightPos", mLightPos1);
		mNormalShader->SetVec3("lightColor", mLightColor);
		mNormalShader->SetVec3("viewPos", mCamera->mPosition);

		pipeline.SetPos(-1.5f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(mLastTime * -10.0f, 0.0f, mLastTime * -10.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);

		mNormalQuad.SetTransform(pipeline.GetTransform());
		mNormalQuad.Draw();

		mParallaxShader->Use();
		mParallaxShader->SetMat4("projection", pipeline.GetCameraProjection());
		mParallaxShader->SetMat4("view", pipeline.GetCameraView());
		mParallaxShader->SetVec3("lightPos", mLightPos2);
		mParallaxShader->SetVec3("lightColor", mLightColor);
		mParallaxShader->SetVec3("viewPos", mCamera->mPosition);
		mParallaxShader->SetFloat("heightScale", mheightScale);

		pipeline.SetPos(1.5f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(mLastTime * -10.0f, 0.0f, mLastTime * -10.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mParallaxQuad.SetTransform(pipeline.GetTransform());
		mParallaxQuad.Draw();
	}

	virtual void ShutDown() override
	{

	}

	virtual void Input() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLShader* mNormalShader;
	OGL::LearnOGLShader* mParallaxShader;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mNormalQuad;
	OGL::LearnOGLBatch mParallaxQuad;

	normal_material* mNormalMaterial;
	parallax_material* mParallaxMaterial;

	glm::vec3 mLightPos1 = glm::vec3(-1.0f, 1.0f, 0.3f);
	glm::vec3 mLightPos2 = glm::vec3(2.0f, 1.0f, 0.3f);
	glm::vec3 mLightColor = glm::vec3(0.2f, 0.2f, 0.2f);

	float mheightScale = 0.1f;
};

DECLARE_MAIN(parallax_mapping)