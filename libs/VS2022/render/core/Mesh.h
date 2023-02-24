#pragma once

#include "../base/Ptr.h"
#include "../base/Def_common.h"
#include "../primitive/PrimitiveDefine.h"

#include "Asset.h"
#include "Morph.h"
#include "Types.h"
#include "TypedArray.h"

#include <glm/glm.hpp>
#include <vector>
#include <optional>
#include <functional>

namespace ll
{

class AABB;
class Device;
class Skeleton;
class ArrayBuffer;
class MorphRendering;
class RenderingSubMesh;

class Mesh : public Asset
{
    using Super = Asset;

    using IBufferView = IMeshBufferView;

    struct IVertexBundle 
    {
        std::optional<uint8_t> _padding;
        IBufferView view;
        AttributeList attributes;
    };

    struct ISubMesh 
    {
        std::vector<uint32_t> vertexBundelIndices;
        PrimitiveMode primitiveMode;
        std::optional<IBufferView> indexView;
        std::optional<uint32_t> jointMapIndex;
    };

    struct IDynamicInfo 
    {
        uint32_t maxSubMeshes{ 0U };
        uint32_t maxSubMeshVertices{ 0U };
        uint32_t maxSubMeshIndices{ 0U };
    };

    struct IDynamicStruct 
    {
        IDynamicInfo info;
        std::vector<AABB> bounds;
    };

    struct IStruct 
    {
        std::vector<IVertexBundle> vertexBundles;
        std::vector<ISubMesh> primitives;
        std::optional<glm::vec3> minPosition;
        inline const std::optional<glm::vec3>& getMinPosition() const { return minPosition; }
        inline void setMinPosition(const std::optional<glm::vec3>& v) { minPosition = v; }

        std::optional<glm::vec3> maxPosition;
        inline const std::optional<glm::vec3>& getMaxPosition() const { return maxPosition; }
        inline void setMaxPosition(const std::optional<glm::vec3>& v) { maxPosition = v; }

        std::optional<std::vector<std::vector<index_t>>> jointMaps;
        std::optional<Morph> morph;
        std::optional<IDynamicStruct> dynamic;
    };

    struct ICreateInfo 
    {
        IStruct structInfo;
        Uint8Array data;
    };

    Mesh() = default;
    ~Mesh() override;

    void SetAssetData(ArrayBuffer* data) { _data = Uint8Array(data); }

    ArrayBuffer* GetAssetData() const { return _data.buffer(); }

    uint32_t GetSubMeshCount() const;

    const glm::vec3* GetMinPosition() const;

    const glm::vec3* GetMaxPosition() const;

    inline const IStruct& GetStruct() const { return _struct; }

    inline void SetStruct(const IStruct& input) { _struct = input; }

    inline Uint8Array& GetData() { return _data; }

    inline void SetData(const Uint8Array& data) { _data = data; }

    using JointBufferIndicesType = std::vector<index_t>;
    const JointBufferIndicesType& GetJointBufferIndices();

    using RenderingSubMeshList = std::vector<IntrusivePtr<RenderingSubMesh>>;
    inline const RenderingSubMeshList& GetRenderingSubMeshes() 
    {
        Initialize();
        return _renderingSubMeshes;
    }

    void OnLoaded() override { Initialize(); }

    void Initialize();

    bool Destroy() override 
    {
        DestroyRenderingMesh();
        return Super::Destroy();
    }

    void DestroyRenderingMesh();

    void Assign(const IStruct& structInfo, const Uint8Array& data);

    void Reset(ICreateInfo&& info);

    using BoneSpaceBounds = std::vector<IntrusivePtr<AABB>>;
    BoneSpaceBounds GetBoneSpaceBounds(Skeleton* skeleton);

    bool Merge(Mesh* mesh, const glm::mat4* worldMatrix = nullptr, bool validate = false);

    bool ValidateMergingMesh(Mesh* mesh);

    TypedArray ReadAttribute(index_t primitiveIndex, const char* attributeName);

    bool CopyAttribute(index_t primitiveIndex, const char* attributeName, ArrayBuffer* buffer, uint32_t stride, uint32_t offset);

    IBArray ReadIndices(index_t primitiveIndex);

    bool CopyIndices(index_t primitiveIndex, TypedArray& outputArray);

    const FormatInfo* ReadAttributeFormat(index_t primitiveIndex, const char* attributeName);

    void UpdateSubMesh(index_t primitiveIndex, const IDynamicGeometry& geometry);

    void SetAllowDataAccess(bool allowDataAccess);

    inline bool IsAllowDataAccess() const { return _allowDataAccess; }

private:
    using AccessorType = std::function<void(const IVertexBundle& vertexBundle, int32_t iAttribute)>;

    void AccessAttribute(index_t primitiveIndex, const char* attributeName, const AccessorType& accessor);

    BufferList CreateVertexBuffers(Device* gfxDevice, ArrayBuffer* data);
    void TryConvertVertexData();

    void ReleaseData();

    static TypedArray CreateTypedArrayWithGFXFormat(Format format, uint32_t count);

public:
    IntrusivePtr<MorphRendering> morphRendering;

private:
    IStruct _struct;
    Uint8Array _data;

    bool _initialized{ false };
    bool _allowDataAccess{ true };
    bool _isMeshDataUploaded{ false };

    RenderingSubMeshList _renderingSubMeshes;

    std::unordered_map<uint64_t, BoneSpaceBounds> _boneSpaceBounds;

    JointBufferIndicesType _jointBufferIndices;

    friend class MeshDeserializer;

    DISALLOW_COPY_MOVE_ASSIGN(Mesh)
};

}