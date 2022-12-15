#pragma once

#include "LearnOGLApp.h"
#include "LearnOGLMesh.h"
#include "LearnOGLMaterial.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace OGL
{
	class LearnOGLModel
	{
	public:
		LearnOGLModel();
		LearnOGLModel(const std::string path);
		virtual ~LearnOGLModel();

		virtual void Draw();

		virtual void ShadowDraw();

		virtual void SetProjection(glm::mat4 projection);
		virtual void SetCameraView(glm::mat4 cameraview);
		virtual void SetTransform(glm::mat4 transofrm);

		virtual void SetShadowProjection(glm::mat4 projection);

	public:
		std::string mPath;
		
		std::vector<LearnOGLMesh*> mMeshs;
	
		LearnOGLMaterial* mMaterials;

		LearnOGLMaterial* mShadowMaterial;

		glm::mat4 mTransform;

	private:
		void LoadModel();

		void ProcessNode(aiNode* node, const aiScene* scene);

		LearnOGLMesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}

