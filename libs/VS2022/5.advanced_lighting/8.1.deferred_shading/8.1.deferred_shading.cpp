
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLModel.h>

#include "g_buffer_material.h"
#include "deferred_shading_material.h"
#include "deferred_light_box_material.h"

#include <vector>

#define LIGHT_COUNT 32

class deferred_shading : public OGL::LearnOGLApp
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

		mObjectPositions.push_back(glm::vec3(-3.0f, -0.5f, -3.0f));
		mObjectPositions.push_back(glm::vec3(0.0f, -0.5f, -3.0f));
		mObjectPositions.push_back(glm::vec3(3.0f, -0.5f, -3.0f));
		mObjectPositions.push_back(glm::vec3(-3.0f, -0.5f, 0.0f));
		mObjectPositions.push_back(glm::vec3(0.0f, -0.5f, 0.0f));
		mObjectPositions.push_back(glm::vec3(3.0f, -0.5f, 0.0f));
		mObjectPositions.push_back(glm::vec3(-3.0f, -0.5f, 3.0f));
		mObjectPositions.push_back(glm::vec3(0.0f, -0.5f, 3.0f));
		mObjectPositions.push_back(glm::vec3(3.0f, -0.5f, 3.0f));

		srand(13);
		for (uint32_t i = 0; i < LIGHT_COUNT; i++)
		{
			float xPos = static_cast<float>(((rand() % 100) / 100.0f) * 6.0f - 3.0f);
			float yPos = static_cast<float>(((rand() % 100) / 100.0f) * 6.0f - 4.0f);
			float zPos = static_cast<float>(((rand() % 100) / 100.0f) * 6.0f - 3.0f);
			mLightPositions.push_back(glm::vec3(xPos, yPos, zPos));

			float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5f);
			float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5f);
			float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5f);
			mLightColors.push_back(glm::vec3(rColor, gColor, bColor));
		}

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand();

		mLightShader = new OGL::LearnOGLShader("8.1.deferred_light_box.vs.vert", "8.1.deferred_light_box.fs.frag");
		mDeferredShader = new OGL::LearnOGLShader("8.1.deferred_shading.vs.vert", "8.1.deferred_shading.fs.frag");
		mGShader = new OGL::LearnOGLShader("8.1.g_buffer.vs.vert", "8.1.g_buffer.fs.frag");

		mLightMaterial = new deferred_light_box_material(mLightShader);
		mDeferredMaterial = new deferred_shading_material(mDeferredShader);
		mGMaterial = new g_buffer_material(mGShader);
		mGMaterial->mDiffuseTex = new OGL::LearnOGLTexture("../../../resources/objects/backpack/diffuse.jpg", true, false, OGL::TextureType::Diffuse);
		mGMaterial->mSpecularTex = new OGL::LearnOGLTexture("../../../resources/objects/backpack/specular.jpg", true, false, OGL::TextureType::Specular);

		mDeferredMaterial->mCommand = mCommand;

		mAttribID = mDeferredShader->GetAttribID("gPos");

		mBackpack = new OGL::LearnOGLModel("../../../resources/objects/backpack/backpack.obj");
		mBackpack->mMaterial = mGMaterial;

		mTools = new OGL::LearnOGLTools();
		mCube = mTools->MakeCube(1.0f);
		mCube.mMaterial = mLightMaterial;

		mQuad = mTools->MakeQuad(1.0f);
		mQuad.mMaterial = mDeferredMaterial;
	}

	virtual void Update(double dt) override
	{

	}

	virtual void Input() override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);

		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mCommand->GetTemporaryCustomRT(mAttribID, info.windowWidth, info.windowHeight, 3, true);
		mCommand->SetRenderTarget(mAttribID);
		{
			mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			mContext->ExecuteCommand(mCommand);

			mGShader->Use();
			mGShader->SetMat4("projection", pipeline.GetCameraProjection());
			mGShader->SetMat4("view", pipeline.GetCameraView());

			for (uint32_t i = 0; i < mObjectPositions.size(); i++)
			{
				pipeline.SetPos(mObjectPositions[i].x, mObjectPositions[i].y, mObjectPositions[i].z);
				pipeline.SetRotate(0.0f, 0.0f, 0.0f);
				pipeline.SetScale(0.5f, 0.5f, 0.5f);
				mBackpack->SetTransform(pipeline.GetTransform());
				mBackpack->Draw();
			}
		}
		mCommand->ReleaseTemporaryRT(mAttribID);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mDeferredShader->Use();
		for (uint32_t i = 0; i < mLightPositions.size(); i++)
		{
			mDeferredShader->SetVec3("lights[" + std::to_string(i) + "].Position", mLightPositions[i]);
			mDeferredShader->SetVec3("lights[" + std::to_string(i) + "].Color", mLightColors[i]);
			mDeferredShader->SetFloat("lights[" + std::to_string(i) + "].Linear", 0.7f);
			mDeferredShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", 1.8f);
		}
		mDeferredShader->SetVec3("viewPos", mCamera->mPosition);
		
		GLuint drawArray[] = {0, 1, 2};
		mQuad.mMaterial->SetAttribID(mAttribID);
		mQuad.DrawByIndexs(drawArray, 3);

		//
		mCommand->SetReadTarget(mAttribID);
		mCommand->SetUnWriteTarget(mAttribID);
		mCommand->BlitDepthFBO(info.windowWidth, info.windowHeight);
		mCommand->UnBindFramebuffer();

		mLightShader->Use();
		mLightShader->SetMat4("projection", pipeline.GetCameraProjection());
		mLightShader->SetMat4("view", pipeline.GetCameraView());
		for (uint32_t i = 0; i < mLightPositions.size(); i++)
		{
			mLightShader->SetVec3("lightColor", mLightColors[i]);

			pipeline.SetPos(mLightPositions[i].x, mLightPositions[i].y, mLightPositions[i].z);
			pipeline.SetRotate(0.0f, 0.0f, 0.0f);
			pipeline.SetScale(0.125f, 0.125f, 0.125f);
			mCube.SetTransform(pipeline.GetTransform());
			mCube.Draw();
		}
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLShader* mLightShader;
	OGL::LearnOGLShader* mDeferredShader;
	OGL::LearnOGLShader* mGShader;

	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLTools* mTools;

	OGL::LearnOGLBatch mCube;
	OGL::LearnOGLBatch mQuad;
	OGL::LearnOGLModel* mBackpack;

	GLuint mAttribID;

	deferred_light_box_material* mLightMaterial;
	deferred_shading_material* mDeferredMaterial;
	g_buffer_material* mGMaterial;

	std::vector<glm::vec3> mObjectPositions;
	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;
};

DECLARE_MAIN(deferred_shading)