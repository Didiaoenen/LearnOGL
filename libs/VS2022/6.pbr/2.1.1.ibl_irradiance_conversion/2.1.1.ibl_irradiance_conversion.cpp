
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
		mCamera->SetCameraPos(glm::vec3(0.0f, 0.0f, 5.0f));
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand();

		mPBRShader = new OGL::LearnOGLShader("2.1.1.pbr.vs.vert", "2.1.1.pbr.fs.frag");
		mEquirectangularToCubemapShader = new OGL::LearnOGLShader("2.1.1.cubemap.vs.vert", "2.1.1.equirectangular_to_cubemap.fs.frag");
		mBackgroundShader = new OGL::LearnOGLShader("2.1.1.background.vs.vert", "2.1.1.background.fs.frag");


		mPBRMaterial = new pbr_material(mPBRShader);
		mCubemapMaterial = new cubemap_material(mEquirectangularToCubemapShader);
		mBackgroundMaterial = new background_material(mBackgroundShader);

		mCubemapMaterial->mEquirectangularTex = new OGL::LearnOGLTexture("./../../../resources/textures/hdr/newport_loft.hdr", false, false, true);

		mAttribID = mEquirectangularToCubemapShader->GetAttribID("equirectangularMap");
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

		mCommand->ClearRenderTarget(true, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		mContext->ExecuteCommand(mCommand);

		mCommand->GetTemporaryCubeMapRT(mAttribID, mapWidth, mapHeight, OGL::AttachType::COLOR, true);
		mCommand->SetReadTarget(mAttribID);
		{
			glm::mat4 shadowProj = pipeline.GetPerspectiveProjection(90.0f, mapWidth / mapHeight, 1.0f, 10.0f);


		}
		mCommand->ReleaseTemporaryRT(mAttribID);
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCommand* mCommand;
	OGL::LearnOGLShader* mPBRShader;
	OGL::LearnOGLShader* mEquirectangularToCubemapShader;
	OGL::LearnOGLShader* mBackgroundShader;

	pbr_material* mPBRMaterial;
	cubemap_material* mCubemapMaterial;
	background_material* mBackgroundMaterial;

	OGL::CameraDirection* mCameraDirs;
	
	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	uint32_t nrRows = 7;
	uint32_t nrColumns = 7;
	float spacing = 2.5f;

	uint32_t mapWidth = 1024;
	uint32_t mapHeight = 1024;

	GLuint mAttribID;
};

DECLARE_MAIN(ibl_irradiance_conversion)