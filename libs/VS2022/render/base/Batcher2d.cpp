#include "Batcher2d.h"

#include "../core/Material.h"

ll::Batcher2d::Batcher2d()
{
}

ll::Batcher2d::Batcher2d(Root* root)
{
}

ll::Batcher2d::~Batcher2d()
{
}

void ll::Batcher2d::SyncMeshBuffersToNative(uint16_t accId, std::vector<UIMeshBuffer*>&& buffers)
{
}

bool ll::Batcher2d::Initialize()
{
    return false;
}

void ll::Batcher2d::Update()
{
}

void ll::Batcher2d::UploadBuffers()
{
}

void ll::Batcher2d::Reset()
{
}

void ll::Batcher2d::SyncRootNodesToNative(std::vector<Node*>&& rootNodes)
{
}

void ll::Batcher2d::ReleaseDescriptorSetCache(Texture* texture, Sampler* sampler)
{
}

ll::UIMeshBuffer* ll::Batcher2d::GetMeshBuffer(uint16_t accId, uint16_t bufferId)
{
    return nullptr;
}

ll::Device* ll::Batcher2d::GetDevice()
{
    return nullptr;
}

void ll::Batcher2d::UpdateDescriptorSet()
{
}

void ll::Batcher2d::FillBuffersAndMergeBatches()
{
}

void ll::Batcher2d::Walk(Node* node, float parentOpacity)
{
}

void ll::Batcher2d::HandlePostRender(RenderEntity* entity)
{
}

void ll::Batcher2d::HandleDrawInfo(RenderEntity* entity, RenderDrawInfo* drawInfo, Node* node)
{
}

void ll::Batcher2d::HandleComponentDraw(RenderEntity* entity, RenderDrawInfo* drawInfo, Node* node)
{
}

void ll::Batcher2d::HandleModelDraw(RenderEntity* entity, RenderDrawInfo* drawInfo)
{
}

void ll::Batcher2d::HandleMiddlewareDraw(RenderEntity* entity, RenderDrawInfo* drawInfo)
{
}

void ll::Batcher2d::HandleSubNode(RenderEntity* entity, RenderDrawInfo* drawInfo)
{
}

void ll::Batcher2d::GenerateBatch(RenderEntity* entity, RenderDrawInfo* drawInfo)
{
}

void ll::Batcher2d::GenerateBatchForMiddleware(RenderEntity* entity, RenderDrawInfo* drawInfo)
{
}

void ll::Batcher2d::ResetRenderStates()
{
}

void ll::Batcher2d::InsertMaskBatch(RenderEntity* entity)
{
}

void ll::Batcher2d::CreateClearModel()
{
}

ll::DescriptorSet* ll::Batcher2d::GetDescriptorSet(Texture* texture, Sampler* sampler, DescriptorSetLayout* dsLayout)
{
    return nullptr;
}
