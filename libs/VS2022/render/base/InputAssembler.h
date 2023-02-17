#pragma once

#include "Object.h"

namespace ll
{

class InputAssembler : public Object
{
public:
    InputAssembler();
    ~InputAssembler() override;

    void Initialize(const InputAssemblerInfo& info);
    void Destroy();

    inline const AttributeList& GetAttributes() const { return _attributes; }
    inline const BufferList& GetVertexBuffers() const { return _vertexBuffers; }
    inline Buffer* GetIndexBuffer() const { return _indexBuffer; }
    inline Buffer* GetIndirectBuffer() const { return _indirectBuffer; }
    inline uint32_t GetAttributesHash() const { return _attributesHash; }

    inline const DrawInfo& GetDrawInfo() const { return _drawInfo; }
    inline void SetDrawInfo(const DrawInfo& info) { _drawInfo = info; }

    inline void SetVertexCount(uint32_t count) { _drawInfo.vertexCount = count; }
    inline void SetFirstVertex(uint32_t first) { _drawInfo.firstVertex = first; }
    inline void SetIndexCount(uint32_t count) { _drawInfo.indexCount = count; }
    inline void SetFirstIndex(uint32_t first) { _drawInfo.firstIndex = first; }
    inline void SetVertexOffset(int32_t offset) { _drawInfo.vertexOffset = offset; }
    inline void SetInstanceCount(uint32_t count) { _drawInfo.instanceCount = count; }
    inline void SetFirstInstance(uint32_t first) { _drawInfo.firstInstance = first; }

    inline uint32_t GetVertexCount() const { return _drawInfo.vertexCount; }
    inline uint32_t GetFirstVertex() const { return _drawInfo.firstVertex; }
    inline uint32_t GetIndexCount() const { return _drawInfo.indexCount; }
    inline uint32_t GetFirstIndex() const { return _drawInfo.firstIndex; }
    inline uint32_t GetVertexOffset() const { return _drawInfo.vertexOffset; }
    inline uint32_t GetInstanceCount() const { return _drawInfo.instanceCount; }
    inline uint32_t GetFirstInstance() const { return _drawInfo.firstInstance; }

protected:
    virtual void DoInit(const InputAssemblerInfo& info) = 0;
    virtual void DoDestroy() = 0;

    uint32_t ComputeAttributesHash() const;

    AttributeList _attributes;
    uint32_t _attributesHash = 0;

    BufferList _vertexBuffers;
    Buffer* _indexBuffer{ nullptr };
    Buffer* _indirectBuffer{ nullptr };

    DrawInfo _drawInfo;
};

}