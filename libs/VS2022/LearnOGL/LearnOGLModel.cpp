#include "LearnOGLModel.h"

namespace OGL
{
	LearnOGLModel::LearnOGLModel()
	{
	}

	LearnOGLModel::LearnOGLModel(const std::string path)
		:mPath(path)
	{
		LoadModel();
	}

	LearnOGLModel::~LearnOGLModel()
	{
	}

	void LearnOGLModel::Draw()
	{
		for (uint32_t i = 0; i < mMeshs.size(); i++)
		{
			mMeshs[i].Draw();
		}

		for (uint32_t i = 0; i < mMaterials.size(); i++)
		{
			mMaterials[i].Draw();
		}
	}

	void LearnOGLModel::LoadModel()
	{
		if (std::strlen(mPath.c_str()) > 0)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(mPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "Error::Assimp: " << importer.GetErrorString() << std::endl;
				return;
			}

			ProcessNode(scene->mRootNode, scene);
		}
	}

	void LearnOGLModel::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			mMeshs.push_back(ProcessMesh(mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	LearnOGLMesh LearnOGLModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<oglVertex> vertices;
		std::vector<uint32_t> indices;

		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
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
				vertex.bittangent = vec3;
			}
			else
			{
				vertex.texcoords = glm::vec2(0);
			}

			vertices.push_back(vertex);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		return LearnOGLMesh(vertices, indices);
	}
}