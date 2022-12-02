#include "LearnOGLModel.h"

LearnOGLModel::LearnOGLModel(const std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error::Assimp: " << importer.GetErrorString() << std::endl;
		return;
	}

	ProcessNode(scene->mRootNode, scene);
}

LearnOGLModel::~LearnOGLModel()
{
}

void LearnOGLModel::Draw()
{
}

void LearnOGLModel::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshs.push_back(ProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

LearnOGLMesh LearnOGLModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<oglVertex> vertices;
	std::vector<UINT> indices;
	std::vector<LearnOGLTexture> textures;

	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		oglVertex vertex;
		glm::vec3 vec3;

		vec3.x = mesh->mVertices[i].x;
		vec3.y = mesh->mVertices[i].y;
		vec3.z = mesh->mVertices[i].z;
		vertex.position = vec3;

		if (mesh->HasNormals())
		{
			vec3.x = mesh->mNormals[i].x;
			vec3.y = mesh->mNormals[i].y;
			vec3.z = mesh->mNormals[i].z;
			vertex.normal = vec3;
		}
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec2;

			vec2.x = mesh->mTextureCoords[0][i].x;
			vec2.y = mesh->mTextureCoords[0][i].y;
			vertex.texcoords = vec2;

			vec3.x = mesh->mTangents[i].x;
			vec3.y = mesh->mTangents[i].y;
			vec3.z = mesh->mTangents[i].z;
			vertex.tangent = vec3;

			vec3.x = mesh->mBitangents[i].x;
			vec3.y = mesh->mBitangents[i].y;
			vec3.z = mesh->mBitangents[i].z;
			vertex.bitTangent = vec3;
		}
		else
		{
			vertex.texcoords = glm::vec2(0);
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<LearnOGLTexture> diffuseMaps = LoadMaterialTexture(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	std::vector<LearnOGLTexture> specularMaps = LoadMaterialTexture(material, aiTextureType_SPECULAR, TextureType::Specular);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	std::vector<LearnOGLTexture> normalMaps = LoadMaterialTexture(material, aiTextureType_HEIGHT, TextureType::Normal);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	std::vector<LearnOGLTexture> heightMaps = LoadMaterialTexture(material, aiTextureType_AMBIENT, TextureType::Height);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return LearnOGLMesh(vertices, indices, textures);
}

std::vector<LearnOGLTexture> LearnOGLModel::LoadMaterialTexture(aiMaterial* mat, aiTextureType type, TextureType eType)
{
	std::vector<LearnOGLTexture> textures;
	for (UINT i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (UINT j = 0; j < mTextures.size(); j++)
		{
			if (std::strcmp(mTextures[j].mPath.data(), str.C_Str()) == 0)
			{
				textures.push_back(mTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			LearnOGLTexture oglTexture = LearnOGLTexture(std::string(str.data), eType);
			textures.push_back(oglTexture);
			mTextures.push_back(oglTexture);
		}
	}
	return textures;
}
