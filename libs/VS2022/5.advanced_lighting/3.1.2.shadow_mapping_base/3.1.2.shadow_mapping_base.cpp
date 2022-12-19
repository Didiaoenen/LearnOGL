
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLMaterial.h"
#include "../LearnOGL/LearnOGLCommand.h"
#include "../LearnOGL/LearnOGLPipeline.h"
#include "../LearnOGL/LearnOGLTools.h"
#include "../LearnOGL/LearnOGLBatch.h"

#include "shadow_material.h"
#include "shadow_depth_material.h"

class shaodw_mapping_base : public OGL::LearnOGLApp
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

		return true;
	}

	virtual void Setup() override
	{
		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 0.0f));

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mTools = new OGL::LearnOGLTools();

		mShader = new OGL::LearnOGLShader("3.1.2.shadow_mapping.vs.vert", "3.1.2.shadow_mapping.fs.frag");
		mShadowShader = new OGL::LearnOGLShader("3.1.2.shadow_mapping_depth.vs.vert", "3.1.2.shadow_mapping_depth.fs.frag");
	
		mPlaneMaterial = new shadow_material(mShader);
		mPlaneMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);
		mPlaneMaterial->mCommand = mCommand;

		mCubeMaterial = new shadow_material(mShader);
		mCubeMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container.jpg", OGL::TextureType::Diffuse);
		mCubeMaterial->mCommand = mCommand;

		mDepthMaterial = new shadow_depth_material(mShadowShader);

		mDepthAttribID = mShadowShader->GetUniformLocation("depthMap");

		mPlane = mTools->MakePlane(10.0f);
		mPlane.mMaterial = mPlaneMaterial;

		mCube = mTools->MakeCube(1.0f);
		mCube.mMaterial = mCubeMaterial;
		mCube.mShadowMaterial = mDepthMaterial;
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
		//mCommand->GetTemporaryRT(mDepthAttribID, 2048, 2048, 0);
		//mCommand->SetRenderTarget(mDepthAttribID);
		//mCommand->ClearRenderTarget(true, false, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		//mContext->ExecuteCommand(mCommand);

		OGL::LearnOGLPipeline pipeline;
		glm::mat4 projection = pipeline.GetOrthographicProjection(mOrthoInfo.left, mOrthoInfo.right, mOrthoInfo.top, mOrthoInfo.bottom, mOrthoInfo.zNear, mOrthoInfo.zFar);
		glm::mat4 view = pipeline.GetViewMatrix(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//
		//pipeline.SetPos(0.0f, 0.0f, 0.0f);
		//pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(30.0f, 0.0f, 0.0f);

		//view = pipeline.GetTransform() * view;

		//pipeline.SetPos(0.0f, 0.5f, 0.0f);
		//pipeline.SetScale(1.0f, 1.0f, 1.0f);
		//pipeline.SetRotate(0.0f, 45.0f, 0.0f);

		//mCube.SetShadowProjection(projection * view);
		//mCube.SetShadowTransform(pipeline.GetTransform());
		//mCube.ShadowDraw();

		//mCommand->ReleaseTemporaryRT(mDepthAttribID);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);
		
		pipeline.SetCamera(mCamera);

		glm::mat4 cameraView = pipeline.GetCameraView();

		pipeline.SetPos(0.0f, -3.0f, -20.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		cameraView = pipeline.GetTransform() * cameraView;

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mPlane.SetProjection(pipeline.GetCameraProjection());
		mPlane.SetCameraView(cameraView);
		mPlane.SetTransform(pipeline.GetTransform());
		mPlane.mMaterial->mShader->SetMat4("lightSpaceMatrix", projection * view);
		mPlane.mMaterial->mShader->SetVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
		mPlane.mMaterial->mShader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		mPlane.mMaterial->mShader->SetVec3("viewPos", mCamera->mPosition);
		mPlane.Draw();

		pipeline.SetPos(0.0f, 0.5f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mCube.mMaterial->mShader->SetMat4("lightSpaceMatrix", projection * view);
		mCube.mMaterial->mShader->SetVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
		mCube.mMaterial->mShader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		mCube.mMaterial->mShader->SetVec3("viewPos", mCamera->mPosition);
		mCube.SetProjection(pipeline.GetCameraProjection());
		mCube.SetCameraView(cameraView);
		mCube.SetTransform(pipeline.GetTransform());
		mCube.Draw();
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCamera* mCamera;
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLTools* mTools;

	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLShader* mShadowShader;

	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLBatch mCube;

	GLuint mDepthAttribID;

	shadow_material* mPlaneMaterial;
	shadow_material* mCubeMaterial;
	shadow_depth_material* mDepthMaterial;
};

DECLARE_MAIN(shaodw_mapping_base)