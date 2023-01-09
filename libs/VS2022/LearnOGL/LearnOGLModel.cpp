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
		mMaterial->Draw();

		mMaterial->mShader->SetMat4("model", mTransform);

		for (uint32_t i = 0; i < mMeshs.size(); i++)
		{
			mMeshs[i]->Draw();
		}
	}

	void LearnOGLModel::ShadowDraw()
	{
		mShadowMaterial->Draw();

		mShadowMaterial->mShader->SetMat4("model", mTransform);

		for (uint32_t i = 0; i < mMeshs.size(); i++)
		{
			mMeshs[i]->Draw();
		}
	}

	void LearnOGLModel::SetCameraView(glm::mat4 cameraview)
	{
		mMaterial->mShader->Use();
		mMaterial->mShader->SetMat4("view", cameraview);
	}

	void LearnOGLModel::SetProjection(glm::mat4 projection)
	{
		mMaterial->mShader->Use();
		mMaterial->mShader->SetMat4("projection", projection);
	}

	void LearnOGLModel::SetTransform(glm::mat4 transfrom)
	{
		mTransform = transfrom;
		mMaterial->mShader->Use();
		mMaterial->mShader->SetMat4("model", mTransform);
	}

	void LearnOGLModel::SetShadowProjection(glm::mat4 projection)
	{
		mShadowMaterial->mShader->Use();
		mShadowMaterial->mShader->SetMat4("vpMatrix", projection);
	}

	void LearnOGLModel::SetShadowCameraView(glm::mat4 cameraview)
	{
		mShadowMaterial->mShader->Use();
		mShadowMaterial->mShader->SetMat4("view", cameraview);
	}

	void LearnOGLModel::SetShadowTransform(glm::mat4 transfrom)
	{
		mTransform = transfrom;
		mShadowMaterial->mShader->Use();
		mShadowMaterial->mShader->SetMat4("model", mTransform);
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

	LearnOGLMesh* LearnOGLModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
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
				vertex.bitangent = vec3;
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

		return new LearnOGLMesh(vertices, indices);
	}
}