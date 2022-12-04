#pragma once

#include "LearnOGLMesh.h"
#include "LearnOGLTexture.h"
#include "LearnOGLMaterial.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace OGL
{
	enum TextureType
	{
		None = 0,
		Diffuse,
		Specular,
		Normal,
		Height,
	};

	class LearnOGLModel
	{
	public:
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

