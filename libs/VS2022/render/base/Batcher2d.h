#pragma once

#include "Ptr.h"
#include "Macros.h"
#include "Def_common.h"
#include "RenderDrawInfo.h"

#include "../core/Material.h"

#include <map>
#include <vector>
#include <glm/glm.hpp>

namespace ll
{

    class Root;
    class Node;
    class Model;
    class Device;
    class Texture;
    class Sampler;
    class UIMeshBuffer;
    class RenderEntity;
    class DescriptorSet;
    
    using UIMeshBufferArray = std::vector<UIMeshBuffer*>;
    using UIMeshBufferMap = std::map<uint16_t, UIMeshBufferArray>;

class Batcher2d final
{
public:
    Batcher2d();
    explicit Batcher2d(Root* root);
    ~Batcher2d();

    void SyncMeshBuffersToNative(uint16_t accId, std::vector<UIMeshBuffer*>&& buffers);

    bool Initialize();
    void Update();
    void UploadBuffers();
    void Reset();

    void SyncRootNodesToNative(std::vector<Node*>&& rootNodes);
    void ReleaseDescriptorSetCache(Texture* texture, Sampler* sampler);

    UIMeshBuffer* GetMeshBuffer(uint16_t accId, uint16_t bufferId);
    Device* GetDevice();
    inline std::vector<Attribute>* GetDefaultAttribute() { return &_attributes; }

    void UpdateDescriptorSet();

    void FillBuffersAndMergeBatches();
    void Walk(Node* node, float parentOpacity);
    void HandlePostRender(RenderEntity* entity);
    void HandleDrawInfo(RenderEntity* entity, RenderDrawInfo* drawInfo, Node* node);
    void HandleComponentDraw(RenderEntity* entity, RenderDrawInfo* drawInfo, Node* node);
    void HandleModelDraw(RenderEntity* entity, RenderDrawInfo* drawInfo);
    void HandleMiddlewareDraw(RenderEntity* entity, RenderDrawInfo* drawInfo);
    void HandleSubNode(RenderEntity* entity, RenderDrawInfo* drawInfo);
    void GenerateBatch(RenderEntity* entity, RenderDrawInfo* drawInfo);
    void GenerateBatchForMiddleware(RenderEntity* entity, RenderDrawInfo* drawInfo);
    void ResetRenderStates();

private:
    bool _isInit = false;

    inline void FillIndexBuffers(RenderDrawInfo* drawInfo) 
    {
        //uint16_t* ib = drawInfo->getIDataBuffer();

        //UIMeshBuffer* buffer = drawInfo->getMeshBuffer();
        //uint32_t indexOffset = buffer->getIndexOffset();

        //uint16_t* indexb = drawInfo->getIbBuffer();
        //uint32_t indexCount = drawInfo->getIbCount();

        //memcpy(&ib[indexOffset], indexb, indexCount * sizeof(uint16_t));
        //indexOffset += indexCount;

        //buffer->setIndexOffset(indexOffset);
    }

    inline void FillVertexBuffers(RenderEntity* entity, RenderDrawInfo* drawInfo) 
    {
        //Node* node = entity->getNode();
        //const glm::mat4& matrix = node->getWorldMatrix();
        //uint8_t stride = drawInfo->getStride();
        //uint32_t size = drawInfo->getVbCount() * stride;
        //float* vbBuffer = drawInfo->getVbBuffer();
        //for (int i = 0; i < size; i += stride) 
        //{
        //    Render2dLayout* curLayout = drawInfo->getRender2dLayout(i);
        //    static_assert(sizeof(glm::vec3) == 3 * sizeof(float));
        //    reinterpret_cast<glm::vec3*>(vbBuffer + i)->transformMat4(curLayout->position, matrix);
        //}
    }

    inline void SetIndexRange(RenderDrawInfo* drawInfo) 
    {
        //UIMeshBuffer* buffer = drawInfo->getMeshBuffer();
        //uint32_t indexOffset = drawInfo->getIndexOffset();
        //uint32_t indexCount = drawInfo->getIbCount();
        //indexOffset += indexCount;
        //if (buffer->getIndexOffset() < indexOffset) 
        //{
        //    buffer->setIndexOffset(indexOffset);
        //}
    }

    inline void FillColors(RenderEntity* entity, RenderDrawInfo* drawInfo) 
    {
        //Color temp = entity->getColor();

        //uint8_t stride = drawInfo->getStride();
        //uint32_t size = drawInfo->getVbCount() * stride;
        //float* vbBuffer = drawInfo->getVbBuffer();

        //uint32_t offset = 0;
        //for (int i = 0; i < size; i += stride) 
        //{
        //    offset = i + 5;
        //    vbBuffer[offset++] = static_cast<float>(temp.r) / 255.0F;
        //    vbBuffer[offset++] = static_cast<float>(temp.g) / 255.0F;
        //    vbBuffer[offset++] = static_cast<float>(temp.b) / 255.0F;
        //    vbBuffer[offset++] = entity->getOpacity();
        //}
    }

    void InsertMaskBatch(RenderEntity* entity);
    void CreateClearModel();

    DescriptorSet* GetDescriptorSet(Texture* texture, Sampler* sampler, DescriptorSetLayout* dsLayout);

    //StencilManager* _stencilManager{ nullptr };

    Root* _root{ nullptr };
    std::vector<Node*> _rootNodeArr;

    //std::vector<DrawBatch2D*> _batches;
    //memop::Pool<DrawBatch2D> _drawBatchPool;

    Device* _device{ nullptr };

    RenderEntity* _currEntity{ nullptr };
    RenderDrawInfo* _currDrawInfo{ nullptr };
    UIMeshBuffer* _currMeshBuffer{ nullptr };
    uint32_t _indexStart{ 0 };
    uint32_t _currLayer{ 0 };
    //StencilStage _currStencilStage{ StencilStage::DISABLED };

    Material* _currMaterial{ nullptr };
    Texture* _currTexture{ nullptr };
    Sampler* _currSampler{ nullptr };

    std::vector<RenderDrawInfo*> _meshRenderDrawInfo;

    //std::map<std::hash_t, DescriptorSet*> _descriptorSetCache;
    DescriptorSetInfo _dsInfo;

    UIMeshBufferMap _meshBuffersMap;

    std::vector<Attribute> _attributes
    {
        Attribute{ATTR_NAME_POSITION, Format::RGB32F},
        Attribute{ATTR_NAME_TEX_COORD, Format::RG32F},
        Attribute{ATTR_NAME_COLOR, Format::RGBA32F},
    };

    IntrusivePtr<Model> _maskClearModel;
    IntrusivePtr<Material> _maskClearMtl;
    //IntrusivePtr<RenderingSubMesh> _maskModelMesh;
    std::vector<Attribute> _maskAttributes{ Attribute{ATTR_NAME_POSITION, Format::RGB32F}, };
    PrimitiveMode _primitiveMode{ PrimitiveMode::TRIANGLE_LIST };

    DISALLOW_COPY_MOVE_ASSIGN(Batcher2d)
};

}