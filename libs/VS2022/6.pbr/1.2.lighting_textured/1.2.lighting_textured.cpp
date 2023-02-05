
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLMaterial.h>

#include <vector>

#include "pbr_material.h"

class lighting_textured : public OGL::LearnOGLApp
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

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 18.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand();

		mShader = new OGL::LearnOGLShader("1.1.pbr.vs.vert", "1.1.pbr.fs.frag");

		mMaterial = new pbr_material(mShader);

		mTools = new OGL::LearnOGLTools();
		mSphere = mTools->MakeSphere(1.0f, 52, 26);
		mSphere.mMaterial = mMaterial;
	}

	virtual void Update(double dt) override
	{

	}

	virtual void Input() override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mCommand->SetViewport(0, 0, info.windowWidth, info.windowHeight);

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mShader->Use();
		mShader->SetMat4("projection", pipeline.GetCameraProjection());
		mShader->SetMat4("view", pipeline.GetCameraView());
		mShader->SetVec3("camPos", mCamera->mPosition);

		for (uint32_t i = 0; i < nrRows; i++)
		{
			mShader->SetFloat("metallic", (float)i / (float)nrRows);
			for (uint32_t j = 0; j < nrColumns; j++)
			{
				mShader->SetFloat("roughness", glm::clamp((float)j / (float)nrColumns, 0.05f, 1.0f));

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
			//newPos = mLightPositions[i];
			mShader->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
			mShader->SetVec3("lightColors[" + std::to_string(i) + "]", mLightColors[i]);

			pipeline.SetPos(newPos.x, newPos.y, newPos.z);
			pipeline.SetRotate(0.0f, 0.0f, 0.0f);
			pipeline.SetScale(0.5f, 0.5f, 0.5f);
			mSphere.SetTransform(pipeline.GetTransform());
			mSphere.Draw();
		}
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLCommand* mCommand;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLTriangleBatch mSphere;

	pbr_material* mMaterial;

	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	uint32_t nrRows = 7;
	uint32_t nrColumns = 7;
	float spacing = 2.5f;
};

DECLARE_MAIN(lighting_textured)