#include "OpenGLGraphicsCommonBaseManager.h"

#include <sstream>
#include <functional>

#include <glad/glad.h>

#include "Image.h"

using namespace OGL;
using namespace std;

void OpenGLGraphicsCommonBaseManager::Present()
{
	glFlush();
}

void OpenGLGraphicsCommonBaseManager::SetPipelineState(const shared_ptr<PipelineState>& pipelineState, const Frame& frame)
{
	glUseProgram(mCurrentShader);

	switch (pipelineState->depthTest)
	{
	case DepthTest::NONE:
		glDisable(GL_DEPTH_TEST);
		break;
	default:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc((GLenum)pipelineState->depthTest);
		break;
	}

	glDepthMask(pipelineState->bWriteDepth);

	switch (pipelineState->cullFace)
	{
	case CullFace::NONE:
		glDisable(GL_CULL_FACE);
		break;
	default:
		glEnable(GL_CULL_FACE);
		glCullFace((GLenum)pipelineState->cullFace);
		break;
	}

	//
	uint32_t blockIndex = glGetUniformBlockIndex(mCurrentShader, "PerFrameConstants");
	if (blockIndex != GL_INVALID_INDEX)
	{
		int32_t blockSize;
		glGetActiveUniformBlockiv(mCurrentShader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

		assert(blockSize >= sizeof(PerFrameConstants));

		glUniformBlockBinding(mCurrentShader, blockIndex, 10);
		glBindBufferBase(GL_UNIFORM_BUFFER, 10, mUBODrawFrameConstant[frame.frameIndex]);
	}

	//
	blockIndex = glGetUniformBlockIndex(mCurrentShader, "PerBatchConstants");
	if (blockIndex != GL_INVALID_INDEX) 
	{
		int32_t blockSize;

		glGetActiveUniformBlockiv(mCurrentShader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

		assert(blockSize >= sizeof(PerBatchConstants));

		glUniformBlockBinding(mCurrentShader, blockIndex, 11);
		glBindBufferBase(GL_UNIFORM_BUFFER, 11, mUBODrawBatchConstant[frame.frameIndex]);
	}

	//
	blockIndex = glGetUniformBlockIndex(mCurrentShader, "LightInfo");
	if (blockIndex != GL_INVALID_INDEX) 
	{
		int32_t blockSize;

		glGetActiveUniformBlockiv(mCurrentShader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

		assert(blockSize >= sizeof(LightInfo));

		glUniformBlockBinding(mCurrentShader, blockIndex, 12);
		glBindBufferBase(GL_UNIFORM_BUFFER, 12, mUBOLightInfo[frame.frameIndex]);
	}

	//
	if (pipelineState->flag == DrawFlag::SHADOW) 
	{
		uint32_t blockIndex = glGetUniformBlockIndex(mCurrentShader, "ShadowMapConstants");
		if (blockIndex != GL_INVALID_INDEX)
		{
			int32_t blockSize;

			glGetActiveUniformBlockiv(mCurrentShader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

			assert(blockSize >= sizeof(ShadowMapConstants));

			glUniformBlockBinding(mCurrentShader, blockIndex, 13);
			glBindBufferBase(GL_UNIFORM_BUFFER, 13, mUBOShadowMatricesConstant[frame.frameIndex]);
		}
	}

	//
	SetShaderParameter("skyboxMap", 10);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, (GLuint)frame.skybox.handler);
}

void OpenGLGraphicsCommonBaseManager::DrawBatch(const Frame& frame)
{
	for (auto& pDbc : frame.batchContexts)
	{
		SetPerBatchConstants(*pDbc);

		const auto& dbc = dynamic_cast<OpenGLDrawBatchContext&>(*pDbc);

		//
		SetShaderParameter("diffuseMap", 0);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, dbc.material.diffuseMap.handler);

		//
		SetShaderParameter("specularMap", 1);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, dbc.material.specularMap.handler);

		//
		SetShaderParameter("ambientMap", 2);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, dbc.material.ambientMap.handler);

		//
		SetShaderParameter("emissiveMap", 3);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, dbc.material.emissiveMap.handler);

		//
		SetShaderParameter("normalMap", 3);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, dbc.material.normalMap.handler);

		//
		glBindVertexArray(dbc.vao);

		glDrawElements(dbc.mode, dbc.count, dbc.type, nullptr);
	}

	glBindVertexArray(0);
}

void OpenGLGraphicsCommonBaseManager::GenerateTexture(Texture2D& texture)
{
}

void OpenGLGraphicsCommonBaseManager::GenerateCubemapArray(TextureCubeArray& textureArray)
{
}

void OpenGLGraphicsCommonBaseManager::GenerateTextureArray(Texture2DArray& textureArray)
{
}

void OpenGLGraphicsCommonBaseManager::BeginShadowMap(const int32_t lightIndex, const TextureBase& pShadowMap, const int32_t layerIndex, const Frame& frame)
{
}

void OpenGLGraphicsCommonBaseManager::EndShadowMap(const TextureBase& pShadowMap, const int32_t layerIndex, const Frame& frame)
{
}

void OpenGLGraphicsCommonBaseManager::SetShadowMaps(const Frame& frame)
{
}

void OpenGLGraphicsCommonBaseManager::ReleaseTexture(TextureBase& texture)
{
	auto id = (GLuint)texture.handler;
	glDeleteTextures(1, &id);
}

void OpenGLGraphicsCommonBaseManager::DrawSkyBox(const Frame& frame)
{
}

void OpenGLGraphicsCommonBaseManager::GenerateTextureForWrite(Texture2D& texture)
{
}

void OpenGLGraphicsCommonBaseManager::BindTextureForWrite(Texture2D& texture, const uint32_t slotIndex)
{
}

void OpenGLGraphicsCommonBaseManager::Dispatch(const uint32_t width, const uint32_t height, const uint32_t depth)
{
}

void OpenGLGraphicsCommonBaseManager::DrawFullScreenQuad()
{
}

void OpenGLGraphicsCommonBaseManager::MSAAResolve(std::optional<std::reference_wrapper<Texture2D>> target, Texture2D& source)
{
}

void OpenGLGraphicsCommonBaseManager::EndScene()
{
	for (int i = 0; i < mFrames.size(); i++) 
	{
		auto& batchContexts = mFrames[i].batchContexts;

		for (auto& dbc : batchContexts) 
		{
			glDeleteVertexArrays(1, &dynamic_pointer_cast<OpenGLDrawBatchContext>(dbc)->vao);
		}

		batchContexts.clear();

		if (mUBODrawFrameConstant[i]) 
		{
			glDeleteBuffers(1, &mUBODrawFrameConstant[i]);
			mUBODrawFrameConstant[i] = 0;
		}

		if (mUBODrawBatchConstant[i]) 
		{
			glDeleteBuffers(1, &mUBODrawBatchConstant[i]);
			mUBODrawBatchConstant[i] = 0;
		}

		if (mUBOLightInfo[i]) 
		{
			glDeleteBuffers(1, &mUBOLightInfo[i]);
			mUBOLightInfo[i] = 0;
		}

		if (mUBOShadowMatricesConstant[i]) 
		{
			glDeleteBuffers(1, &mUBOShadowMatricesConstant[i]);
			mUBOShadowMatricesConstant[i] = 0;
		}
	}

	if (mSkyBoxDrawBatchContext.vao) 
	{
		glDeleteVertexArrays(1, &mSkyBoxDrawBatchContext.vao);
		mSkyBoxDrawBatchContext.vao = 0;
	}

	for (auto& buf : mBuffers) 
	{
		glDeleteBuffers(1, &buf);
	}
	mBuffers.clear();

	GraphicsManager::EndScene();
}

void OpenGLGraphicsCommonBaseManager::BeginFrame(Frame& frame)
{
	GraphicsManager::BeginFrame(frame);

	SetPerFrameConstants(frame.frameContext);
	SetLightInfo(frame.lightInfo);
}

void OpenGLGraphicsCommonBaseManager::EndFrame(Frame& frame)
{
	mFrameIndex = (mFrameIndex + 1) % GfxConfiguration::kMaxInFlightFrameCount;
	
	GraphicsManager::EndFrame(frame);
}

void OpenGLGraphicsCommonBaseManager::InitializeGeometries(const Scene& scene)
{
	uint32_t batchIndex = 0;

	for (const auto& it : scene.mGeometryNodes)
	{
		const auto& geometryNode = it.second.lock();
		const auto& geometry = scene.GetGeometry(geometryNode->GetSceneObjectRef());
		const auto& material = scene.GetMaterial(geometryNode->GetMaterialRef(0));
		const auto& mesh = geometry->mMeshs[0];
		
		uint32_t vao, vbo, ebo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh->mVertices.size() * sizeof(_Vertex), &mesh->mVertices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray((GLuint)_VertAttrib::Position);
		glVertexAttribPointer((GLuint)_VertAttrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)0);

		if (mesh->hasNormal)
		{
			glEnableVertexAttribArray((GLuint)_VertAttrib::Normal);
			glVertexAttribPointer((GLuint)_VertAttrib::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::normal));
		}

		if (mesh->hasVertexColors)
		{
			glEnableVertexAttribArray((GLuint)_VertAttrib::Color);
			glVertexAttribPointer((GLuint)_VertAttrib::Color, 4, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::color));
		}

		if (mesh->hasTextureCoords)
		{
			glEnableVertexAttribArray((GLuint)_VertAttrib::TexCoord);
			glVertexAttribPointer((GLuint)_VertAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::texcoord));
		}

		if (mesh->hasTangentsAndBitangents)
		{
			glEnableVertexAttribArray((GLuint)_VertAttrib::Tangent);
			glVertexAttribPointer((GLuint)_VertAttrib::Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::tangent));
		
			glEnableVertexAttribArray((GLuint)_VertAttrib::Bitangent);
			glVertexAttribPointer((GLuint)_VertAttrib::Bitangent, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::bitangent));
		}

		mBuffers.push_back(vbo);

		glGenBuffers(1, &ebo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndices.size() * sizeof(uint32_t), &mesh->mIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray((GLuint)_VertAttrib::Position);
		glVertexAttribPointer((GLuint)_VertAttrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)0);

		mBuffers.push_back(ebo);

		function<Texture2D(const string, const shared_ptr<Image>&)> uploadTexture;

		uploadTexture = [this](const string& name, const shared_ptr<Image>& image)
		{

			GLuint id;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
					
			uint32_t format, internalFormat, type;
			GetOpenGLTextureFormat(image->pixelFormat, format, internalFormat, type);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image->width, image->height, 0, format, type, image->data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			Texture2D texture;
			texture.handler = static_cast<TextureHandler>(id);
			texture.format = internalFormat;
			texture.pixelFormat = image->pixelFormat;
			texture.width = image->width;
			texture.height = image->height;

			return texture;
		};

		auto dbc = make_shared<OpenGLDrawBatchContext>();

		/*
		* 	Color mDiffuse;
			Color mSpecular;
			Color mAmbient;
			Color mEmissive;
			Normal mNormal;
		*/
		const auto& diffuse = material->mDiffuse;
		if (diffuse.ValueMap)
		{
			const auto& keyName = diffuse.ValueMap->mName;
			const auto& image = diffuse.ValueMap->GetTextureImage();
			if (image) 
			{
				dbc->material.diffuseMap = uploadTexture(keyName, image);
			}
		}

		//
		const auto& specular = material->mSpecular;
		if (specular.ValueMap) 
		{
			const auto& keyName = specular.ValueMap->mName;
			const auto& image = specular.ValueMap->GetTextureImage();
			if (image) 
			{
				dbc->material.specularMap = uploadTexture(keyName, image);
			}
		}

		//
		const auto& ambient = material->mAmbient;
		if (ambient.ValueMap) 
		{
			const auto& keyName = ambient.ValueMap->mName;
			const auto& image = ambient.ValueMap->GetTextureImage();
			if (image) 
			{
				dbc->material.ambientMap = uploadTexture(keyName, image);
			}
		}

		//
		const auto& emissive = material->mEmissive;
		if (emissive.ValueMap) 
		{
			const auto& keyName = emissive.ValueMap->mName;
			const auto& image = emissive.ValueMap->GetTextureImage();
			if (image) 
			{
				dbc->material.emissiveMap = uploadTexture(keyName, image);
			}
		}

		//
		const auto& normal = material->mNormal;
		if (normal.ValueMap) 
		{
			const auto& keyName = normal.ValueMap->mName;
			const auto& image = normal.ValueMap->GetTextureImage();
			if (image) 
			{
				dbc->material.normalMap = uploadTexture(keyName, image);
			}
		}

		glBindVertexArray(0);

		PrimitiveType primitiveType;
		if ((mesh->mPrimitiveTypes & (uint32_t)PrimitiveType::POINT) == (uint32_t)PrimitiveType::POINT)
		{
			primitiveType = PrimitiveType::POINT;
		}
		if ((mesh->mPrimitiveTypes & (uint32_t)PrimitiveType::LINE) == (uint32_t)PrimitiveType::LINE)
		{
			primitiveType = PrimitiveType::LINE;
		}
		if ((mesh->mPrimitiveTypes & (uint32_t)PrimitiveType::TRIANGLE) == (uint32_t)PrimitiveType::TRIANGLE)
		{
			primitiveType = PrimitiveType::TRIANGLE;
		}
		if ((mesh->mPrimitiveTypes & (uint32_t)PrimitiveType::POLYGON) == (uint32_t)PrimitiveType::POLYGON)
		{
			primitiveType = PrimitiveType::POLYGON;
		}

		dbc->batchIndex = batchIndex++;
		dbc->vao = vao;
		dbc->node = geometryNode;
		dbc->type = (uint32_t)primitiveType;

		for (size_t i = 0; i < GfxConfiguration::kMaxInFlightFrameCount; i++) 
		{
			mFrames[i].batchContexts.push_back(dbc);
		}
	}
}

void OpenGLGraphicsCommonBaseManager::InitializeSkyBox(const Scene& scene)
{
}

void OpenGLGraphicsCommonBaseManager::SetPerFrameConstants(const DrawFrameContext& context)
{
}

void OpenGLGraphicsCommonBaseManager::SetPerBatchConstants(const DrawBatchContext& context)
{
}

void OpenGLGraphicsCommonBaseManager::SetLightInfo(const LightInfo& lightInfo)
{
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::mat4x4& param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, &param[0][0]);

	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::mat4x4* param, const int32_t count)
{
	bool result = true;

	for (int32_t i = 0; i < count; i++) 
	{
		std::stringstream ss;
		ss << paramName << i;
		result &= SetShaderParameter(ss.str(), *(param + i));
	}

	return result;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::vec4& param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform4fv(location, 1, &param[0]);

	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::vec3& param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform3fv(location, 1, &param[0]);

	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::vec2& param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform2fv(location, 1, &param[0]);

	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const float param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform1f(location, param);

	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const int32_t param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform1i(location, param);
	
	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const uint32_t param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform1ui(location, param);

	return false;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const bool param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1) 
	{
		return false;
	}
	glUniform1f(location, param);
	
	return false;
}
