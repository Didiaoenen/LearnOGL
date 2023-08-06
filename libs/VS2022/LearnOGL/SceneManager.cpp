#include "SceneManager.h"

#include <memory>
#include <iostream>
#include <functional>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "CBuffer.h"

using namespace OGL;
using namespace std;

bool SceneManager::Initialize()
{
    return true;
}

void SceneManager::Finalize()
{
}

void SceneManager::Tick()
{
}

bool SceneManager::LoadScene(const string& sceneName)
{
	if (sceneName.length() > 0)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(sceneName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "Error::Assimp: " << importer.GetErrorString() << std::endl;
			return false;
		}

		shared_ptr<Scene> scenePtr = make_shared<Scene>();
		mScenes.push(scenePtr);

		//
		for (size_t i = 0; i < scene->mNumLights; i++)
		{
			auto light = scene->mLights[i];
			scenePtr->mLights.emplace(light->mName.C_Str(), make_shared<SceneObjectLight>(*light));
		}

		//
		for (size_t i = 0; i < scene->mNumCameras; i++)
		{
			auto camera = scene->mCameras[i];
			scenePtr->mCameras.emplace(camera->mName.C_Str(), make_shared<SceneObjectCamera>(*camera));
		}

		function<void(const aiScene* scene, aiNode* node)> _ProcessNode;
		function<shared_ptr<SceneObjectGeometry>(const aiScene* scene, aiMesh* mesh)> _ProcessMesh;

		_ProcessMesh = [&](const aiScene* scene, aiMesh* mesh) -> shared_ptr<SceneObjectGeometry> 
		{
			std::vector<_Vertex> vertices;
			std::vector<uint32_t> indices;

			for (uint32_t i = 0; i < mesh->mNumVertices; i++)
			{
				_Vertex vertex;

				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;

				if (mesh->HasNormals())
				{
					vertex.normal.x = mesh->mNormals[i].x;
					vertex.normal.y = mesh->mNormals[i].y;
					vertex.normal.z = mesh->mNormals[i].z;
				}
				if (mesh->mTextureCoords[0])
				{
					glm::vec2 vec2;

					vertex.texcoord.x = mesh->mTextureCoords[0][i].x;
					vertex.texcoord.y = mesh->mTextureCoords[0][i].y;

					vertex.tangent.x = mesh->mTangents[i].x;
					vertex.tangent.y = mesh->mTangents[i].y;
					vertex.tangent.z = mesh->mTangents[i].z;

					vertex.bitangent.x = mesh->mBitangents[i].x;
					vertex.bitangent.y = mesh->mBitangents[i].y;
					vertex.bitangent.z = mesh->mBitangents[i].z;
				}
				else
				{
					vertex.texcoord = glm::vec2(0);
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

			auto meshPtr = make_shared<SceneObjectMesh>();
			meshPtr->mVertices = vertices;
			meshPtr->mIndices = indices;

			auto meshPtrs = vector<shared_ptr<SceneObjectMesh>>();
			meshPtrs.push_back(meshPtr);

			auto geometry = make_shared<SceneObjectGeometry>();
			geometry->mMeshs = meshPtrs;

			return geometry;
		};

		_ProcessNode = [&](const aiScene* scene, aiNode* node) 
		{
			for (size_t i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				scenePtr->mGeometries.emplace(mesh->mName.C_Str(), _ProcessMesh(scene, mesh));
			}

			for (size_t i = 0; i < node->mNumChildren; i++)
			{
				_ProcessNode(scene, node->mChildren[i]);
			}
		};
	}

    return true;
}

const std::shared_ptr<Scene> SceneManager::GetSceneForRendering() const
{
    return mScenes.top();
}

std::weak_ptr<BaseSceneNode> SceneManager::GetRootNode() const
{
    return mScenes.top()->mSceneGraph;
}

std::weak_ptr<SceneGeometryNode> SceneManager::GetSceneGeometryNode(const std::string& name) const
{
    return std::weak_ptr<SceneGeometryNode>();
}

std::weak_ptr<SceneObjectGeometry> SceneManager::GetSceneGeometryObject(const std::string& key) const
{
    return std::weak_ptr<SceneObjectGeometry>();
}
