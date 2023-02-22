#pragma once

#include "../base/Ptr.h"
#include "../base/Def_common.h"
#include "../scene/Light.h"

#include <string>

namespace ll
{

enum class UpdateFrequency 
{
    PER_INSTANCE,
    PER_BATCH,
    PER_QUEUE,
    PER_PASS,
    COUNT,
};

enum class TaskType 
{
    SYNC,
    ASYNC,
};

enum class ResourceResidency 
{
    MANAGED,
    MEMORYLESS,
    PERSISTENT,
    EXTERNAL,
    BACKBUFFER,
};

enum class SceneFlags : uint32_t 
{
    NONE = 0,
    OPAQUE_OBJECT = 1,
    CUTOUT_OBJECT = 2,
    TRANSPARENT_OBJECT = 4,
    SHADOW_CASTER = 8,
    UI = 16,
    DEFAULT_LIGHTING = 32,
    VOLUMETRIC_LIGHTING = 64,
    CLUSTERED_LIGHTING = 128,
    PLANAR_SHADOW = 256,
    GEOMETRY = 512,
    PROFILER = 1024,
    ALL = 0xFFFFFFFF,
};

enum class QueueHint 
{
    NONE,
    RENDER_OPAQUE,
    RENDER_CUTOUT,
    RENDER_TRANSPARENT,
};

enum class ParameterType 
{
    CONSTANTS,
    CBV,
    UAV,
    SRV,
    TABLE,
    SSV,
};

enum class AccessType 
{
    READ,
    READ_WRITE,
    WRITE,
};

enum class ClearValueType 
{
    FLOAT_TYPE,
    INT_TYPE,
};

enum class AttachmentType 
{
    RENDER_TARGET,
    DEPTH_STENCIL,
};

struct ComputeView 
{
    ComputeView(ComputeView&& rhs) noexcept = default;
    ComputeView(ComputeView const& rhs) = delete;
    ComputeView& operator=(ComputeView&& rhs) = default;
    ComputeView& operator=(ComputeView const& rhs) = default;

    bool isRead() const 
    {
        return accessType != AccessType::WRITE;
    }
    bool isWrite() const 
    {
        return accessType != AccessType::READ;
    }

    std::pmr::string name;
    AccessType         accessType{ AccessType::READ };
    ClearFlagBit  clearFlags{ ClearFlagBit::NONE };
    Color         clearColor;
    ClearValueType     clearValueType{ ClearValueType::FLOAT_TYPE };
};

struct LightInfo 
{
    LightInfo() = default;
    LightInfo(IntrusivePtr<Light> lightIn, uint32_t levelIn) noexcept
        : light(std::move(lightIn)),
        level(levelIn) {}

    IntrusivePtr<Light> light;
    uint32_t                   level{ 0 };
};

struct RasterView 
{
    RasterView(RasterView&& rhs) noexcept = default;
    RasterView(RasterView const& rhs) = delete;
    RasterView& operator=(RasterView&& rhs) = default;
    RasterView& operator=(RasterView const& rhs) = default;

    std::pmr::string slotName;
    AccessType         accessType{ AccessType::WRITE };
    AttachmentType     attachmentType{ AttachmentType::RENDER_TARGET };
    LoadOp        loadOp{ LoadOp::LOAD };
    StoreOp       storeOp{ StoreOp::STORE };
    ClearFlagBit  clearFlags{ ClearFlagBit::ALL };
    Color         clearColor;
};

}

class RenderCommonTypes
{
};
