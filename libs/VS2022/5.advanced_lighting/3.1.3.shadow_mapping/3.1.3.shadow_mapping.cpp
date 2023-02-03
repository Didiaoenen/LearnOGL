
#include <LearnOGLApp.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLBatch.h>

#include "shadow_material.h"
#include "shadow_depth_material.h"

class shaodw_mapping : public OGL::LearnOGLApp
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

		mOrthoInfo.left = -info.windowWidth / 200.0f;
		mOrthoInfo.right = info.windowWidth / 200.0f;
		mOrthoInfo.bottom = -info.windowHeight / 200.0f;
		mOrthoInfo.top = info.windowHeight / 200.0f;
		mOrthoInfo.zNear = -10.0f;
		mOrthoInfo.zFar = 10.0f;

		mShadowAtlasWidth = info.windowWidth * 4;
		mShadowAtlasHeight = info.windowHeight * 4;

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mTools = new OGL::LearnOGLTools();

		mShader = new OGL::LearnOGLShader("3.1.3.shadow_mapping.vs.vert", "3.1.3.shadow_mapping.fs.frag");
		mShadowShader = new OGL::LearnOGLShader("3.1.3.shadow_mapping_depth.vs.vert", "3.1.3.shadow_mapping_depth.fs.frag");

		mPlaneMaterial = new shadow_material(mShader);
		mPlaneMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", true, false, OGL::TextureType::Diffuse);
		mPlaneMaterial->mCommand = mCommand;

		mCubeMaterial = new shadow_material(mShader);
		mCubeMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container.jpg", true, false, OGL::TextureType::Diffuse);
		mCubeMaterial->mCommand = mCommand;

		mBackpackMaterial = new shadow_material(mShader);
		mBackpackMaterial->mDiffuseTex = new OGL::LearnOGLTexture("../../../resources/objects/backpack/diffuse.jpg", true, false, OGL::TextureType::Diffuse);
		mBackpackMaterial->mCommand = mCommand;

		mDepthMaterial = new shadow_depth_material(mShadowShader);

		mDepthAttribID = mShader->GetAttribID("depthMap");

		mPlane = mTools->MakePlane(10.0f);
		mPlane.mMaterial = mPlaneMaterial;
		mPlane.mShadowMaterial = mDepthMaterial;

		mCube = mTools->MakeCube(0.5f);
		mCube.mMaterial = mCubeMaterial;
		mCube.mShadowMaterial = mDepthMaterial;

		mBackpack = new OGL::LearnOGLModel("../../../resources/objects/backpack/backpack.obj");
		mBackpack->mMaterial = mBackpackMaterial;
		mBackpack->mShadowMaterial = mDepthMaterial;
	}

	virtual void Input() override
	{

	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		RenderShadow();
	}

	void RenderShadow()
	{
		OGL::LearnOGLPipeline pipeline;
		glm::mat4 lightProj = pipeline.GetOrthographicProjection(mOrthoInfo.left, mOrthoInfo.right, mOrthoInfo.top, mOrthoInfo.bottom, mOrthoInfo.zNear, mOrthoInfo.zFar);
		glm::mat4 lightView = pipeline.GetViewMatrix(mLightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		mCommand->SetViewport(0, 0, mShadowAtlasWidth, mShadowAtlasHeight);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mCommand->GetTemporaryRT(mDepthAttribID, mShadowAtlasWidth, mShadowAtlasHeight);
		mCommand->SetRenderTarget(mDepthAttribID);
		{
			mCommand->ClearRenderTarget(true, false, glm::vec4(0.0f));
			mContext->ExecuteCommand(mCommand, false);

			mShadowShader->Use();
			mShadowShader->SetMat4("vpMatrix", lightProj * lightView);

			pipeline.SetPos(0.0f, 0.0f, 0.0f);
			pipeline.SetScale(1.0f, 1.0f, 1.0f);
			pipeline.SetRotate(0.0f, 0.0f, 0.0f);
			mPlane.SetShadowTransform(pipeline.GetTransform());
			mPlane.ShadowDraw();

			pipeline.SetPos(-2.0f, 0.5f, 0.0f);
			pipeline.SetScale(1.0f, 1.0f, 1.0f);
			pipeline.SetRotate(0.0f, 45.0f, 0.0f);
			mCube.SetShadowTransform(pipeline.GetTransform());
			mCube.ShadowDraw();

			pipeline.SetPos(2.0f, 2.0f, 0.0f);
			pipeline.SetScale(0.5f, 0.5f, 0.5f);
			pipeline.SetRotate(0.0f, 45.0f, 0.0f);
			mBackpack->SetShadowTransform(pipeline.GetTransform());
			mBackpack->ShadowDraw();
		}
		mCommand->ReleaseTemporaryRT(mDepthAttribID);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
		mContext->ExecuteCommand(mCommand, false);

		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);

		pipeline.SetCamera(mCamera);

		pipeline.SetPos(0.0f, -1.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);

		mShader->Use();
		mShader->SetMat4("projection", pipeline.GetCameraProjection());
		mShader->SetMat4("view", pipeline.GetTransform() * pipeline.GetCameraView());
		mShader->SetMat4("lightSpaceMatrix", lightProj * lightView);
		mShader->SetVec3("lightPos", mLightPos);
		mShader->SetVec3("lightColor", mLightColor);
		mShader->SetVec3("viewPos", mCamera->mPosition);

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mPlane.SetTransform(pipeline.GetTransform());
		mPlane.Draw();

		pipeline.SetPos(-2.0f, 0.5f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mCube.SetTransform(pipeline.GetTransform());
		mCube.Draw();

		pipeline.SetPos(2.0f, 2.0f, 0.0f);
		pipeline.SetScale(0.5f, 0.5f, 0.5f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mBackpack->SetTransform(pipeline.GetTransform());
		mBackpack->Draw();
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLTools* mTools;

	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLShader* mShadowShader;

	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLBatch mCube;
	OGL::LearnOGLModel* mBackpack;

	GLuint mDepthAttribID;

	shadow_material* mPlaneMaterial;
	shadow_material* mCubeMaterial;
	shadow_material* mBackpackMaterial;
	shadow_depth_material* mDepthMaterial;

	glm::vec3 mLightPos = glm::vec3(-3.0f, 3.0f, 0.0f);
	glm::vec3 mLightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	GLfloat mShadowAtlasWidth;
	GLfloat mShadowAtlasHeight;
};

DECLARE_MAIN(shaodw_mapping)