
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLTools.h"
#include "../LearnOGL/LearnOGLCommand.h"
#include "../LearnOGL/LearnOGLPipeline.h"
#include "../LearnOGL/LearnOGLMaterial.h"

#include "point_shadow_material.h"
#include "point_shadow_depth_material.h"

#include <vector>

class point_shadows : public OGL::LearnOGLApp
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

		mOrthoInfo.left = -info.windowWidth / 200.0f;
		mOrthoInfo.right = info.windowWidth / 200.0f;
		mOrthoInfo.bottom = -info.windowHeight / 200.0f;
		mOrthoInfo.top = info.windowHeight / 200.0f;
		mOrthoInfo.zNear = -10.0f;
		mOrthoInfo.zFar = 10.0f;

		mShadowAtlasWidth = info.windowWidth * 4;
		mShadowAtlasHeight = info.windowHeight * 4;

		return true;
	}

	virtual void Setup() override
	{
		mCamera->SetCameraInfo(OGL::CameraType::Perspective, &mPersInfo);

		mCommand = new OGL::LearnOGLCommand("TestCommand");

		mShader = new OGL::LearnOGLShader("3.2.1.point_shadows.vs.vert", "3.2.1.point_shadows.fs.frag");
		mShadowShader = new OGL::LearnOGLShader("3.2.1.point_shadows_depth.vs.vert", "3.2.1.point_shadows_depth.fs.frag", "3.2.1.point_shadows_depth.gs.geom");
		
		mPlaneMaterial = new point_shadow_material(mShader);
		mPlaneMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/wood.png", OGL::TextureType::Diffuse);
		mPlaneMaterial->mCommand = mCommand;

		mCubeMaterial = new point_shadow_material(mShader);
		mCubeMaterial->mDiffuseTex = new OGL::LearnOGLTexture("./../../../resources/textures/container.jpg", OGL::TextureType::Diffuse);
		mCubeMaterial->mCommand = mCommand;

		mShadowMaterial = new point_shadow_depth_material(mShadowShader);
	
		mDepthAttribID = mShader->GetUniformLocation("depthMap");

		mTool = new OGL::LearnOGLTools();

		mPlane = mTool->MakePlane(10.0f);
		mPlane.mMaterial = mPlaneMaterial;
		mPlane.mShadowMaterial = mShadowMaterial;

		mCube = mTool->MakeCube(0.5f);
		mPlane.mMaterial = mPlaneMaterial;
		mPlane.mShadowMaterial = mShadowMaterial;
	}

	virtual void Input() override
	{

	}

	virtual void Update(double dt) override
	{

	}

	virtual void Render(OGL::LearnOGLContext* context) override
	{
		mCommand->ClearRenderTarget(true, false, glm::vec4(0.0));
		mContext->ExecuteCommand(mCommand);

		OGL::LearnOGLPipeline pipeline;

		float zFar = 25.0f;
		glm::mat4 shadowProj = pipeline.GetPerspectiveProjection(90.0f, mShadowAtlasWidth / mShadowAtlasHeight, 1.0f, zFar);
		std::vector<glm::mat4> shadowTrans;
		shadowTrans.push_back(shadowProj * pipeline.GetViewMatrix(mLightPos, mLightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	}

	virtual void ShutDown() override
	{

	}

private:
	OGL::LearnOGLTools* mTool;
	OGL::LearnOGLBatch mPlane;
	OGL::LearnOGLBatch mCube;

	OGL::LearnOGLCommand* mCommand;

	OGL::LearnOGLShader* mShader;
	OGL::LearnOGLShader* mShadowShader;

	GLuint mDepthAttribID;

	point_shadow_material* mPlaneMaterial;
	point_shadow_material* mCubeMaterial;
	point_shadow_depth_material* mShadowMaterial;

	float mShadowAtlasWidth;
	float mShadowAtlasHeight;

	glm::vec3 mLightPos = glm::vec3(0.0f);
};

DECLARE_MAIN(point_shadows)