
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLMaterial.h>

#include "background_material.h"
#include "brdf_material.h"
#include "equirectangular_material.h"
#include "irradiance_material.h"
#include "pbr_material.h"
#include "prefilter_material.h"

class ibl_specular : public OGL::LearnOGLApp
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

		mLightPositions.push_back(glm::vec3(-10.0f, 10.0f, 10.0f));
		mLightPositions.push_back(glm::vec3(10.0f, 10.0f, 10.0f));
		mLightPositions.push_back(glm::vec3(-10.0f, -10.0f, 10.0f));
		mLightPositions.push_back(glm::vec3(10.0f, -10.0f, 10.0f));

		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
		mLightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));

		mCameraDirs = new OGL::CameraDirection[NUM_LAYERS]
		{
			{ glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
			{ glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
			{ glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,   0.0f,  1.0f) },
			{ glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,   0.0f, -1.0f) },
			{ glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
			{ glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f,  -1.0f,  0.0f) },
		};

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand();

		mBackgroundShader = new OGL::LearnOGLShader("2.1.2.background.vs.vert", "2.1.2.background.fs.frag");
		mPBRShader = new OGL::LearnOGLShader("2.1.2.pbr.vs.vert", "2.1.2.pbr.fs.frag");
		mEquirectangularToCubemapShader = new OGL::LearnOGLShader("2.1.2.cubemap.vs.vert", "2.1.2.equirectangular_to_cubemap.fs.frag");
		mIrradianceShader = new OGL::LearnOGLShader("2.1.2.cubemap.vs.vert", "2.1.2.irradiance_convolution.fs.frag");
		mBRDFShader = new OGL::LearnOGLShader("2.1.2.background.vs.vert", "2.1.2.background.fs.frag");
		mPrefilterShader = new OGL::LearnOGLShader("2.1.2.background.vs.vert", "2.1.2.background.fs.frag");

		mBackgroundMaterial = new background_material(mBackgroundShader);
		mPBRMaterial = new pbr_material(mPBRShader);
		mCubemapMaterial = new equirectangular_material(mEquirectangularToCubemapShader);
		mIrradianceMaterial = new irradiance_material(mIrradianceShader);
		mBRDFMaterial = new brdf_material(mBRDFShader);
		mPrefilterMaterial = new prefilter_material(mPrefilterShader);

		mPBRMaterial->mCommand = mCommand;
		mIrradianceMaterial->mCommand = mCommand;
		mBackgroundMaterial->mCommand = mCommand;

		mCubemapMaterial->mEquirectangularTex = new OGL::LearnOGLTexture("./../../../resources/textures/hdr/newport_loft.hdr", true, false, false, true);

		mEquirectangularAttribID = mEquirectangularToCubemapShader->GetAttribID("equirectangularTex");
		mIrradianceEnvAttribID = mIrradianceShader->GetAttribID("environmentTex");
		mPrefilterEnvAttribID = mIrradianceShader->GetAttribID("environmentTex");

		mTools = new OGL::LearnOGLTools();
		mCube = mTools->MakeCube(1.0);

		mSphere = mTools->MakeSphere(1.0, 104, 52);
		mSphere.mMaterial = mPBRMaterial;

		mCommand->SetDepthFunc(OGL::DepthCompOpt::LEQUAL);

		//
		OGL::LearnOGLPipeline pipeline;
		mCommand->SetViewport(0.0f, 0.0f, mapWidth, mapHeight);
		mCommand->GetTemporaryCubeMapRT(mEquirectangularAttribID, mapWidth, mapHeight, OGL::AttachType::COLOR, true);
		mCommand->SetRenderTarget(mEquirectangularAttribID);
		{
			glm::mat4 captureProj = pipeline.GetPerspectiveProjection(90.0f, mapWidth / mapHeight, 0.1f, 10.0f);

			mEquirectangularToCubemapShader->Use();
			mEquirectangularToCubemapShader->SetMat4("projection", captureProj);

			for (uint32_t i = 0; i < NUM_LAYERS; i++)
			{
				glm::mat4 view = pipeline.GetViewMatrix(mEyePos, mEyePos + mCameraDirs[i].mCenter, mCameraDirs[i].mUp);
				mEquirectangularToCubemapShader->SetMat4("view", view);

				mCommand->CubemapFramebufferTex2D(mEquirectangularAttribID, i);

				mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
				mContext->ExecuteCommand(mCommand, false);

				mCube.mMaterial = mCubemapMaterial;
				mCube.Draw();
			}
		}
		mCommand->ReleaseTemporaryRT(mEquirectangularAttribID);

		mCommand->SetViewport(0.0f, 0.0f, mIrradianceWidth, mIrradianceHeight);
		mCommand->GetTemporaryCubeMapRT(mIrradianceEnvAttribID, mIrradianceWidth, mIrradianceHeight, OGL::AttachType::COLOR, true);
		mCommand->SetRenderTarget(mIrradianceEnvAttribID);
		{
			glm::mat4 captureProj = pipeline.GetPerspectiveProjection(90.0f, mIrradianceWidth / mIrradianceHeight, 0.1f, 10.0f);

			mIrradianceShader->Use();
			mIrradianceShader->SetMat4("projection", captureProj);

			for (uint32_t i = 0; i < NUM_LAYERS; i++)
			{
				glm::mat4 view = pipeline.GetViewMatrix(mEyePos, mEyePos + mCameraDirs[i].mCenter, mCameraDirs[i].mUp);
				mIrradianceShader->SetMat4("view", view);

				mCommand->CubemapFramebufferTex2D(mIrradianceEnvAttribID, i);
				mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
				mContext->ExecuteCommand(mCommand, false);

				mCube.mMaterial = mIrradianceMaterial;
				mCube.mMaterial->SetAttribID(mEquirectangularAttribID);
				mCube.DrawByIndex();
			}
		}
		mCommand->ReleaseTemporaryRT(mIrradianceEnvAttribID);

		mCommand->GetTemporaryCubeMapRT(mPrefilterEnvAttribID, mIrradianceWidth, mIrradianceHeight, OGL::AttachType::COLOR, true);
		mCommand->SetRenderTarget(mPrefilterEnvAttribID);
		{
			glm::mat4 captureProj = pipeline.GetPerspectiveProjection(90.0f, mIrradianceWidth / mIrradianceHeight, 0.1f, 10.0f);

			mPrefilterShader->Use();
			mPrefilterShader->SetMat4("projection", captureProj);

			uint32_t maxMipLevels = 5;
			for (uint32_t mip = 0; mip < maxMipLevels; mip++)
			{
				auto mipWidth = (uint32_t)128 * std::pow(0.5, mip);
				auto mipHeight = (uint32_t)128 * std::pow(0.5, mip);

				float roughness = (float)mip / (maxMipLevels - 1);
				mPrefilterShader->SetFloat("roughness", roughness);
				for (uint32_t i = 0; i < NUM_LAYERS; i++)
				{
					glm::mat4 view = pipeline.GetViewMatrix(mEyePos, mEyePos + mCameraDirs[i].mCenter, mCameraDirs[i].mUp);
					mPrefilterShader->SetMat4("view", view);

					mCommand->CubemapFramebufferTex2D(mPrefilterEnvAttribID, i);
					mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
					mContext->ExecuteCommand(mCommand, false);

					mCube.mMaterial = mIrradianceMaterial;
					mCube.Draw();
				}
			}
		}
		mCommand->ReleaseTemporaryRT(mPrefilterEnvAttribID);


	}

	virtual void Input() override
	{

	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{

	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mCube;
	OGL::LearnOGLTriangleBatch mSphere;

	OGL::LearnOGLShader* mBackgroundShader;
	OGL::LearnOGLShader* mPBRShader;
	OGL::LearnOGLShader* mEquirectangularToCubemapShader;
	OGL::LearnOGLShader* mIrradianceShader;
	OGL::LearnOGLShader* mBRDFShader;
	OGL::LearnOGLShader* mPrefilterShader;

	background_material* mBackgroundMaterial;
	brdf_material* mBRDFMaterial;
	equirectangular_material* mCubemapMaterial;
	irradiance_material* mIrradianceMaterial;
	pbr_material* mPBRMaterial;
	prefilter_material* mPrefilterMaterial;

	OGL::CameraDirection* mCameraDirs;
	glm::vec3 mEyePos = glm::vec3(0.0f, 0.0f, 0.0f);

	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	uint32_t mRows = 7;
	uint32_t mColumns = 7;
	float mSpacing = 2.5f;

	uint32_t mapWidth = 1024;
	uint32_t mapHeight = 1024;

	uint32_t mIrradianceWidth = 32;
	uint32_t mIrradianceHeight = 32;

	GLuint mIrradianceEnvAttribID;
	GLuint mPrefilterEnvAttribID;
	GLuint mEquirectangularAttribID;
};