// 1.1.depth_testing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"
#include "../LearnOGL/LearnOGLModel.h"
#include "../LearnOGL/LearnOGLMaterial.h"
#include "../LearnOGL/LearnOGLCamera.h"

#include <iostream>

class depth_testing : public OGL::LearnOGLApp
{
public:

	depth_testing() :
		oglShader(nullptr),
		oglDiffuseTex(nullptr),
		oglNormalTex(nullptr),
		oglRoughnessTex(nullptr),
		oglSpecularTex(nullptr),
		oglMaterial(nullptr),
		oglModel(nullptr),
		oglCamera(nullptr)
	{
	}

	virtual bool Init() override
	{
		return true;
	}

	virtual void Setup() override
	{
		oglShader = new OGL::LearnOGLShader("1.model_loading.vs.vert", "1.model_loading.fs.frag");
		oglDiffuseTex = new OGL::LearnOGLTexture("../../resources/objects/backpack/diffuse.jpg", OGL::TextureType::Diffuse);
		oglNormalTex = new OGL::LearnOGLTexture("../../resources/objects/backpack/normal.png", OGL::TextureType::Normal);
		oglRoughnessTex = new OGL::LearnOGLTexture("../../resources/objects/backpack/roughness.jpg", OGL::TextureType::Roughness);
		oglSpecularTex = new OGL::LearnOGLTexture("../../resources/objects/backpack/specular.jpg", OGL::TextureType::Specular);
	
		oglMaterial = new OGL::LearnOGLMaterial(oglShader);
		oglMaterial->mDiffuseTexture = oglDiffuseTex;
		oglMaterial->mNormalTexture = oglNormalTex;
		oglMaterial->mRoughnessTexture = oglRoughnessTex;
		oglMaterial->mSpecularTexture = oglSpecularTex;
		
		oglModel = new OGL::LearnOGLModel("../../resources/objects/backpack/backpack.obj");
		oglModel->mMaterials.push_back(*oglMaterial);

		oglCamera = new OGL::LearnOGLCamera(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(oglCamera->mZoom), (float)info.windowWidth / (float)info.windowHeight, 0.1f, 100.0f);
		glm::mat4 view = oglCamera->GetViewMatrix();


		for (uint32_t i = 0; i < oglModel->mMaterials.size(); i++)
		{
			oglModel->mMaterials[i].mShader->SetMat4("projection", projection);
			oglModel->mMaterials[i].mShader->SetMat4("view", view);
		}

		OGL::oglTransform transform;
		transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
		transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
		transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		oglModel->SetTransform(transform);

		oglModel->Draw();
	}

private:
	OGL::LearnOGLShader* oglShader;
	OGL::LearnOGLTexture* oglDiffuseTex;
	OGL::LearnOGLTexture* oglNormalTex;
	OGL::LearnOGLTexture* oglRoughnessTex;
	OGL::LearnOGLTexture* oglSpecularTex;
	OGL::LearnOGLMaterial* oglMaterial;
	OGL::LearnOGLModel* oglModel;
	OGL::LearnOGLCamera* oglCamera;
};

DECLARE_MAIN(depth_testing)