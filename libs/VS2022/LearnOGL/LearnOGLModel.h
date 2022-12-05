#pragma once

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
	struct oglTransform
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;
	};

	class LearnOGLModel
	{
	public:
		LearnOGLModel();
		LearnOGLModel(const std::string path);
		~LearnOGLModel();

		void Draw();

		void SetTransform(oglTransform transofrm);

	public:
		std::string mPath;
		
		std::vector<LearnOGLMesh> mMeshs;
	
		std::vector<LearnOGLMaterial> mMaterials;

		oglTransform mTransform;

	private:
		void LoadModel();

		void ProcessNode(aiNode* node, const aiScene* scene);

		LearnOGLMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}

