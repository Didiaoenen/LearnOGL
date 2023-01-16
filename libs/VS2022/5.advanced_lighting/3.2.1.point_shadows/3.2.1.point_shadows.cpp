
#include <LearnOGLApp.h>
#include <LearnOGLTools.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLMaterial.h>

#include "point_shadow_material.h"
#include "point_shadow_depth_material.h"

#include <vector>

#define NUM_LAYERS 6

class point_shadows : public OGL::LearnOGLApp
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

		mShadowAtlasWidth = 1024 * 4;
		mShadowAtlasHeight = 1024 * 4;

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mShader = new OGL::LearnOGLShader("3.2.1.point_shadows.vs.vert", "3.2.1.point_shadows.fs.frag");
		mShadowShader = new OGL::LearnOGLShader("3.2.1.point_shadows_depth.vs.vert", "3.2.1.point_shadows_depth.fs.frag", "3.2.1.point_shadows_depth.gs.geom");
		
		mPlaneMaterial = new point_shadow_material(mShader);
		mPlaneMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", false, OGL::TextureType::Diffuse);
		mPlaneMaterial->mCommand = mCommand;

		mCubeMaterial = new point_shadow_material(mShader);
		mCubeMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container.jpg", false, OGL::TextureType::Diffuse);
		mCubeMaterial->mCommand = mCommand;

		mShadowMaterial = new point_shadow_depth_material(mShadowShader);
	
		mDepthAttribID = mShader->GetUniformLocation("depthMap");

		mTool = new OGL::LearnOGLTools();

		mPlane = mTool->MakePlane(10.0f);
		mPlane.mMaterial = mPlaneMaterial;
		mPlane.mShadowMaterial = mShadowMaterial;

		for (int i = 0; i < 4; i++)
		{
			auto cube = mTool->MakeCube(0.5f);
			cube.mMaterial = mCubeMaterial;
			cube.mShadowMaterial = mShadowMaterial;
			mCubes.push_back(cube);
		}
	}

	virtual void Input() override
	{

	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->SetViewport(0, 0, mShadowAtlasWidth, mShadowAtlasHeight);

		mCommand->GetTemporaryCubeMapRT(mDepthAttribID, mShadowAtlasWidth, mShadowAtlasHeight);
		mCommand->SetRenderTarget(mDepthAttribID);
		mCommand->ClearRenderTarget(true, false, glm::vec4(0.0));
		mContext->ExecuteCommand(mCommand);

		OGL::LearnOGLPipeline pipeline;

		float zFar = 25.0f;
		glm::mat4 shadowProj = pipeline.GetPerspectiveProjection(90.0f, mShadowAtlasWidth / mShadowAtlasHeight, 1.0f, zFar);
	
		mShadowShader->Use();
		for (uint32_t i = 0; i < NUM_LAYERS; i++)
		{
			mShadowShader->SetMat4("shadowMatrices[" + std::to_string(i) + "]", shadowProj * pipeline.GetViewMatrix(mLightPos, mLightPos + mCameraDirs[i].mCenter, mCameraDirs[i].mUp));
		}
		mShadowShader->SetFloat("farPlane", zFar);
		mShadowShader->SetVec3("lightPos", mLightPos);

		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mPlane.SetShadowTransform(pipeline.GetTransform());
		mPlane.ShadowDraw();

		std::vector<glm::vec3> mPos;
		mPos.push_back(glm::vec3( 3.0f, 0.5f,  0.0f));
		mPos.push_back(glm::vec3(-3.0f, 0.5f,  0.0f));
		mPos.push_back(glm::vec3( 0.0f, 0.5f,  3.0f));
		mPos.push_back(glm::vec3( 0.0f, 0.5f, -3.0f));

		for (int i = 0; i < 4; i++)
		{
			pipeline.SetPos(mPos[i].x, mPos[i].y, mPos[i].z);
			mCubes[i].SetShadowTransform(pipeline.GetTransform());
			mCubes[i].ShadowDraw();
		}

		mCommand->ReleaseTemporaryRT(mDepthAttribID);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);

		pipeline.SetCamera(mCamera);

		mShader->Use();
		mShader->SetMat4("projection", pipeline.GetCameraProjection());
		mShader->SetMat4("view", pipeline.GetCameraView());
		mShader->SetVec3("lightPos", mLightPos);
		mShader->SetVec3("lightColor", mLightColor);
		mShader->SetVec3("viewPos", mCamera->mPosition);
		mShader->SetFloat("farPlane", zFar);

		mPlane.SetTransform(pipeline.GetTransform());
		mPlane.Draw();

		for (int i = 0; i < 4; i++)
		{
			mCubes[i].SetTransform(pipeline.GetTransform());
			mCubes[i].Draw();
		}
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLTools* mTool;
	OGL::LearnOGLBatch mPlane;
	std::vector<OGL::LearnOGLBatch> mCubes;

	OGL::LearnOGLCommand* mCommand;

	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLShader* mShadowShader;

	GLuint mDepthAttribID;

	point_shadow_material* mPlaneMaterial;
	point_shadow_material* mCubeMaterial;
	point_shadow_depth_material* mShadowMaterial;

	float mShadowAtlasWidth;
	float mShadowAtlasHeight;

	struct CameraDirection
	{
		glm::vec3 mCenter;
		glm::vec3 mUp;
	};

	CameraDirection mCameraDirs[NUM_LAYERS] =
	{
		{ glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
		{ glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
		{ glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,   0.0f,  1.0f) },
		{ glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,   0.0f, -1.0f) },
		{ glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
		{ glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
	};

	glm::vec3 mLightPos = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 mLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
};

DECLARE_MAIN(point_shadows)