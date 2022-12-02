#pragma once

#include "LearnOGLMesh.h"
#include "LearnOGLTexture.h"
#include "LearnOGLMaterial.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

class LearnOGLModel
{
public:
	LearnOGLModel(const std::string path);
	~LearnOGLModel();

	void Draw();

public:
	enum TextureType
	{
		None = 0,
		Diffuse,
		Specular,
		Normal,
		Height,
	};
	
	std::vector<LearnOGLMesh> mMeshs;
	
	std::vector<LearnOGLTexture> mTextures;
	
	std::vector<LearnOGLMaterial> mMaterials;

private:
	void ProcessNode(aiNode* node, const aiScene* scene);

	LearnOGLMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<LearnOGLTexture> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, TextureType eType);
};

