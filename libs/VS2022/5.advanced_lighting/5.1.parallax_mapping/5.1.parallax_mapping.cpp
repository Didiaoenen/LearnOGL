
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

class parallax_mapping : public OGL::LearnOGLApp
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

		return true;
	}

	virtual void Setup() override
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

	virtual void Input() override
	{

	}

private:

};

DECLARE_MAIN(parallax_mapping)