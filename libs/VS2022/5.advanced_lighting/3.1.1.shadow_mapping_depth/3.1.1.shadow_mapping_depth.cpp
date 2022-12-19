
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLTools.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLMaterial.h"
#include "../LearnOGL/LearnOGLDepthFBO.h"

#include <iostream>

class shadow_mapping_depth : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{
		mCameraType = OGL::CameraType::Perspective;
		mPersInfo.fov = 45.0f;
		mPersInfo.width = info.windowWidth;
		mPersInfo.height = info.windowHeight;
		mPersInfo.zFar = 100.0f;
		mPersInfo.zNear = 0.1f;
		return true;
	}

	virtual void Setup() override
	{
		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 10.0f));
		mCamera->SetCameraInfo(mCameraType, &mPersInfo);

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
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		RenderShadowPass();
	}

	void RenderShadowPass()
	{

	}

	virtual void ShutDown() override
	{
		
	}

private:

	OGL::LearnOGLCamera* mCamera;

	OGL::LearnOGLMaterial* mSimpleDepthMaterial;
	OGL::LearnOGLMaterial* mDepthDepthMaterial;

	OGL::LearnOGLShader* mSimpleDepthShader;
	OGL::LearnOGLShader* mDebugDepthShader;

	OGL::LearnOGLTools* mTools;

	OGL::LearnOGLBatch mPlane;

	OGL::LearnOGLDepthFBO* mDepthFBO;
};

DECLARE_MAIN(shadow_mapping_depth)