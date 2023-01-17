
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

#include "hdr_material.h"
#include "lighting_material.h"

#include <vector>

class hdr : public OGL::LearnOGLApp
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

		mLightPositions.push_back(glm::vec3(0.0f, 0.0f, 49.5f));
		mLightPositions.push_back(glm::vec3(-1.4f, -1.9f, 9.0f));
		mLightPositions.push_back(glm::vec3(0.0f, -1.8f, 4.0f));
		mLightPositions.push_back(glm::vec3(0.8f, -1.7f, 6.0f));

		mLightColors.push_back(glm::vec3(200.0f, 200.0f, 200.0f));
		mLightColors.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
		mLightColors.push_back(glm::vec3(0.0f, 0.0f, 0.2f));
		mLightColors.push_back(glm::vec3(0.0f, 0.1f, 0.0f));

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mHDRShader = new OGL::LearnOGLShader("6.hdr.vs.vert", "6.hdr.fs.frag");
		mHDRMaterial = new hdr_material(mHDRShader);
		mHDRMaterial->mCommand = mCommand;

		mLightShader = new OGL::LearnOGLShader("6.lighting.vs.vert", "6.lighting.fs.frag");
		mLightMaterial = new lighting_material(mLightShader);
		mLightMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", false, OGL::TextureType::Diffuse);

		mHDRTexAttribID = mHDRShader->GetUniformLocation("hdrTex");

		mTools = new OGL::LearnOGLTools();
		mCube = mTools->MakeCube(1.0f);
		mCube.mMaterial = mLightMaterial;

		mQuad = mTools->MakeQuad(1.0f);
		mQuad.mMaterial = mHDRMaterial;
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

		//mCommand->GetTemporaryHDRRT(mHDRTexAttribID, info.windowWidth, info.windowHeight);
		//mCommand->SetRenderTarget(mHDRTexAttribID);
		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);

		mLightShader->Use();
		mLightShader->SetMat4("projection", pipeline.GetCameraProjection());
		mLightShader->SetMat4("view", pipeline.GetCameraView());
		mLightShader->SetBool("inverseNormal", true);

		for (uint32_t i = 0; i < mLightPositions.size(); i++)
		{
			mLightShader->SetVec3("lights[" + std::to_string(i) + "].Position", mLightPositions[i]);
			mLightShader->SetVec3("lights[" + std::to_string(i) + "].Color", mLightColors[i]);
		}
		mLightShader->SetVec3("lightColor", mLightColor);

		pipeline.SetPos(0.0f, 0.0f, 25.0f);
		pipeline.SetScale(2.5f, 2.5f, 27.5f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
		mCube.SetTransform(pipeline.GetTransform());
		mCube.Draw();

		//mCommand->ReleaseTemporaryRT(mHDRTexAttribID);

		//mCommand->ClearRenderTarget(true, true, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
		//mContext->ExecuteCommand(mCommand);

		//mHDRShader->Use();
		//mHDRShader->SetInt("hdr", mHDR);
		//mHDRShader->SetInt("exposure", mExposure);

		//mQuad.Draw();

		std::cout << "hdr: " << (mHDR ? "on" : "off") << " | exposure: " << mExposure << std::endl;
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	
	OGL::LearnOGLShader* mHDRShader;
	OGL::LearnOGLShader* mLightShader;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mCube;
	OGL::LearnOGLBatch mQuad;

	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	hdr_material* mHDRMaterial;
	lighting_material* mLightMaterial;

	GLuint mHDRTexAttribID;

	glm::vec3 mLightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	bool mHDR = true;
	float mExposure = 1.0f;
};

DECLARE_MAIN(hdr)