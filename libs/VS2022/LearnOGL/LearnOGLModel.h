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

		virtual void SetProjection(glm::mat4 projection);
		virtual void SetCameraView(glm::mat4 cameraview);
		virtual void SetTransform(glm::mat4 transofrm);

	public:
		std::string mPath;
		
		std::vector<LearnOGLMesh*> mMeshs;
	
		std::vector<LearnOGLMaterial*> mMaterials;

		glm::mat4 mTransform;

	private:
		void LoadModel();

		void ProcessNode(aiNode* node, const aiScene* scene);

		LearnOGLMesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}

