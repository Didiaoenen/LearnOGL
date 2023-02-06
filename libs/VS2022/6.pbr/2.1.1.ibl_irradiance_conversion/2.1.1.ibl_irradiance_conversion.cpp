
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>
#include <LearnOGLMaterial.h>

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

		OGL::CameraDirection mCameraDirs[NUM_LAYERS] =
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
	OGL::LearnOGLShader* mPBRShader;
	OGL::LearnOGLShader* mEquirectangularToCubemapShader;
	OGL::LearnOGLShader* mBackgroundShader;

	std::vector<glm::vec3> mLightPositions;
	std::vector<glm::vec3> mLightColors;

	uint32_t nrRows = 7;
	uint32_t nrColumns = 7;
	float spacing = 2.5f;
};

DECLARE_MAIN(ibl_irradiance_conversion)