#include "OpenGLGraphicsCommonBaseManager.h"

#include <sstream>
#include <functional>

#include <glad/glad.h>

#include "Image.h"
#include "CBuffer.h"
#include "OpenGLPipelineStateCommonBaseManager.h"

#include "LearnOGLTools.h"

#include "OGL_Entity.h"
#include "OGL_MeshRenderer.h"

using namespace OGL;

void OpenGLGraphicsCommonBaseManager::Present()
{
	glFlush();
}

void OpenGLGraphicsCommonBaseManager::SetPipelineState(const shared_ptr<PipelineState>& pipelineState, const Frame& frame)
{
	auto pPipelineState = dynamic_pointer_cast<const OpenGLPipelineState>(pipelineState);
	mCurrentShader = pPipelineState->shaderProgram;
	glUseProgram(mCurrentShader);

	SetShaderParameter("view", frame.frameContext.viewMatrix);
	SetShaderParameter("projection", frame.frameContext.projectionMatrix);

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

	//glDepthMask(pipelineState->bWriteDepth);

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
	/*uint32_t blockIndex = glGetUniformBlockIndex(mCurrentShader, "PerFrameConstants");
	if (blockIndex != GL_INVALID_INDEX)
	{
		int32_t blockSize;
		glGetActiveUniformBlockiv(mCurrentShader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

		assert(blockSize >= sizeof(PerFrameConstants));

		glUniformBlockBinding(mCurrentShader, blockIndex, 10);
		glBindBufferBase(GL_UNIFORM_BUFFER, 10, mUBODrawFrameConstant[frame.frameIndex]);
	}*/

	//
	uint32_t blockIndex = glGetUniformBlockIndex(mCurrentShader, "PerBatchConstants");
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
	/*if (pipelineState->flag == DrawFlag::SHADOW) 
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
	}*/

	//
	//SetShaderParameter("skyboxMap", 10);
	//glActiveTexture(GL_TEXTURE10);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, (GLuint)frame.skybox.handler);
}

void OpenGLGraphicsCommonBaseManager::DrawBatch(const Frame& frame)
{
	for (auto& pDbc : frame.batchContexts)
	{
		SetPerBatchConstants(*pDbc);

		const auto& dbc = dynamic_cast<OpenGLDrawBatchContext&>(*pDbc);

		SetShaderParameter("diffuseMap", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, dbc.material.diffuseMap.handler);

		SetShaderParameter("normalMap", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, dbc.material.normalMap.handler);

		SetShaderParameter("maskMap", 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, dbc.material.maskMap.handler);

		//
		glBindVertexArray(dbc.vao);
		glDrawElements(dbc.mode, dbc.count, dbc.type, 0);
	}

	glBindVertexArray(0);
}

void OpenGLGraphicsCommonBaseManager::GenerateTexture(Texture2D& texture)
{
	GLenum format, internalFormat, type;
	GetOpenGLTextureFormat(texture.pixelFormat, format, internalFormat, type);

	uint32_t id;
	glGenTextures(1, &id);
	if (texture.samples > 1) 
	{
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id);
		glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, texture.samples, internalFormat, texture.width, texture.height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	}
	else 
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture.width, texture.height, 0, format, type, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	texture.handler = static_cast<TextureHandler>(id);
	texture.format = static_cast<TextureHandler>(internalFormat);
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

	for (const auto& [_, oglEntity] : scene.mEntitys)
	{
		if (!oglEntity->HasComponent<OGL_MeshRenderer>())
		{
			continue;
		}

		const auto& oglMeshRenderer = oglEntity->GetComponent<OGL_MeshRenderer>();
		for (size_t i = 0; i < oglMeshRenderer.mMeshs.size(); i++)
		{
			const auto& oglMesh = oglMeshRenderer.mMeshs[i];
			const auto& it = oglMeshRenderer.mMaterials.find(oglMesh->mName);
			if (it != oglMeshRenderer.mMaterials.end())
			{
				const auto& [_, oglMaerial] = *it;

				uint32_t vao, vbo, ebo;
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);

				glGenBuffers(1, &vbo);

				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, oglMesh->mVertices.size() * sizeof(_Vertex), &oglMesh->mVertices[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray((GLuint)_VertAttrib::Position);
				glVertexAttribPointer((GLuint)_VertAttrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)0);

				if (oglMesh->hasNormal)
				{
					glEnableVertexAttribArray((GLuint)_VertAttrib::Normal);
					glVertexAttribPointer((GLuint)_VertAttrib::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::normal));
				}

				if (oglMesh->hasTextureCoords)
				{
					glEnableVertexAttribArray((GLuint)_VertAttrib::TexCoord);
					glVertexAttribPointer((GLuint)_VertAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::texcoord));
				}

				if (oglMesh->hasTangentsAndBitangents)
				{
					glEnableVertexAttribArray((GLuint)_VertAttrib::Tangent);
					glVertexAttribPointer((GLuint)_VertAttrib::Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::tangent));
				
					glEnableVertexAttribArray((GLuint)_VertAttrib::Bitangent);
					glVertexAttribPointer((GLuint)_VertAttrib::Bitangent, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), (void*)offsetof(_Vertex, _Vertex::bitangent));
				}

				mBuffers.push_back(vbo);

				glGenBuffers(1, &ebo);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, oglMesh->mIndices.size() * sizeof(uint32_t), &oglMesh->mIndices[0], GL_STATIC_DRAW);

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

				//const auto& diffuse = oglMaerial->mDiffuseMap;
				//if (diffuse.ValueMap)
				//{
				//	const auto& keyName = diffuse.ValueMap->mName;
				//	const auto& image = diffuse.ValueMap->GetTextureImage();
				//	if (image) 
				//	{
				//		dbc->material.diffuseMap = uploadTexture(keyName, image);
				//	}
				//}

				//const auto& normal = material->mNormal;
				//if (normal.ValueMap) 
				//{
				//	const auto& keyName = normal.ValueMap->mName;
				//	const auto& image = normal.ValueMap->GetTextureImage();
				//	if (image) 
				//	{
				//		dbc->material.normalMap = uploadTexture(keyName, image);
				//	}
				//}

				//const auto& mask = material->mMask;
				//if (mask.ValueMap)
				//{
				//	const auto& keyName = mask.ValueMap->mName;
				//	const auto& image = mask.ValueMap->GetTextureImage();
				//	if (image)
				//	{
				//		dbc->material.maskMap = uploadTexture(keyName, image);
				//	}
				//}

				glBindVertexArray(0);

				GLenum model = 0;
				if ((oglMesh->mPrimitiveTypes & (uint32_t)PrimitiveType::POINT))
				{
					model = GL_POINT;
				}
				if ((oglMesh->mPrimitiveTypes & (uint32_t)PrimitiveType::LINE))
				{
					model = GL_LINE;
				}
				if ((oglMesh->mPrimitiveTypes & (uint32_t)PrimitiveType::TRIANGLE))
				{
					model = GL_TRIANGLES;
				}
				if ((oglMesh->mPrimitiveTypes & (uint32_t)PrimitiveType::POLYGON))
				{
					model = GL_TRIANGLES;
				}

				dbc->batchIndex = batchIndex++;
				dbc->vao = vao;
				dbc->mode = (uint32_t)model;
				dbc->type = (uint32_t)GL_UNSIGNED_INT;
				dbc->count = oglMesh->mIndices.size();

				for (size_t i = 0; i < GfxConfiguration::kMaxInFlightFrameCount; i++) 
				{
					mFrames[i].batchContexts.push_back(dbc);
				}
			}

		}
	}
}

void OpenGLGraphicsCommonBaseManager::InitializeSkyBox(const Scene& scene)
{
}

void OpenGLGraphicsCommonBaseManager::SetPerFrameConstants(const DrawFrameContext& context)
{
	//if (!mUBODrawFrameConstant[mFrameIndex]) 
	//{
	//	glGenBuffers(1, &mUBODrawFrameConstant[mFrameIndex]);
	//}

	//glBindBuffer(GL_UNIFORM_BUFFER, mUBODrawFrameConstant[mFrameIndex]);

	//auto constants = static_cast<PerFrameConstants>(context);

	//glBufferData(GL_UNIFORM_BUFFER, kSizePerFrameConstantBuffer, &constants, GL_DYNAMIC_DRAW);

	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLGraphicsCommonBaseManager::SetPerBatchConstants(const DrawBatchContext& context)
{
	if (!mUBODrawBatchConstant[mFrameIndex]) 
	{
		glGenBuffers(1, &mUBODrawBatchConstant[mFrameIndex]);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, mUBODrawBatchConstant[mFrameIndex]);

	const auto& constant = static_cast<const PerBatchConstants&>(context);

	glBufferData(GL_UNIFORM_BUFFER, kSizePerBatchConstantBuffer, &constant, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLGraphicsCommonBaseManager::SetLightInfo(const LightInfo& lightInfo)
{
	if (!mUBOLightInfo[mFrameIndex]) 
	{
		glGenBuffers(1, &mUBOLightInfo[mFrameIndex]);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, mUBOLightInfo[mFrameIndex]);

	glBufferData(GL_UNIFORM_BUFFER, kSizeLightInfo, &lightInfo, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::mat4& param)
{
	unsigned int location = glGetUniformLocation(mCurrentShader, paramName.c_str());
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, &param[0][0]);

	return true;
}

bool OpenGLGraphicsCommonBaseManager::SetShaderParameter(const std::string& paramName, const glm::mat4* param, const int32_t count)
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


