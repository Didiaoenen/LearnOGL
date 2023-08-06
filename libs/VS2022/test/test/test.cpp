//
//#include <LearnOGLApp.h>
//#include <LearnOGLTools.h>
//#include <LearnOGLPipeline.h>
//#include <LearnOGLDepthFBO.h>
//
//#include "test_material.h"
//#include "shadow_material.h"
//#include "debug_shadow_material.h"
//
//class test : public OGL::LearnOGLApp
//{
//public:
//
//	virtual bool Init() override
//	{
//		OGL::LearnOGLApp::Init();
//
//		mPersInfo.fov = 60.0f;
//		mPersInfo.width = info.windowWidth;
//		mPersInfo.height = info.windowHeight;
//		mPersInfo.zFar = 100.0f;
//		mPersInfo.zNear = 0.1f;
//
//		mOrthoInfo.left = -mShadowWidth / 2;
//		mOrthoInfo.right = mShadowWidth / 2;
//		mOrthoInfo.bottom = -mShadowHeight / 2;
//		mOrthoInfo.top = mShadowHeight / 2;
//		mOrthoInfo.zNear = -10.0f;
//		mOrthoInfo.zFar = 10.0f;
//
//		return true;
//	}
//
//	virtual void Setup() override
//	{
//		mCommand = new OGL::LearnOGLCommand("TestCommand");
//
//		mShader = new OGL::LearnOGLShader("test.vs.vert", "test.fs.frag");
//		mMaterial = new test_material(mShader);
//		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);
//
//		mBoxMaterial = new test_material(mShader);
//		mBoxMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("./../../../resources/textures/container.jpg", OGL::TextureType::Diffuse);
//
//		mShadowShader = new OGL::LearnOGLShader("shadow_mapping_depth.vs.vert", "shadow_mapping_depth.fs.frag");
//		mShadowMaterial = new shadow_material(mShadowShader);
//
//		mDebugShadowShader = new OGL::LearnOGLShader("debug_quad_depth.vs.vert", "debug_quad_depth.fs.frag");
//		mDebugShadowMaterial = new debug_shadow_material(mDebugShadowShader);
//		mDebugShadowMaterial->mCommand = mCommand;
//
//		mDepthAttribID = mDebugShadowShader->GetUniformLocation("depthMap");
//
//		mTools = OGL::LearnOGLTools::Instance();
//
//		mPlane = mTools->MakePlane(3.0f);
//		mPlane.mMaterial = mMaterial;
//
//		mCube = mTools->MakeCube(0.5f);
//		mCube.mMaterial = mBoxMaterial;
//
//		mShadowPlane = mTools->MakePlane(1.0f);
//		mShadowPlane.mShadowMaterial = mShadowMaterial;
//
//		mShadowCube = mTools->MakeCube(1.0f);
//		mShadowCube.mShadowMaterial = mShadowMaterial;
//
//		mDebugQuad = mTools->MakeQuad(1.0f);
//		mDebugQuad.mMaterial = mDebugShadowMaterial;
//
//		//mContext->AddRenderer(nullptr);
//	}
//
//	virtual void Update(double dt) override
//	{
//	}
//
//	virtual void Render(OGL::LearnOGLContext* context) override
//	{
//		RenderShadow();
//	}
//
//	void RenderShadow()
//	{
//		mCommand->GetTemporaryRT(mDepthAttribID, info.windowWidth, info.windowHeight);
//		mCommand->SetRenderTarget(mDepthAttribID);
//		mCommand->ClearRenderTarget(true, false, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//		mContext->ExecuteCommand(mCommand);
//
//		OGL::LearnOGLPipeline pipeline;
//
//		RenderShadowPass(pipeline);
//
//		mCommand->ReleaseTemporaryRT(mDepthAttribID);
//
//		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//		mContext->ExecuteCommand(mCommand);
//
//		RenderDebugShadowPass(pipeline);
//	}
//
//	void RenderShadowPass(OGL::LearnOGLPipeline pipeline)
//	{
//		mCamera->SetCameraInfo(OGL::CameraType::Orthographic, &mOrthoInfo);
//
//		pipeline.SetCamera(mCamera);
//
//		pipeline.SetPos(-2.0f, 0.0f, 0.0f);
//		pipeline.SetScale(1.0f, 1.0f, 1.0f);
//		pipeline.SetRotate(30.0f, 0.0f, 0.0f);
//		mShadowPlane.SetShadowProjection(pipeline.GetCameraProjection() * pipeline.GetCameraView());
//		mShadowPlane.SetShadowTransform(pipeline.GetTransform());
//		mShadowPlane.ShadowDraw();
//
//		pipeline.SetPos(2.0f, 0.0f, 0.0f);
//		pipeline.SetScale(1.0f, 1.0f, 1.0f);
//		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
//		mShadowCube.SetShadowProjection(pipeline.GetCameraProjection() * pipeline.GetCameraView());
//		mShadowCube.SetShadowTransform(pipeline.GetTransform());
//		mShadowCube.ShadowDraw();
//	}
//
//	void RenderDebugShadowPass(OGL::LearnOGLPipeline pipeline)
//	{
//		mDebugQuad.Draw();
//	}
//
//	void RenderPass()
//	{
//		mCommand->ClearRenderTarget(true, true, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//		mContext->ExecuteCommand(mCommand);
//		RenderPlanePass();
//		RenderCubePass();
//	}
//
//	void RenderPlanePass()
//	{
//		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);
//
//		OGL::LearnOGLPipeline pipeline;
//		pipeline.SetCamera(mCamera);
//		pipeline.SetPos(0.0f, -1.0f, 0.0f);
//		pipeline.SetScale(1.0f, 1.0f, 1.0f);
//		pipeline.SetRotate(0.0f, 0.0f, 0.0f);
//
//		mPlane.SetProjection(pipeline.GetCameraProjection());
//		mPlane.SetCameraView(pipeline.GetCameraView());
//		mPlane.SetTransform(pipeline.GetTransform());
//		mPlane.Draw();
//	}
//
//	void RenderCubePass()
//	{
//		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);
//
//		OGL::LearnOGLPipeline pipeline;
//		pipeline.SetCamera(mCamera);
//		pipeline.SetPos(0.0f, -0.5f, 0.0f);
//		pipeline.SetScale(1.0f, 1.0f, 1.0f);
//		pipeline.SetRotate(0.0f, 45.0f, 0.0f);
//
//		mCube.SetProjection(pipeline.GetCameraProjection());
//		mCube.SetCameraView(pipeline.GetCameraView());
//		mCube.SetTransform(pipeline.GetTransform());
//		mCube.Draw();
//	}
//
//	virtual void ShutDown() override
//	{
//
//	}
//
//private:
//	float mShadowWidth = 16.0f;
//	float mShadowHeight = 9.0f;
//	
//	test_material* mMaterial;
//	test_material* mBoxMaterial;
//	shadow_material* mShadowMaterial;
//	debug_shadow_material* mDebugShadowMaterial;
//
//	OGL::LearnOGLShader* mShader;
//	OGL::LearnOGLShader* mShadowShader;
//	OGL::LearnOGLShader* mDebugShadowShader;
//
//	OGL::LearnOGLTools* mTools;
//	OGL::LearnOGLBatch mPlane;
//	OGL::LearnOGLBatch mCube;
//
//	OGL::LearnOGLBatch mShadowPlane;
//	OGL::LearnOGLBatch mShadowCube;
//	OGL::LearnOGLBatch mDebugQuad;
//
//	OGL::LearnOGLDepthFBO* mDepthFBO;
//
//	OGL::LearnOGLCommand* mCommand;
//	OGL::LearnOGLContext* mContext;
//
//	GLuint mDepthAttribID;
//};
//
////DECLARE_MAIN(test)