
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

#include "bloom_material.h"
#include "blur_material.h"
#include "final_material.h"
#include "light_material.h"

#define CUBE_COUNT 11
#define QUAD_COUNT 11

class bloom : public OGL::LearnOGLApp
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

		mLightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
		mLightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
		mLightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
		mLightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));

		mLightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
		mLightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
		mLightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
		mLightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mBloomShader = new OGL::LearnOGLShader("7.bloom.vs.vert", "7.bloom.fs.frag");
		mBlurShader1 = new OGL::LearnOGLShader("7.blur.vs.vert", "7.blur.fs.frag");
		mBlurShader2 = new OGL::LearnOGLShader("7.blur.vs.vert", "7.blur.fs.frag");
		mFinalShader = new OGL::LearnOGLShader("7.final.vs.vert", "7.final.fs.frag");
		mLightShader = new OGL::LearnOGLShader("7.bloom.vs.vert", "7.light.fs.frag");

		mBloomMaterial = new bloom_material(mBloomShader);
		mBlurMaterial1 = new blur_material(mBlurShader1);
		mBlurMaterial2 = new blur_material(mBlurShader2);
		mFinalMaterial = new final_material(mFinalShader);
		mLightMaterial = new light_material(mLightShader);

		mFinalMaterial->mCommand = mCommand;

		mTexture1 = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", false, true, OGL::TextureType::Diffuse);
		mTexture2 = new OGL::LearnOGLTexture("./../../../resources/textures/container2.png", false, true, OGL::TextureType::Diffuse);

		mSceneTexAttribID = mFinalShader->GetUniformLocation("sceneTex");
		mImageTex1AttribID = mBlurShader1->GetUniformLocation("imageTex");
		mImageTex2AttribID = mBlurShader2->GetUniformLocation("imageTex");

		mTools = new OGL::LearnOGLTools();
		for (uint32_t i = 0; i < CUBE_COUNT; i++)
		{
			mCubes[i] = mTools->MakeCube(1.0f);
			mCubes[i].mMaterial = mBloomMaterial;
		}

		for (uint32_t i = 0; i < CUBE_COUNT; i++)
		{
			mQuads[i] = mTools->MakeQuad(1.0f);
		}
	}

	virtual void Update(double dt) override
	{

	}

	virtual void Input() override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->SetViewport(0.0f, 0.0f, info.windowWidth, info.windowHeight);

		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		//mFBO1 = mCommand->GetTemporaryCustomRT(mSceneTexAttribID, info.windowWidth, info.windowHeight);
		//mCommand->SetRenderTarget(mSceneTexAttribID);
		{
			mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			mContext->ExecuteCommand(mCommand);

			mBloomShader->Use();
			mBloomShader->SetMat4("projection", pipeline.GetCameraProjection());
			mBloomShader->SetMat4("view", pipeline.GetCameraView());

			for (uint32_t i = 0; i < mLightPositions.size(); i++)
			{
				mBloomShader->SetVec3("lights[" + std::to_string(i) + "].Position", mLightPositions[i]);
				mBloomShader->SetVec3("lights[" + std::to_string(i) + "].Color", mLightColors[i]);
			}

			dynamic_cast<bloom_material*>(mCubes[0].mMaterial)->mDiffuseTex = mTexture1;
			{
				pipeline.SetPos(0.0f, -1.0f, 0.0f);
				pipeline.SetRotate(0.0f, 0.0f, 0.0f);
				pipeline.SetScale(12.5f, 0.5f, 12.5f);
				mCubes[0].SetTransform(pipeline.GetTransform());
			}
			mCubes[0].Draw();

			dynamic_cast<bloom_material*>(mCubes[1].mMaterial)->mDiffuseTex = mTexture2;
			{
				pipeline.SetPos(0.0f, 1.5f, 0.0f);
				pipeline.SetRotate(0.0f, 0.0f, 0.0f);
				pipeline.SetScale(0.5f, 0.5f, 0.5f);
				mCubes[1].SetTransform(pipeline.GetTransform());
			}
			mCubes[1].Draw();

			dynamic_cast<bloom_material*>(mCubes[2].mMaterial)->mDiffuseTex = mTexture2;
			{
				pipeline.SetPos(2.0f, 0.0f, 1.0f);
				pipeline.SetRotate(0.0f, 0.0f, 0.0f);
				pipeline.SetScale(0.5f, 0.5f, 0.5f);
				mCubes[2].SetTransform(pipeline.GetTransform());
			}
			mCubes[2].Draw();

			dynamic_cast<bloom_material*>(mCubes[3].mMaterial)->mDiffuseTex = mTexture2;
			{
				pipeline.SetPos(-1.0f, -1.0f, 2.0f);
				pipeline.SetRotate(60.0f, 0.0f, 60.0f);
				pipeline.SetScale(1.0f, 1.0f, 1.0f);
				mCubes[3].SetTransform(pipeline.GetTransform());
			}
			mCubes[3].Draw();

			dynamic_cast<bloom_material*>(mCubes[4].mMaterial)->mDiffuseTex = mTexture2;
			{
				pipeline.SetPos(0.0f, 2.7f, 4.0f);
				pipeline.SetRotate(23.0f, 0.0f, 23.0f);
				pipeline.SetScale(1.25f, 1.25f, 1.25f);
				mCubes[4].SetTransform(pipeline.GetTransform());
			}
			mCubes[4].Draw();

			dynamic_cast<bloom_material*>(mCubes[5].mMaterial)->mDiffuseTex = mTexture2;
			{
				pipeline.SetPos(-2.0f, 1.0f, -3.0f);
				pipeline.SetRotate(124.0f, 0.0f, 124.0f);
				pipeline.SetScale(1.0f, 1.0f, 1.0f);
				mCubes[5].SetTransform(pipeline.GetTransform());
			}
			mCubes[5].Draw();

			dynamic_cast<bloom_material*>(mCubes[6].mMaterial)->mDiffuseTex = mTexture2;
			{
				pipeline.SetPos(-3.0f, 0.0f, 0.0f);
				pipeline.SetRotate(0.0f, 0.0f, 0.0f);
				pipeline.SetScale(0.5f, 0.5f, 0.5f);
				mCubes[6].SetTransform(pipeline.GetTransform());
			}
			mCubes[6].Draw();

			mLightShader->Use();
			mLightShader->SetMat4("projection", pipeline.GetCameraProjection());
			mLightShader->SetMat4("view", pipeline.GetCameraView());

			for (uint32_t i = 0; i < mLightPositions.size(); i++)
			{
				mLightShader->SetVec3("lightColor", mLightColors[i]);

				dynamic_cast<bloom_material*>(mCubes[7 + i].mMaterial)->mDiffuseTex = mTexture2;
				{
					pipeline.SetPos(mLightPositions[i].x, mLightPositions[i].y, mLightPositions[i].z);
					pipeline.SetRotate(0.0f, 0.0f, 0.0f);
					pipeline.SetScale(0.25f, 0.25f, 0.25f);
					mCubes[7 + i].SetTransform(pipeline.GetTransform());
				}
				mCubes[7 + i].Draw();
			}
		}
		//mCommand->ReleaseTemporaryRT(mSceneTexAttribID);


		//uint32_t amount = 10;
		//bool horizontal = true, firstIteration = true;
		//GLuint attribs[2] = { mImageTex1AttribID, mImageTex2AttribID };
		//OGL::LearnOGLShader* shaders[2] = { mBlurShader1, mBlurShader2 };
		//OGL::LearnOGLMaterial* materials[2] = { mBlurMaterial1, mBlurMaterial2 };
		//for (uint32_t i = 0; i < amount; i++)
		//{
		//	shaders[horizontal]->Use();
		//	mFBO2 = mCommand->GetTemporaryCustomRT(attribs[horizontal], info.windowWidth, info.windowHeight);
		//	mCommand->SetRenderTarget(attribs[horizontal]);

		//	shaders[horizontal]->SetInt("horizontal", horizontal);

		//	mQuads[i].mMaterial = materials[horizontal];
		//	
		//	if (firstIteration)
		//	{
		//		mFBO1->BindForReading(GL_TEXTURE0, 1);
		//	}
		//	else
		//	{
		//		mQuads[i].Draw();
		//	}

		//	horizontal = !horizontal;
		//	firstIteration = false;
		//}
		//mCommand->ReleaseTemporaryRT(mImageTex1AttribID);
		//mCommand->ReleaseTemporaryRT(mImageTex2AttribID);

		//mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		//mContext->ExecuteCommand(mCommand);

		//mFinalShader->Use();
		//mFinalShader->SetInt("bloom", mBloom);
		//mFinalShader->SetFloat("exposure", mExposure);
		//
		//mFBO2->BindForReading(GL_TEXTURE1, 0);

		//mQuads[amount].mMaterial = mFinalMaterial;
		//mQuads[amount].Draw();
	}

	virtual void ShutDown() override
	{
		
	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mQuads[QUAD_COUNT];
	OGL::LearnOGLBatch mCubes[CUBE_COUNT];

	OGL::LearnOGLShader* mBloomShader;
	OGL::LearnOGLShader* mLightShader;
	OGL::LearnOGLShader* mBlurShader1;
	OGL::LearnOGLShader* mBlurShader2;
	OGL::LearnOGLShader* mFinalShader;

	OGL::LearnOGLTexture* mTexture1;
	OGL::LearnOGLTexture* mTexture2;

	OGL::LearnOGLFBO* mFBO1;
	OGL::LearnOGLFBO* mFBO2;

	bloom_material* mBloomMaterial;
	blur_material* mBlurMaterial1;
	blur_material* mBlurMaterial2;
	final_material* mFinalMaterial;
	light_material* mLightMaterial;

	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	GLuint mSceneTexAttribID;
	GLuint mImageTex1AttribID;
	GLuint mImageTex2AttribID;

	bool mBloom = true;
	bool mExposure = 1.0f;
};

DECLARE_MAIN(bloom)