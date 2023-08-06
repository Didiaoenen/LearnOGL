#pragma once

#include <map>
#include <vector>
#include <memory>
#include <typeinfo> 

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GfxConfiguration.h"
#include "IGraphicsManager.h"
#include "IDispatchPass.h"
#include "IDrawPass.h"
#include "Scene.h"

using namespace std;

namespace OGL
{
class GraphicsManager : public IGraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager() override = default;

	bool Initialize() override;
	void Finalize() override;

	void Tick() override;

	void Draw() override;
	void Present() override {}

	void SetPipelineState(const std::shared_ptr<PipelineState>& pipelineState, const Frame& frame) override {}

	void DrawBatch(const Frame& frame) override {}

	void BeginPass(Frame& frame) override {}
	void EndPass(Frame& frame) override {}

	void BeginCompute() override {}
	void EndCompute() override {}

	void GenerateTexture(Texture2D& texture) override {}
		
	void ReleaseTexture(TextureBase& texture) override {}

	void GenerateCubemapArray(TextureCubeArray& textureArray) override {}

	void GenerateTextureArray(Texture2DArray& textureArray) override {}

	void CreateTextureView(Texture2D& textureView, const TextureArrayBase& textureArray, const uint32_t slice, const uint32_t mip) override {}

	void BeginShadowMap(const int32_t lightIndex, const TextureBase& pShadowMap, const int32_t layerIndex, const Frame& frame) override {}
	void EndShadowMap(const TextureBase& pShadowMap, const int32_t layerIndex, const Frame& frame) override {}

	void SetShadowMaps(const Frame& frame) override {}

	void DrawSkyBox(const Frame& frame) override {}

	void GenerateTextureForWrite(Texture2D& texture) override {}

	void BindTextureForWrite(Texture2D& texture, const uint32_t slotIndex) override {}

	void Dispatch(const uint32_t width, const uint32_t height, const uint32_t depth) override {}

	void DrawFullScreenQuad() override {}

	void MSAAResolve(optional<reference_wrapper<Texture2D>> target, Texture2D& source) override {}

protected:
	virtual void BeginScene(const Scene& scene);
	virtual void EndScene();

	virtual void BeginFrame(Frame& frame) {}
	virtual void EndFrame(Frame& frame) {}

	virtual void InitializeGeometries(const Scene& scene) {}
	virtual void InitializeSkyBox(const Scene& scene) {}

private:
	void InitConstants() {}
	void CalculateCameraMatrix();
	void CalculateLights();

	void UpdateConstants();

protected:
	uint64_t mSceneRevision{ 0 };
	uint64_t mFrameIndex{ 0 };

	vector<Frame> mFrames;
	vector<shared_ptr<IDispatchPass>> mInitPasses;
	vector<shared_ptr<IDispatchPass>> mDispatchPasses;
	vector<shared_ptr<IDrawPass>> mDrawPasses;

	map<string, MaterialTexture> mMaterialMap;

	vector<TextureBase> mTextures;
	uint32_t mCanvasWidth{ 0 };
	uint32_t mCanvasHeight{ 0 };

private:
	void CreateFrameBuffers();

private:
	bool mInitialize = false;
};
}

