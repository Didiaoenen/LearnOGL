#pragma once

#include "LearnOGLMesh.h"
#include "LearnOGLMaterial.h"

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
		~LearnOGLModel();

		void Draw();

	public:
		std::string mPath;
		
		std::vector<LearnOGLMesh> mMeshs;
	
		std::vector<LearnOGLMaterial> mMaterials;

	private:
		void LoadModel();

		void ProcessNode(aiNode* node, const aiScene* scene);

		LearnOGLMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}

