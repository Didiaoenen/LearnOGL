
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLTools.h"
#include "../LearnOGL/LearnOGLPipeline.h"

#include "test_material.h"

#include <iostream>

class test : public OGL::LearnOGLApp
{
public:
	test() :
		mMaterial(nullptr),
		mCamera(nullptr),
		mShader(nullptr),
		mTools(nullptr)
	{
	}

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
		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));
		mCamera->SetCameraInfo(mCameraType, &mPersInfo);

		mShader = new OGL::LearnOGLShader("test.vs.vert", "test.fs.frag");
		mMaterial = new test_material(mShader);
		mMaterial->mDiffuseTexture = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);

		mTools = OGL::LearnOGLTools::Instance();

		mPlane = mTools->MakePlane(0.3f);
		mPlane.mMaterials.push_back(mMaterial);

		mCube = mTools->MakeCube(0.3f);
		mCube.mMaterials.push_back(mMaterial);
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		RenderPlanePass();
		RenderCubePass();
	}

	virtual void ShutDown() override
	{

	}

	void RenderPlanePass()
	{
		OGL::LearnOGLPipeline pipeline;
		pipeline.SetCamera(mCamera);
		pipeline.SetPerspectiveInfo(mPersInfo);
		pipeline.SetPos(-1.0f, 0.0f, 0.0f);
		pipeline.SetScale(1.0f, 1.0f, 1.0f);
		pipeline.SetRotate(45.0f, 45.0f, 0.0f);

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

private:
	test_material* mMaterial;

	OGL::LearnOGLCamera* mCamera;
	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLTools* mTools;

	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLBatch mCube;
};

DECLARE_MAIN(test)