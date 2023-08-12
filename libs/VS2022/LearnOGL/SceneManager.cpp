#include "SceneManager.h"

#include <memory>
#include <iostream>
#include <functional>

#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "CBuffer.h"
#include "AssetLoader.h"

using namespace OGL;
using namespace std;
using namespace glm;

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
		AssetLoader assetLoader;
		auto buffer = assetLoader.SyncOpenAndReadBinary(sceneName.c_str());
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFileFromMemory(buffer.GetData(), buffer.GetDataSize(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
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
			auto keyName = light->mName.C_Str();

			auto lightObject = make_shared<SceneObjectLight>();
			lightObject->mUp.x = light->mUp.x;
			lightObject->mUp.y = light->mUp.y;
			lightObject->mUp.z = light->mUp.z;

			lightObject->mSize.x = light->mSize.x;
			lightObject->mSize.y = light->mSize.y;

			lightObject->mDirection.x = light->mDirection.x;
			lightObject->mDirection.y = light->mDirection.y;
			lightObject->mDirection.z = light->mDirection.z;

			lightObject->mColorDiffuse.r = light->mColorDiffuse.r;
			lightObject->mColorDiffuse.g = light->mColorDiffuse.g;
			lightObject->mColorDiffuse.b = light->mColorDiffuse.b;

			lightObject->mColorSpecular.r = light->mColorSpecular.r;
			lightObject->mColorSpecular.g = light->mColorSpecular.g;
			lightObject->mColorSpecular.b = light->mColorSpecular.b;

			lightObject->mColorAmbient.r = light->mColorAmbient.r;
			lightObject->mColorAmbient.g = light->mColorAmbient.g;
			lightObject->mColorAmbient.b = light->mColorAmbient.b;

			lightObject->mType = (LightType)light->mType;
			lightObject->mAngleInnerCone = light->mAngleInnerCone;
			lightObject->mAngleOuterCone = light->mAngleOuterCone;
			lightObject->mAttenuationLinear = light->mAttenuationLinear;
			lightObject->mAttenuationConstant = light->mAttenuationConstant;
			lightObject->mAttenuationQuadratic = light->mAttenuationQuadratic;

			scenePtr->mLights.emplace(keyName, make_shared<SceneObjectLight>());

			auto node = make_shared<SceneLightNode>(keyName);
			node->AddSceneObjectRef(keyName);
			scenePtr->mLightNodes.emplace(keyName, node);
		}

		//
		for (size_t i = 0; i < scene->mNumCameras; i++)
		{
			auto camera = scene->mCameras[i];
			auto keyName = camera->mName.C_Str();

			auto cameraObject = make_shared<SceneObjectPerspectiveCamera>();
			cameraObject->mUp.x = camera->mUp.x;
			cameraObject->mUp.y = camera->mUp.y;
			cameraObject->mUp.z = camera->mUp.z;

			cameraObject->mLookAt.x = camera->mLookAt.x;
			cameraObject->mLookAt.y = camera->mLookAt.y;
			cameraObject->mLookAt.z = camera->mLookAt.z;

			cameraObject->mClipPlaneFar = camera->mClipPlaneFar;
			cameraObject->mClipPlaneNear = camera->mClipPlaneNear;
			cameraObject->mHorizontalFOV = camera->mHorizontalFOV;
			cameraObject->mOrthographicWidth = camera->mOrthographicWidth;

			scenePtr->mCameras.emplace(keyName, cameraObject);

			auto nodePtr = make_shared<SceneCameraNode>(keyName);
			nodePtr->AddSceneObjectRef(keyName);
			scenePtr->mCameraNodes.emplace(keyName, nodePtr);
		}

		function<void(const aiScene* scene, aiNode* node)> _ProcessNode;
		function<shared_ptr<SceneObjectMesh>(aiMesh* mesh)> _ProcessMesh;
		function<vector<shared_ptr<SceneObjectTexture>>(const aiMaterial* material, aiTextureType type)> _ProcessTexture;

		_ProcessMesh = [&](aiMesh* mesh) -> shared_ptr<SceneObjectMesh>
		{
			std::vector<_Vertex> vertices;
			std::vector<uint32_t> indices;

			auto meshPtr = make_shared<SceneObjectMesh>();

			for (uint32_t i = 0; i < mesh->mNumVertices; i++)
			{
				_Vertex vertex;

				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;

				if (mesh->HasNormals())
				{
					meshPtr->hasNormal = true;

					vertex.normal.x = mesh->mNormals[i].x;
					vertex.normal.y = mesh->mNormals[i].y;
					vertex.normal.z = mesh->mNormals[i].z;
				}

				if (mesh->HasTangentsAndBitangents())
				{
					meshPtr->hasTangentsAndBitangents = true;

					vertex.tangent.x = mesh->mTangents[i].x;
					vertex.tangent.y = mesh->mTangents[i].y;
					vertex.tangent.z = mesh->mTangents[i].z;

					vertex.bitangent.x = mesh->mBitangents[i].x;
					vertex.bitangent.y = mesh->mBitangents[i].y;
					vertex.bitangent.z = mesh->mBitangents[i].z;
				}

				//if (mesh->HasVertexColors(0))
				//{
				//	meshPtr->hasVertexColors = true;

				//	vertex.color.r = mesh->mColors[0]->r;
				//	vertex.color.g = mesh->mColors[0]->g;
				//	vertex.color.b = mesh->mColors[0]->b;
				//}

				if (mesh->HasTextureCoords(0))
				{
					meshPtr->hasTextureCoords = true;

					vertex.texcoord.x = mesh->mTextureCoords[0][i].x;
					vertex.texcoord.y = mesh->mTextureCoords[0][i].y;
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

			meshPtr->mVertices = vertices;
			meshPtr->mIndices = indices;

			meshPtr->mPrimitiveTypes = mesh->mPrimitiveTypes;

			return meshPtr;
		};

		_ProcessTexture = [&](const aiMaterial* material, aiTextureType type) -> vector<shared_ptr<SceneObjectTexture>>
		{
			vector<shared_ptr<SceneObjectTexture>> textures;

			for (GLuint i = 0; i < material->GetTextureCount(type); i++)
			{
				aiString str;
				material->GetTexture(type, i, &str);
				textures.push_back(make_shared<SceneObjectTexture>(str.C_Str()));
			}

			return textures;
		};

		_ProcessNode = [&](const aiScene* scene, aiNode* node) 
		{
			auto transform = node->mTransformation;
			auto matPtr = glm::identity<mat4>();

			matPtr[0][0] = transform.a1;
			matPtr[0][1] = transform.a2;
			matPtr[0][2] = transform.a3;
			matPtr[0][3] = transform.d1;

			matPtr[1][0] = transform.b1;
			matPtr[1][1] = transform.b2;
			matPtr[1][2] = transform.b3;
			matPtr[1][3] = transform.d2;

			matPtr[2][0] = transform.c1;
			matPtr[2][1] = transform.c2;
			matPtr[2][2] = transform.c3;
			matPtr[2][3] = transform.d3;

			matPtr[3][0] = transform.a4;
			matPtr[3][1] = transform.b4;
			matPtr[3][2] = transform.c4;
			matPtr[3][3] = transform.d4;

			auto keyName = node->mName.C_Str();
			auto sceneNode = scenePtr->GetSceneNode(keyName);
			if (sceneNode)
			{
				sceneNode->AppendTransform(keyName, make_shared<SceneObjectTransform>(matPtr));
			}
			else
			{
				auto nodePtr = make_shared<SceneGeometryNode>(keyName);
				nodePtr->AddSceneObjectRef(keyName);

				nodePtr->AppendTransform(keyName, make_shared<SceneObjectTransform>(matPtr));
				scenePtr->mGeometryNodes.emplace(keyName, nodePtr);

				auto geometry = make_shared<SceneObjectGeometry>();
				scenePtr->mGeometries.emplace(keyName, geometry);

				for (size_t i = 0; i < node->mNumMeshes; i++)
				{
					aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

					geometry->mMeshs.push_back(_ProcessMesh(mesh));

					aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				
					auto materialPtr = make_shared<SceneObjectMaterial>();

					aiString name;
					if (AI_SUCCESS == aiGetMaterialString(material, AI_MATKEY_NAME, &name))
					{
						materialPtr->mName = name.C_Str();
					}

					vector<shared_ptr<SceneObjectTexture>> diffuseMaps = _ProcessTexture(material, aiTextureType_DIFFUSE);
					vector<shared_ptr<SceneObjectTexture>> specularMaps = _ProcessTexture(material, aiTextureType_SPECULAR);
					vector<shared_ptr<SceneObjectTexture>> ambientMaps = _ProcessTexture(material, aiTextureType_AMBIENT);
					vector<shared_ptr<SceneObjectTexture>> emissiveMaps = _ProcessTexture(material, aiTextureType_EMISSIVE);
					vector<shared_ptr<SceneObjectTexture>> normalMaps = _ProcessTexture(material, aiTextureType_NORMALS);
			
					if (diffuseMaps.size() > 0)
					{
						materialPtr->mDiffuse = diffuseMaps.at(0);
					}
					if (specularMaps.size() > 0)
					{
						materialPtr->mSpecular = specularMaps.at(0);
					}
					if (ambientMaps.size() > 0)
					{
						materialPtr->mAmbient = ambientMaps.at(0);
					}
					if (emissiveMaps.size() > 0)
					{
						materialPtr->mEmissive = emissiveMaps.at(0);
					}
					if (normalMaps.size() > 0)
					{
						materialPtr->mNormal = normalMaps.at(0);
					}

					aiColor4D diffuse, specular, ambient, emission;
					if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
					{
						materialPtr->mDiffuse = Color(vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
					}
					if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular)) 
					{
						materialPtr->mSpecular = Color(vec4(specular.r, specular.g, specular.b, specular.a));
					}
					if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient))
					{
						materialPtr->mAmbient = Color(vec4(ambient.r, ambient.g, ambient.b, ambient.a));
					}
					if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emission))
					{
						materialPtr->mEmissive = Color(vec4(emission.r, emission.g, emission.b, emission.a));
					}

					ai_real diffuse_intensity, specular_hardness, specular_intensity;
					if (AI_SUCCESS == aiGetMaterialFloat(material, "$mat.blend.diffuse.intensity", 0, 0, &diffuse_intensity))
					{
						materialPtr->mDiffuseIntensity = Parameter(diffuse_intensity);
					}
					if (AI_SUCCESS == aiGetMaterialFloat(material, "$mat.blend.specular.hardness", 0, 0, &specular_hardness))
					{
						materialPtr->mSpecularPower = Parameter(specular_hardness);
					}
					if (AI_SUCCESS == aiGetMaterialFloat(material, "$mat.blend.specular.intensity", 0, 0, &specular_intensity))
					{
						materialPtr->mSpecularIntensity = Parameter(specular_intensity);
					}

					for (size_t i = 0; i < material->mNumProperties; i++)
					{
						auto property = material->mProperties[i];
						cout << property->mKey.C_Str() << " " << property->mType << endl;
					}

					nodePtr->AddMaterialRef(materialPtr->mName);

					scenePtr->mMaterials.emplace(keyName, materialPtr);
				}

				for (size_t i = 0; i < node->mNumChildren; i++)
				{
					_ProcessNode(scene, node->mChildren[i]);
				}
			}
		};

		_ProcessNode(scene, scene->mRootNode);
	}

	mSceneRevision++;

    return true;
}

const shared_ptr<Scene> SceneManager::GetSceneForRendering() const
{
    return mScenes.top();
}

std::weak_ptr<BaseSceneNode> SceneManager::GetRootNode() const
{
    return mScenes.top()->mSceneGraph;
}

weak_ptr<SceneGeometryNode> SceneManager::GetSceneGeometryNode(const string& name) const
{
    return weak_ptr<SceneGeometryNode>();
}

weak_ptr<SceneObjectGeometry> SceneManager::GetSceneGeometryObject(const string& key) const
{
    return weak_ptr<SceneObjectGeometry>();
}
