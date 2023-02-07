﻿
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLMaterial.h>

#include "pbr_material.h"
#include "cubemap_material.h"
#include "background_material.h"

class ibl_irradiance_conversion : public OGL::LearnOGLApp
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

		mLightPositions.push_back(glm::vec3(-10.0f,  10.0f, 10.0f));
		mLightPositions.push_back(glm::vec3( 10.0f,  10.0f, 10.0f));
		mLightPositions.push_back(glm::vec3(-10.0f, -10.0f, 10.0f));
		mLightPositions.push_back(glm::vec3( 10.0f, -10.0f, 10.0f));

		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));

		mCameraDirs = new OGL::CameraDirection[NUM_LAYERS]
		{
			{ glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
			{ glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
			{ glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,   0.0f,  1.0f) },
			{ glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,   0.0f, -1.0f) },
			{ glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
			{ glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
		};

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand();

		mPBRShader = new OGL::LearnOGLShader("2.1.1.pbr.vs.vert", "2.1.1.pbr.fs.frag");
		mEquirectangularToCubemapShader = new OGL::LearnOGLShader("2.1.1.cubemap.vs.vert", "2.1.1.equirectangular_to_cubemap.fs.frag");
		mBackgroundShader = new OGL::LearnOGLShader("2.1.1.background.vs.vert", "2.1.1.background.fs.frag");


		mPBRMaterial = new pbr_material(mPBRShader);
		mCubemapMaterial = new cubemap_material(mEquirectangularToCubemapShader);
		mBackgroundMaterial = new background_material(mBackgroundShader);

		mBackgroundMaterial->mCommand = mCommand;

		mCubemapMaterial->mEquirectangularTex = new OGL::LearnOGLTexture("./../../../resources/textures/hdr/newport_loft.hdr", true, false, false, true);

		mAttribID = mEquirectangularToCubemapShader->GetAttribID("equirectangularTex");

		mTools = new OGL::LearnOGLTools();
		mCube = mTools->MakeCube(1.0);

		mSphere = mTools->MakeSphere(1.0, 52, 26);
		mSphere.mMaterial = mPBRMaterial;
	}

	virtual void Input() override
	{

	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mCommand->SetViewport(0, 0, mapWidth, mapHeight);

		mCommand->SetDepthFunc(OGL::DepthCompOpt::LEQUAL);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
		mContext->ExecuteCommand(mCommand);

		mCommand->GetTemporaryCubeMapRT(mAttribID, mapWidth, mapHeight, OGL::AttachType::COLOR, true);
		mCommand->SetRenderTarget(mAttribID);
		{
			glm::mat4 captureProj = pipeline.GetPerspectiveProjection(90.0f, mapWidth / mapHeight, 0.1f, 10.0f);

			mEquirectangularToCubemapShader->Use();
			mEquirectangularToCubemapShader->SetMat4("projection", captureProj);

			for (uint32_t i = 0; i < NUM_LAYERS; i++)
			{
				glm::mat4 view = pipeline.GetViewMatrix(mEyePos, mEyePos + mCameraDirs[i].mCenter, mCameraDirs[i].mUp);
				mEquirectangularToCubemapShader->SetMat4("view", view);

				mCommand->CubemapFramebufferTex2D(mAttribID, i);

				mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
				mContext->ExecuteCommand(mCommand, false);

				mCube.mMaterial = mCubemapMaterial;
				mCube.Draw();
			}
		}
		mCommand->ReleaseTemporaryRT(mAttribID);

		mCommand->SetViewportByFramebufferSize(mWindow);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mPBRShader->Use();
		mPBRShader->SetMat4("projection", pipeline.GetCameraProjection());
		mPBRShader->SetMat4("view", pipeline.GetCameraView());
		mPBRShader->SetVec3("camPos", mCamera->mPosition);
		mPBRShader->SetVec3("albedo", 0.5f, 0.0f, 0.0f);
		mPBRShader->SetFloat("ao", 1.0f);

		for (uint32_t i = 0; i < nrRows; i++)
		{
			mPBRShader->SetFloat("metallic", (float)i / (float)nrRows);
			for (uint32_t j = 0; j < nrColumns; j++)
			{
				mPBRShader->SetFloat("roughness", glm::clamp((float)j / (float)nrColumns, 0.05f, 1.0f));

				int col = i - nrRows / 2;
				int row = j - nrColumns / 2;

				pipeline.SetPos(row * spacing, col * spacing, 0.0f);
				pipeline.SetRotate(0.0f, 0.0f, 0.0f);
				pipeline.SetScale(1.0f, 1.0f, 1.0f);
				mSphere.SetTransform(pipeline.GetTransform());
				mSphere.Draw();
			}
		}

		for (uint32_t i = 0; i < mLightPositions.size(); i++)
		{
			glm::vec3 newPos = mLightPositions[i] + glm::vec3(sin(mLastTime * 5.0) * 5.0, 0.0, 0.0);
			newPos = mLightPositions[i];
			mPBRShader->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
			mPBRShader->SetVec3("lightColors[" + std::to_string(i) + "]", mLightColors[i]);

			pipeline.SetPos(newPos.x, newPos.y, newPos.z);
			pipeline.SetRotate(0.0f, 0.0f, 0.0f);
			pipeline.SetScale(0.5f, 0.5f, 0.5f);
			mSphere.SetTransform(pipeline.GetTransform());
			mSphere.Draw();
		}

		mBackgroundShader->Use();
		mBackgroundShader->SetMat4("projection", pipeline.GetCameraProjection());
		mBackgroundShader->SetMat4("view", pipeline.GetCameraView());
		mCube.mMaterial = mBackgroundMaterial;
		mCube.mMaterial->SetAttribID(mAttribID);
		mCube.Draw();

		//mEquirectangularToCubemapShader->Use();
		//mEquirectangularToCubemapShader->SetMat4("view", pipeline.GetCameraView());
		//mCube.mMaterial = mCubemapMaterial;
		//mCube.Draw();
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLShader* mPBRShader;
	OGL::LearnOGLShader* mEquirectangularToCubemapShader;
	OGL::LearnOGLShader* mBackgroundShader;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mCube;
	OGL::LearnOGLTriangleBatch mSphere;

	pbr_material* mPBRMaterial;
	cubemap_material* mCubemapMaterial;
	background_material* mBackgroundMaterial;

	OGL::CameraDirection* mCameraDirs;
	glm::vec3 mEyePos = glm::vec3(0.0f, 0.0f, 0.0f);
	
	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	uint32_t nrRows = 7;
	uint32_t nrColumns = 7;
	float spacing = 2.5f;

	uint32_t mapWidth = 1024;
	uint32_t mapHeight = 1024;

	GLuint mAttribID;

	unsigned int envCubemap;
};

DECLARE_MAIN(ibl_irradiance_conversion)