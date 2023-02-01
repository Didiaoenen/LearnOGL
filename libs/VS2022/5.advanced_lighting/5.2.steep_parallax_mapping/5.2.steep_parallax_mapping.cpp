
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

#include "steep_normal_material.h"
#include "steep_parallax_material.h"

class steep_parallax_mapping : public OGL::LearnOGLApp
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
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mNormalShader = new OGL::LearnOGLShader("5.2.steep_parallax_mapping.vs.vert", "5.2.steep_parallax_mapping.fs.frag");
		mNormalMaterial = new steep_normal_material(mNormalShader);
		mNormalMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2.jpg", false, false, OGL::TextureType::Diffuse);
		mNormalMaterial->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_normal.jpg", false, false, OGL::TextureType::Normal);

		mParallaxShader1 = new OGL::LearnOGLShader("5.2.steep_parallax_mapping.vs.vert", "5.2.steep_parallax_mapping.fs.frag");
		mParallaxMaterial1 = new steep_parallax_material(mParallaxShader1);
		mParallaxMaterial1->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2.jpg", false, false, OGL::TextureType::Diffuse);
		mParallaxMaterial1->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_normal.jpg", false, false, OGL::TextureType::Normal);
		mParallaxMaterial1->mDepthTex = new OGL::LearnOGLTexture("./../../../resources/textures/bricks2_disp.jpg", false, false, OGL::TextureType::Parallax);

		mParallaxShader2 = new OGL::LearnOGLShader("5.2.steep_parallax_mapping.vs.vert", "5.2.steep_parallax_mapping.fs.frag");
		mParallaxMaterial2 = new steep_parallax_material(mParallaxShader1);
		mParallaxMaterial2->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/toy_box_diffuse.png", false, false, OGL::TextureType::Diffuse);
		mParallaxMaterial2->mNormalTex = new OGL::LearnOGLTexture("./../../../resources/textures/toy_box_normal.png", false, false, OGL::TextureType::Normal);
		mParallaxMaterial2->mDepthTex = new OGL::LearnOGLTexture("./../../../resources/textures/toy_box_disp.png", false, false, OGL::TextureType::Parallax);

		mTools = new OGL::LearnOGLTools();
		mNormalQuad = mTools->MakeQuad(1.0f, true, true);
		mNormalQuad.mMaterial = mNormalMaterial;

		mParallaxQuad1 = mTools->MakeQuad(1.0f, true, true);
		mParallaxQuad1.mMaterial = mParallaxMaterial1;

		mParallaxQuad2 = mTools->MakeQuad(1.0f, true, true);
		mParallaxQuad2.mMaterial = mParallaxMaterial2;
	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mCommand->SetViewport(0.0f, 0.0f, info.windowWidth, info.windowHeight);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mNormalShader->Use();
		mNormalShader->SetMat4("projection", pipeline.GetCameraProjection());
		mNormalShader->SetMat4("view", pipeline.GetCameraView());
		mNormalShader->SetVec3("lightPos", mLightPos1);
		mNormalShader->SetVec3("lightColor", mLightColor);
		mNormalShader->SetVec3("viewPos", mCamera->mPosition);

		pipeline.SetPos(-3.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(mLastTime * -10.0f, 0.0f, mLastTime * -10.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);

		mNormalQuad.SetTransform(pipeline.GetTransform());
		mNormalQuad.Draw();

		mParallaxShader1->Use();
		mParallaxShader1->SetMat4("projection", pipeline.GetCameraProjection());
		mParallaxShader1->SetMat4("view", pipeline.GetCameraView());
		mParallaxShader1->SetVec3("lightPos", mLightPos2);
		mParallaxShader1->SetVec3("lightColor", mLightColor);
		mParallaxShader1->SetVec3("viewPos", mCamera->mPosition);
		mParallaxShader1->SetFloat("heightScale", mheightScale);

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(mLastTime * -10.0f, 0.0f, mLastTime * -10.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mParallaxQuad1.SetTransform(pipeline.GetTransform());
		mParallaxQuad1.Draw();

		mParallaxShader1->Use();
		mParallaxShader1->SetMat4("projection", pipeline.GetCameraProjection());
		mParallaxShader1->SetMat4("view", pipeline.GetCameraView());
		mParallaxShader1->SetVec3("lightPos", mLightPos3);
		mParallaxShader1->SetVec3("lightColor", mLightColor);
		mParallaxShader1->SetVec3("viewPos", mCamera->mPosition);
		mParallaxShader1->SetFloat("heightScale", mheightScale);

		pipeline.SetPos(3.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(mLastTime * -10.0f, 0.0f, mLastTime * -10.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mParallaxQuad2.SetTransform(pipeline.GetTransform());
		mParallaxQuad2.Draw();
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
	OGL::LearnOGLShader* mParallaxShader1;
	OGL::LearnOGLShader* mParallaxShader2;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mNormalQuad;
	OGL::LearnOGLBatch mParallaxQuad1;
	OGL::LearnOGLBatch mParallaxQuad2;

	steep_normal_material* mNormalMaterial;
	steep_parallax_material* mParallaxMaterial1;
	steep_parallax_material* mParallaxMaterial2;

	glm::vec3 mLightPos1 = glm::vec3(-2.5f, 1.0f, 0.3f);
	glm::vec3 mLightPos2 = glm::vec3(0.5f, 1.0f, 0.3f);
	glm::vec3 mLightPos3 = glm::vec3(3.5f, 1.0f, 0.3f);
	glm::vec3 mLightColor = glm::vec3(0.2f, 0.2f, 0.2f);

	float mheightScale = 0.1f;
};

DECLARE_MAIN(steep_parallax_mapping)