
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLTools.h"
#include "../LearnOGL/LearnOGLCamera.h"
#include "../LearnOGL/LearnOGLMaterial.h"

#include <iostream>

class shadow_mapping_depth : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{
		return true;
	}

	virtual void Setup() override
	{
		glEnable(GL_DEPTH_TEST);
	
		mCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));

		mSimpleDepthShader = new OGL::LearnOGLShader("3.1.1.shadow_mapping_depth.vs.vert", "3.1.1.shadow_mapping_depth.fs.frag");
		mDebugDepthShader = new OGL::LearnOGLShader("3.1.1.debug_quad_depth.vs.vert", "3.1.1.debug_quad_depth.fs.frag");
	
		mSimpleDepthMaterial = new OGL::LearnOGLMaterial(mSimpleDepthShader);
		mDepthDepthMaterial = new OGL::LearnOGLMaterial(mDebugDepthShader);

		mTools = OGL::LearnOGLTools::Instance();

		mPlane = mTools->MakePlane(12.5f);
		
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = mCamera->GetOrthographicProjection(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
		glm::mat4 view = mCamera->GetViewMatrix();
	
		

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
};

DECLARE_MAIN(shadow_mapping_depth)