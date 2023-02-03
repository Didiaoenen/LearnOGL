
#include <LearnOGLApp.h>
#include <LearnOGLTools.h>
#include <LearnOGLCommand.h>
#include <LearnOGLMaterial.h>
#include <LearnOGLDepthFBO.h>

class shadow_mapping_depth : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{
		mPersInfo.fov = 60.0f;
		mPersInfo.width = info.windowWidth;
		mPersInfo.height = info.windowHeight;
		mPersInfo.zFar = 100.0f;
		mPersInfo.zNear = 0.1f;
		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mSimpleDepthShader = new OGL::LearnOGLShader("3.1.1.shadow_mapping_depth.vs.vert", "3.1.1.shadow_mapping_depth.fs.frag");
		mDebugDepthShader = new OGL::LearnOGLShader("3.1.1.debug_quad_depth.vs.vert", "3.1.1.debug_quad_depth.fs.frag");
	
		mSimpleDepthMaterial = new OGL::LearnOGLMaterial(mSimpleDepthShader);
		mDepthDepthMaterial = new OGL::LearnOGLMaterial(mDebugDepthShader);

		mTools = OGL::LearnOGLTools::Instance();

		mPlane = mTools->MakePlane(12.5f);
	
		mDepthFBO = new OGL::LearnOGLDepthFBO(info.windowWidth, info.windowHeight);
	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		RenderShadowPass();
	}

	void RenderShadowPass()
	{

	}

	virtual void ShutDown() override
	{
		
	}

private:
	OGL::LearnOGLMaterial* mSimpleDepthMaterial;
	OGL::LearnOGLMaterial* mDepthDepthMaterial;

	OGL::LearnOGLShader* mSimpleDepthShader;
	OGL::LearnOGLShader* mDebugDepthShader;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLDepthFBO* mDepthFBO;
};

DECLARE_MAIN(shadow_mapping_depth)