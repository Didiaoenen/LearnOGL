#include "Mesh.h"

using namespace ll;

ll::Mesh::~Mesh()
{
}

uint32_t ll::Mesh::GetSubMeshCount() const
{
    return 0;
}

const glm::vec3* ll::Mesh::GetMinPosition() const
{
    return nullptr;
}

const glm::vec3* ll::Mesh::GetMaxPosition() const
{
    return nullptr;
}

const Mesh::JointBufferIndicesType& ll::Mesh::GetJointBufferIndices()
{
    // TODO: 在此处插入 return 语句
    return {};
}

void ll::Mesh::Initialize()
{
}

void ll::Mesh::DestroyRenderingMesh()
{
}

void ll::Mesh::Assign(const IStruct& structInfo, const Uint8Array& data)
{
}

void ll::Mesh::Reset(ICreateInfo&& info)
{
}

Mesh::BoneSpaceBounds ll::Mesh::GetBoneSpaceBounds(Skeleton* skeleton)
{
    return Mesh::BoneSpaceBounds();
}

bool ll::Mesh::Merge(Mesh* mesh, const glm::mat4* worldMatrix, bool validate)
{
    return false;
}

bool ll::Mesh::ValidateMergingMesh(Mesh* mesh)
{
    return false;
}

TypedArray ll::Mesh::ReadAttribute(index_t primitiveIndex, const char* attributeName)
{
    return TypedArray();
}

bool ll::Mesh::CopyAttribute(index_t primitiveIndex, const char* attributeName, ArrayBuffer* buffer, uint32_t stride, uint32_t offset)
{
    return false;
}

IBArray ll::Mesh::ReadIndices(index_t primitiveIndex)
{
    return IBArray();
}

bool ll::Mesh::CopyIndices(index_t primitiveIndex, TypedArray& outputArray)
{
    return false;
}

const FormatInfo* ll::Mesh::ReadAttributeFormat(index_t primitiveIndex, const char* attributeName)
{
    return nullptr;
}

void ll::Mesh::UpdateSubMesh(index_t primitiveIndex, const IDynamicGeometry& geometry)
{
}

void ll::Mesh::SetAllowDataAccess(bool allowDataAccess)
{
}

void ll::Mesh::AccessAttribute(index_t primitiveIndex, const char* attributeName, const AccessorType& accessor)
{
}

BufferList ll::Mesh::CreateVertexBuffers(Device* gfxDevice, ArrayBuffer* data)
{
    return BufferList();
}

void ll::Mesh::TryConvertVertexData()
{
}

void ll::Mesh::ReleaseData()
{
}

TypedArray ll::Mesh::CreateTypedArrayWithGFXFormat(Format format, uint32_t count)
{
    return TypedArray();
}
