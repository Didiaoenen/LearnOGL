
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

		mShadowAtlasWidth = info.windowWidth * 4;
		mShadowAtlasHeight = info.windowHeight * 4;

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mTools = new OGL::LearnOGLTools();

		mShader = new OGL::LearnOGLShader("3.1.2.shadow_mapping.vs.vert", "3.1.2.shadow_mapping.fs.frag");
		mShadowShader = new OGL::LearnOGLShader("3.1.2.shadow_mapping_depth.vs.vert", "3.1.2.shadow_mapping_depth.fs.frag");
	
		mPlaneMaterial = new shadow_material(mShader);
		mPlaneMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);
		mPlaneMaterial->mCommand = mCommand;

		mCubeMaterial1 = new shadow_material(mShader);
		mCubeMaterial1->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container.jpg", OGL::TextureType::Diffuse);
		mCubeMaterial1->mCommand = mCommand;

		mCubeMaterial2 = new shadow_material(mShader);
		mCubeMaterial2->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container2.png", OGL::TextureType::Diffuse);
		mCubeMaterial2->mCommand = mCommand;

		mCubeMaterial3 = new shadow_material(mShader);
		mCubeMaterial3->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container2_specular.png", OGL::TextureType::Diffuse);
		mCubeMaterial3->mCommand = mCommand;

		mCubeMaterial4 = new shadow_material(mShader);
		mCubeMaterial4->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container2_specular_colored.png", OGL::TextureType::Diffuse);
		mCubeMaterial4->mCommand = mCommand;

		mDepthMaterial = new shadow_depth_material(mShadowShader);

		mDepthAttribID = mShader->GetUniformLocation("depthMap");

		mPlane = mTools->MakePlane(10.0f);
		mPlane.mMaterial = mPlaneMaterial;
		mPlane.mShadowMaterial = mDepthMaterial;

		mCube1 = mTools->MakeCube(0.5f);
		mCube1.mMaterial = mCubeMaterial1;
		mCube1.mShadowMaterial = mDepthMaterial;

		mCube2 = mTools->MakeCube(0.5f);
		mCube2.mMaterial = mCubeMaterial2;
		mCube2.mShadowMaterial = mDepthMaterial;

		mCube3 = mTools->MakeCube(0.5f);
		mCube3.mMaterial = mCubeMaterial3;
		mCube3.mShadowMaterial = mDepthMaterial;

		mCube4 = mTools->MakeCube(0.5f);
		mCube4.mMaterial = mCubeMaterial4;
		mCube4.mShadowMaterial = mDepthMaterial;
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
		mCommand->SetViewport(0, 0, mShadowAtlasWidth, mShadowAtlasHeight);

		mCommand->GetTemporaryRT(mDepthAttribID, mShadowAtlasWidth, mShadowAtlasHeight, 0);
		mCommand->SetRenderTarget(mDepthAttribID);
		mCommand->ClearRenderTarget(true, false, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		mContext->ExecuteCommand(mCommand);

		OGL::LearnOGLPipeline pipeline;
		glm::mat4 lightProj = pipeline.GetOrthographicProjection(mOrthoInfo.left, mOrthoInfo.right, mOrthoInfo.top, mOrthoInfo.bottom, mOrthoInfo.zNear, mOrthoInfo.zFar);
		glm::mat4 lightView = pipeline.GetViewMatrix(mLightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		mShadowShader->Use();
		mShadowShader->SetMat4("vpMatrix", lightProj * lightView);

		pipeline.SetPos(5.0f, 0.5f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mCube1.SetShadowTransform(pipeline.GetTransform());
		mCube1.ShadowDraw();

		pipeline.SetPos(-5.0f, 0.5f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mCube2.SetShadowTransform(pipeline.GetTransform());
		mCube2.ShadowDraw();

		pipeline.SetPos(0.0f, 0.5f, 5.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mCube3.SetShadowTransform(pipeline.GetTransform());
		mCube3.ShadowDraw();

		pipeline.SetPos(0.0f, 0.5f, -5.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
		mCube4.SetShadowTransform(pipeline.GetTransform());
		mCube4.ShadowDraw();

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mPlane.SetShadowTransform(pipeline.GetTransform());
		mPlane.ShadowDraw();

		mCommand->ReleaseTemporaryRT(mDepthAttribID);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);
		
		pipeline.SetCamera(mCamera);

		glm::mat4 cameraView = pipeline.GetCameraView();

		pipeline.SetPos(0.0f, -1.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		cameraView = pipeline.GetTransform() * cameraView;

		mShader->Use();
		mShader->SetMat4("projection", pipeline.GetCameraProjection());
		mShader->SetMat4("view", cameraView);
		mShader->SetMat4("lightSpaceMatrix", lightProj * lightView);
		mShader->SetVec3("lightPos", mLightPos);
		mShader->SetVec3("lightColor", mLightColor);
		mShader->SetVec3("viewPos", mCamera->mPosition);

		mPlane.Draw();

		mCube1.Draw();
		mCube2.Draw();
		mCube3.Draw();
		mCube4.Draw();
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
	OGL::LearnOGLBatch mCube1;
	OGL::LearnOGLBatch mCube2;
	OGL::LearnOGLBatch mCube3;
	OGL::LearnOGLBatch mCube4;

	GLuint mDepthAttribID;

	shadow_material* mPlaneMaterial;
	shadow_material* mCubeMaterial1;
	shadow_material* mCubeMaterial2;
	shadow_material* mCubeMaterial3;
	shadow_material* mCubeMaterial4;
	shadow_depth_material* mDepthMaterial;

	glm::vec3 mLightPos = glm::vec3(-3.0f, 3.0f, 0.0f);
	glm::vec3 mLightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	GLfloat mShadowAtlasWidth;
	GLfloat mShadowAtlasHeight;
};

DECLARE_MAIN(shaodw_mapping_base)