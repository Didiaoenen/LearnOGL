
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLTools.h"
#include "../LearnOGL/LearnOGLPipeline.h"
#include "../LearnOGL/LearnOGLDepthFBO.h"

#include "test_material.h"
#include "shadow_material.h"
#include "debug_shadow_material.h"

#include <iostream>

class test : public OGL::LearnOGLApp
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

		mOrthoInfo.left = -1.0f;
		mOrthoInfo.right = 1.0f;
		mOrthoInfo.bottom = -1.0f;
		mOrthoInfo.top = 1.0f;
		mOrthoInfo.zNear = -10.0f;
		mOrthoInfo.zFar = 10.0f;

		return true;
	}

	virtual void Setup() override
	{
		mDepthFBO = new OGL::LearnOGLDepthFBO(info.windowWidth, info.windowHeight);

		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));
		mCamera->SetCameraInfo(mCameraType, &mPersInfo);

		mShader = new OGL::LearnOGLShader("test.vs.vert", "test.fs.frag");
		mMaterial = new test_material(mShader);
		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);

		mShadowShader = new OGL::LearnOGLShader("shadow_mapping_depth.vs.vert", "shadow_mapping_depth.fs.frag");
		mShadowMaterial = new shadow_material(mShadowShader);

		mDebugShadowShader = new OGL::LearnOGLShader("debug_quad_depth.vs.vert", "debug_quad_depth.fs.frag");
		mDebugShadowMaterial = new debug_shadow_material(mDebugShadowShader);

		mTools = OGL::LearnOGLTools::Instance();

		mPlane = mTools->MakePlane(0.5f);
		mPlane.mMaterials = mMaterial;
		mPlane.mShadowMaterial = mShadowMaterial;

		mDebugQuad = mTools->MakePlane(1.0f);
		mDebugQuad.mMaterials = mDebugShadowMaterial;

		mCube = mTools->MakeCube(0.5f);
		mCube.mMaterials = mMaterial;
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		RenderShadowPass();

		//glClear(GL_DEPTH_BUFFER_BIT);

		//RenderDebugShadowPass();

		//RenderPlanePass();
		//RenderCubePass();
	}

	void RenderShadowPass()
	{
		mDepthFBO->BindForWriting();

		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);
		pipeline.SetOrthographicInfo(mOrthoInfo);
		pipeline.SetPos(0.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);

		mPlane.SetShadowProjection(pipeline.GetOrthographicProjection() * pipeline.GetCameraView());
		mPlane.SetShadowTransform(pipeline.GetTransform());
		mPlane.ShadowDraw();

		mDepthFBO->UnbindForWriting();
	}

	void RenderDebugShadowPass()
	{
		mDebugQuad.mMaterials->mShader->Use();

		mDepthFBO->BindForReading();
		
		mDebugQuad.Draw();
	}

	void RenderPlanePass()
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);
		pipeline.SetPerspectiveInfo(mPersInfo);
		pipeline.SetPos(-1.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(0.0f, 0.0f, 0.0f);

		mPlane.SetProjection(pipeline.GetPerspectiveProjection());
		mPlane.SetCameraView(pipeline.GetCameraView());
		mPlane.SetTransform(pipeline.GetTransform());
		mPlane.Draw();
	}

	void RenderCubePass()
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);
		pipeline.SetPerspectiveInfo(mPersInfo);
		pipeline.SetPos(1.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(45.0f, 45.0f, 0.0f);

		mCube.SetProjection(pipeline.GetPerspectiveProjection());
		mCube.SetCameraView(pipeline.GetCameraView());
		mCube.SetTransform(pipeline.GetTransform());
		mCube.Draw();
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLCamera* mCamera;

	test_material* mMaterial;
	shadow_material* mShadowMaterial;
	debug_shadow_material* mDebugShadowMaterial;

	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLShader* mShadowShader;
	OGL::LearnOGLShader* mDebugShadowShader;

	OGL::LearnOGLTools* mTools;
	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLBatch mDebugQuad;
	OGL::LearnOGLBatch mCube;

	OGL::LearnOGLDepthFBO* mDepthFBO;
};

DECLARE_MAIN(test)