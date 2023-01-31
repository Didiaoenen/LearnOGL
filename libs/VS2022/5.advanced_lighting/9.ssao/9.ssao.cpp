
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLModel.h>

#include <random>
#include <vector>

#include "ssao_material.h"
#include "ssao_blur_material.h"
#include "ssao_geometry_material.h"
#include "ssao_lighting_material.h"

#define QUAD_COUNT 3
#define SAMPLE_COUNT 64

class ssao : public OGL::LearnOGLApp
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

		std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
		std::default_random_engine generator;
		for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
		{
			glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
			sample = glm::normalize(sample);
			float scale = float(i) / SAMPLE_COUNT;
			scale = lerp(0.1f, 1.0f, scale * scale);
			sample *= scale;
			mSSAOKernel.push_back(sample);
		}

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand();

		mShader = new OGL::LearnOGLShader("9.ssao.vs.vert", "9.ssao.fs.frag");
		mBlurShader = new OGL::LearnOGLShader("9.ssao.vs.vert", "9.ssao_blur.fs.frag");
		mLightShader = new OGL::LearnOGLShader("9.ssao.vs.vert", "9.ssao_lighting.fs.frag");
		mGeometryShader = new OGL::LearnOGLShader("9.ssao_geometry.vs.vert", "9.ssao_geometry.fs.frag");

		mMaterial = new ssao_material(mShader);
		mBlurMaterial = new ssao_blur_material(mBlurShader);
		mLightMaterial = new ssao_lighting_material(mLightShader);
		mGeometryMaterial = new ssao_geometry_material(mGeometryShader);

		mMaterial->mCommand = mCommand;
		mBlurMaterial->mCommand = mCommand;
		mLightMaterial->mCommand = mCommand;

		mBackpack = new OGL::LearnOGLModel("../../../resources/objects/backpack/backpack.obj");
		mBackpack->mMaterial = mGeometryMaterial;

		mAttribID = mShader->GetAttribID("gPos");
		mBlurAttribID = mBlurShader->GetAttribID("ssaoInput");
		mGeometryAttribID = mGeometryShader->GetAttribID("albedoColor");

		mTools = new OGL::LearnOGLTools();
		mCube = mTools->MakeCube(1.0f);
		mCube.mMaterial = mGeometryMaterial;

		for (uint32_t i = 0; i < QUAD_COUNT; i++)
		{
			mQuad[i] = mTools->MakeQuad(1.0f);
		}

		mRandomTex = mTools->MakeRandomNoiseTex(4, 4);
	}

	virtual void Input() override
	{

	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);

		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mCommand->GetTemporaryCustomRT(mGeometryAttribID, info.windowWidth, info.windowHeight, 3, true);
		mCommand->SetRenderTarget(mGeometryAttribID);
		{
			mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			mContext->ExecuteCommand(mCommand);

			mGeometryShader->Use();
			mGeometryShader->SetMat4("projection", pipeline.GetCameraProjection());
			mGeometryShader->SetMat4("view", pipeline.GetCameraView());
			mGeometryShader->SetVec3("albedoColor", glm::vec3(0.95f));

			pipeline.SetPos(0.0f, 7.0f, 0.0f);
			pipeline.SetRotate(0.0f, 0.0f, 0.0f);
			pipeline.SetScale(7.5f, 7.5f, 7.5f);
			mCube.SetTransform(pipeline.GetTransform());

			mGeometryShader->SetInt("invertedNormal", 1);
			mCube.Draw();
			mGeometryShader->SetInt("invertedNormal", 0);

			pipeline.SetPos(0.0f, 0.5f, 0.0f);
			pipeline.SetRotate(-90.0f, 0.0f, 0.0f);
			pipeline.SetScale(1.0f, 1.0f, 1.0f);
			mBackpack->SetTransform(pipeline.GetTransform());
			mBackpack->Draw();
		}
		mCommand->ReleaseTemporaryRT(mGeometryAttribID);

		mCommand->GetTemporaryCustomRT(mAttribID, info.windowWidth, info.windowHeight);
		mCommand->SetRenderTarget(mAttribID);
		{
			mCommand->ClearRenderTarget(true, false, glm::vec4(0.0f));
			mContext->ExecuteCommand(mCommand, false);

			mShader->Use();
			for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
			{
				mShader->SetVec3("samples[" + std::to_string(i) + "]", mSSAOKernel[i]);
			}
			mShader->SetMat4("projection", pipeline.GetCameraProjection());
			
			mRandomTex->Bind(GL_TEXTURE2);

			GLuint drawArray[] = { 0, 1 };
			mQuad[0].mMaterial = mMaterial;
			mQuad[0].mMaterial->SetAttribID(mGeometryAttribID);
			mQuad[0].DrawByIndexs(drawArray, sizeof(drawArray) / sizeof(GLuint));
		}
		mCommand->ReleaseTemporaryRT(mAttribID);

		mCommand->GetTemporaryCustomRT(mBlurAttribID, info.windowWidth, info.windowHeight);
		mCommand->SetRenderTarget(mBlurAttribID);
		{
			mCommand->ClearRenderTarget(true, false, glm::vec4(0.0f));
			mContext->ExecuteCommand(mCommand, false);

			mBlurShader->Use();
			mQuad[1].mMaterial = mBlurMaterial;
			mQuad[1].mMaterial->SetAttribID(mAttribID);
			mQuad[1].DrawByIndex(0);
		}
		mCommand->ReleaseTemporaryRT(mBlurAttribID);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f));
		mContext->ExecuteCommand(mCommand, false);

		mLightShader->Use();
		mLightShader->SetVec3("viewPos", glm::vec3(0.0f));
		mLightShader->SetVec3("light.Position", pipeline.GetCameraView() * glm::vec4(lightPos, 1.0));
		mLightShader->SetVec3("light.Color", lightColor);
		mLightShader->SetFloat("light.Linear", 0.09f);
		mLightShader->SetFloat("light.Quadratic", 0.032f);

		GLuint drawArray[] = { 0, 1, 2, 3 };
		mQuad[2].mMaterial = mLightMaterial;
		mQuad[2].mMaterial->SetAttribID(mGeometryAttribID);
		mQuad[2].mMaterial->SetAttribID(mBlurAttribID);
		mQuad[2].DrawByIndexs(drawArray, sizeof(drawArray) / sizeof(GLuint));
	}

	virtual void ShutDown() override
	{

	}
	
	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLShader* mBlurShader;
	OGL::LearnOGLShader* mLightShader;
	OGL::LearnOGLShader* mGeometryShader;

	OGL::LearnOGLMaterial* mMaterial;
	OGL::LearnOGLMaterial* mBlurMaterial;
	OGL::LearnOGLMaterial* mLightMaterial;
	OGL::LearnOGLMaterial* mGeometryMaterial;

	OGL::LearnOGLTexture* mRandomTex;

	OGL::LearnOGLModel* mBackpack;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mCube;
	OGL::LearnOGLBatch mQuad[QUAD_COUNT];

	GLuint mAttribID;
	GLuint mBlurAttribID;
	GLuint mGeometryAttribID;

	std::vector<glm::vec3> mSSAOKernel;

	glm::vec3 lightPos = glm::vec3(2.0f, 4.0f, -2.0f);
	glm::vec3 lightColor = glm::vec3(0.2f, 0.2f, 0.7f);
};

DECLARE_MAIN(ssao)