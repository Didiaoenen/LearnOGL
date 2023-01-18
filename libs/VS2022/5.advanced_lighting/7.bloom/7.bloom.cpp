
#include <LearnOGLApp.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLPipeline.h>
#include <LearnOGLTools.h>

#include "bloom_material.h"
#include "blur_material.h"
#include "final_material.h"
#include "light_material.h"

class bloom : public OGL::LearnOGLApp
{
public:

	virtual bool Init() override
	{
		OGL::LearnOGLApp::Init();



		return true;
	}

	virtual void Setup() override
	{
		mBloomShader = new OGL::LearnOGLShader("7.bloom.vs.vert", "7.bloom.fs.frag");
		mBlurShader = new OGL::LearnOGLShader("7.blur.vs.vert", "7.blur.fs.frag");
		mFinalShader = new OGL::LearnOGLShader("7.final.vs.vert", "7.final.fs.frag");
		mLightShader = new OGL::LearnOGLShader("7.bloom.vs.vert", "7.light.fs.frag");

		mBloomMaterial = new bloom_material(mBloomShader);
		

		mBlurMaterial = new blur_material(mBlurShader);
		mFinalMaterial = new final_material(mFinalShader);
		mLightMaterial = new light_material(mLightShader);


	}

	virtual void Update(double dt) override
	{

	}

	virtual void Input() override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{

	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLShader* mBloomShader;
	OGL::LearnOGLShader* mLightShader;
	OGL::LearnOGLShader* mBlurShader;
	OGL::LearnOGLShader* mFinalShader;

	bloom_material* mBloomMaterial;
	blur_material* mBlurMaterial;
	final_material* mFinalMaterial;
	light_material* mLightMaterial;

};

DECLARE_MAIN(bloom)