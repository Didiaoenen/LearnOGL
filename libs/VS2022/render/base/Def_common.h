#pragma once

#include <string>
#include <vector>

#include "Def_type.h"

#include "Queue.h"
#include "Texture.h"
#include "QueryPool.h"
#include "CommandBuffer.h"
#include "TextureBarrier.h"
#include "GeneralBarrier.h"
#include "DescriptorSetLayout.h"

namespace ll
{

class Swapchain;
class Sampler;

using BufferBarrierList = std::vector<BufferBarrier*>;
using TextureBarrierList = std::vector<TextureBarrier*>;
using IndexList = std::vector<uint32_t>;
using SamplerList = std::vector<Sampler*>;
using TextureList = std::vector<Texture*>;
using CommandBufferList = std::vector<CommandBuffer*>;
using QueryPoolList = std::vector<QueryPool*>;
using BufferDataList = std::vector<const uint8_t*>;
using DescriptorSetLayoutList = std::vector<DescriptorSetLayout*>;

using BufferSrcList = std::vector<uint8_t*>;

constexpr uint32_t MAX_ATTACHMENTS = 4U;
constexpr uint32_t INVALID_BINDING = ~0U;
constexpr uint32_t SUBPASS_EXTERNAL = ~0U;

using BufferList = std::vector<Buffer*>;

enum class TextureType : uint32_t 
{
    TEX1D,
    TEX2D,
    TEX3D,
    CUBE,
    TEX1D_ARRAY,
    TEX2D_ARRAY,
};

enum class TextureUsageBit : uint32_t 
{
    NONE = 0,
    TRANSFER_SRC = 0x1,
    TRANSFER_DST = 0x2,
    SAMPLED = 0x4,
    STORAGE = 0x8,
    COLOR_ATTACHMENT = 0x10,
    DEPTH_STENCIL_ATTACHMENT = 0x20,
    INPUT_ATTACHMENT = 0x40,
};
using TextureUsage = TextureUsageBit;

enum class TextureFlagBit : uint32_t 
{
    NONE = 0,
    GEN_MIPMAP = 0x1,
    GENERAL_LAYOUT = 0x2,
};
using TextureFlags = TextureFlagBit;

enum class SampleCount : uint32_t 
{
    ONE,
    MULTIPLE_PERFORMANCE,
    MULTIPLE_BALANCE,
    MULTIPLE_QUALITY,
};
CC_ENUM_CONVERSION_OPERATOR(SampleCount);

#define EXPOSE_COPY_FN(type)      \
    type &copy(const type &rhs) { \
        *this = rhs;              \
        return *this;             \
    }

enum class Format : uint32_t 
{

    UNKNOWN,

    A8,
    L8,
    LA8,

    R8,
    R8SN,
    R8UI,
    R8I,
    R16F,
    R16UI,
    R16I,
    R32F,
    R32UI,
    R32I,

    RG8,
    RG8SN,
    RG8UI,
    RG8I,
    RG16F,
    RG16UI,
    RG16I,
    RG32F,
    RG32UI,
    RG32I,

    RGB8,
    SRGB8,
    RGB8SN,
    RGB8UI,
    RGB8I,
    RGB16F,
    RGB16UI,
    RGB16I,
    RGB32F,
    RGB32UI,
    RGB32I,

    RGBA8,
    BGRA8,
    SRGB8_A8,
    RGBA8SN,
    RGBA8UI,
    RGBA8I,
    RGBA16F,
    RGBA16UI,
    RGBA16I,
    RGBA32F,
    RGBA32UI,
    RGBA32I,

    // Special Format
    R5G6B5,
    R11G11B10F,
    RGB5A1,
    RGBA4,
    RGB10A2,
    RGB10A2UI,
    RGB9E5,

    // Depth-Stencil Format
    DEPTH,
    DEPTH_STENCIL,

    // Compressed Format

    // Block Compression Format, DDS (DirectDraw Surface)
    // DXT1: 3 channels (5:6:5), 1/8 original size, with 0 or 1 bit of alpha
    BC1,
    BC1_ALPHA,
    BC1_SRGB,
    BC1_SRGB_ALPHA,
    // DXT3: 4 channels (5:6:5), 1/4 original size, with 4 bits of alpha
    BC2,
    BC2_SRGB,
    // DXT5: 4 channels (5:6:5), 1/4 original size, with 8 bits of alpha
    BC3,
    BC3_SRGB,
    // 1 channel (8), 1/4 original size
    BC4,
    BC4_SNORM,
    // 2 channels (8:8), 1/2 original size
    BC5,
    BC5_SNORM,
    // 3 channels (16:16:16), half-floating point, 1/6 original size
    // UF16: unsigned float, 5 exponent bits + 11 mantissa bits
    // SF16: signed float, 1 signed bit + 5 exponent bits + 10 mantissa bits
    BC6H_UF16,
    BC6H_SF16,
    // 4 channels (4~7 bits per channel) with 0 to 8 bits of alpha, 1/3 original size
    BC7,
    BC7_SRGB,

    // Ericsson Texture Compression Format
    ETC_RGB8,
    ETC2_RGB8,
    ETC2_SRGB8,
    ETC2_RGB8_A1,
    ETC2_SRGB8_A1,
    ETC2_RGBA8,
    ETC2_SRGB8_A8,
    EAC_R11,
    EAC_R11SN,
    EAC_RG11,
    EAC_RG11SN,

    // PVRTC (PowerVR)
    PVRTC_RGB2,
    PVRTC_RGBA2,
    PVRTC_RGB4,
    PVRTC_RGBA4,
    PVRTC2_2BPP,
    PVRTC2_4BPP,

    // ASTC (Adaptive Scalable Texture Compression)
    ASTC_RGBA_4X4,
    ASTC_RGBA_5X4,
    ASTC_RGBA_5X5,
    ASTC_RGBA_6X5,
    ASTC_RGBA_6X6,
    ASTC_RGBA_8X5,
    ASTC_RGBA_8X6,
    ASTC_RGBA_8X8,
    ASTC_RGBA_10X5,
    ASTC_RGBA_10X6,
    ASTC_RGBA_10X8,
    ASTC_RGBA_10X10,
    ASTC_RGBA_12X10,
    ASTC_RGBA_12X12,

    // ASTC (Adaptive Scalable Texture Compression) SRGB
    ASTC_SRGBA_4X4,
    ASTC_SRGBA_5X4,
    ASTC_SRGBA_5X5,
    ASTC_SRGBA_6X5,
    ASTC_SRGBA_6X6,
    ASTC_SRGBA_8X5,
    ASTC_SRGBA_8X6,
    ASTC_SRGBA_8X8,
    ASTC_SRGBA_10X5,
    ASTC_SRGBA_10X6,
    ASTC_SRGBA_10X8,
    ASTC_SRGBA_10X10,
    ASTC_SRGBA_12X10,
    ASTC_SRGBA_12X12,

    // Total count
    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(Format);

enum class FormatType : uint32_t 
{
    NONE,
    UNORM,
    SNORM,
    UINT,
    INT,
    UFLOAT,
    FLOAT,
};

enum class Filter : uint32_t 
{
    NONE,
    POINT,
    LINEAR,
    ANISOTROPIC,
};
CC_ENUM_CONVERSION_OPERATOR(Filter);

enum class Address : uint32_t 
{
    WRAP,
    MIRROR,
    CLAMP,
    BORDER,
};
CC_ENUM_CONVERSION_OPERATOR(Address);

enum class BufferUsageBit : uint32_t 
{
    NONE = 0,
    TRANSFER_SRC = 0x1,
    TRANSFER_DST = 0x2,
    INDEX = 0x4,
    VERTEX = 0x8,
    UNIFORM = 0x10,
    STORAGE = 0x20,
    INDIRECT = 0x40,
};
using BufferUsage = BufferUsageBit;
CC_ENUM_BITWISE_OPERATORS(BufferUsageBit);

enum class DynamicStateFlagBit : uint32_t 
{
    NONE = 0x0,
    LINE_WIDTH = 0x1,
    DEPTH_BIAS = 0x2,
    BLEND_CONSTANTS = 0x4,
    DEPTH_BOUNDS = 0x8,
    STENCIL_WRITE_MASK = 0x10,
    STENCIL_COMPARE_MASK = 0x20,
};
using DynamicStateList = std::vector<DynamicStateFlagBit>;
using DynamicStateFlags = DynamicStateFlagBit;
CC_ENUM_BITWISE_OPERATORS(DynamicStateFlagBit);

struct DrawInfo 
{
    uint32_t vertexCount{ 0 };
    uint32_t firstVertex{ 0 };
    uint32_t indexCount{ 0 };
    uint32_t firstIndex{ 0 };
    int32_t vertexOffset{ 0 };
    uint32_t instanceCount{ 0 };
    uint32_t firstInstance{ 0 };

    EXPOSE_COPY_FN(DrawInfo)
};
using DrawInfoList = std::vector<DrawInfo>;

struct FormatInfo 
{
    const std::string name;
    const uint32_t size{ 0 };
    const uint32_t count{ 0 };
    const FormatType type{ FormatType::NONE };
    const bool hasAlpha{ false };
    const bool hasDepth{ false };
    const bool hasStencil{ false };
    const bool isCompressed{ false };
};

struct alignas(8) TextureInfo 
{
    TextureType type{ TextureType::TEX2D };
    TextureUsage usage{ TextureUsageBit::NONE };
    Format format{ Format::UNKNOWN };
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    TextureFlags flags{ TextureFlagBit::NONE };
    uint32_t layerCount{ 1 };
    uint32_t levelCount{ 1 };
    SampleCount samples{ SampleCount::ONE };
    uint32_t depth{ 1 };
    void* externalRes{ nullptr };

    EXPOSE_COPY_FN(TextureInfo)
};

enum class LoadOp : uint32_t 
{
    LOAD,
    CLEAR,
    DISCARD,
};
CC_ENUM_CONVERSION_OPERATOR(LoadOp);

enum class StoreOp : uint32_t 
{
    STORE,
    DISCARD,
};
CC_ENUM_CONVERSION_OPERATOR(StoreOp);

struct alignas(8) TextureViewInfo 
{
    Texture* texture{ nullptr };
    TextureType type{ TextureType::TEX2D };
    Format format{ Format::UNKNOWN };
    uint32_t baseLevel{ 0 };
    uint32_t levelCount{ 1 };
    uint32_t baseLayer{ 0 };
    uint32_t layerCount{ 1 };

    EXPOSE_COPY_FN(TextureViewInfo)
};

struct alignas(8) ColorAttachment 
{
    Format format{ Format::UNKNOWN };
    SampleCount sampleCount{ SampleCount::ONE };
    LoadOp loadOp{ LoadOp::CLEAR };
    StoreOp storeOp{ StoreOp::STORE };
    GeneralBarrier* barrier{ nullptr };
    uint32_t isGeneralLayout{ 0 };

    EXPOSE_COPY_FN(ColorAttachment)
};
using ColorAttachmentList = std::vector<ColorAttachment>;

struct alignas(8) DepthStencilAttachment 
{
    Format format{ Format::UNKNOWN };
    SampleCount sampleCount{ SampleCount::ONE };
    LoadOp depthLoadOp{ LoadOp::CLEAR };
    StoreOp depthStoreOp{ StoreOp::STORE };
    LoadOp stencilLoadOp{ LoadOp::CLEAR };
    StoreOp stencilStoreOp{ StoreOp::STORE };
    GeneralBarrier* barrier{ nullptr };
    uint32_t isGeneralLayout{ 0 };

    EXPOSE_COPY_FN(DepthStencilAttachment)
};

struct UniformBlock 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformBlock)
};
using UniformBlockList = std::vector<UniformBlock>;

struct Offset 
{
    int32_t x{ 0 };
    int32_t y{ 0 };
    int32_t z{ 0 };

    EXPOSE_COPY_FN(Offset)
};

struct Rect {
    int32_t x{ 0 };
    int32_t y{ 0 };
    uint32_t width{ 0 };
    uint32_t height{ 0 };

    EXPOSE_COPY_FN(Rect)
};

struct Extent 
{
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    uint32_t depth{ 1 };

    EXPOSE_COPY_FN(Extent)
};

struct Viewport 
{
    int32_t left{ 0 };
    int32_t top{ 0 };
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    float minDepth{ 0.F };
    float maxDepth{ 1.F };

    EXPOSE_COPY_FN(Viewport)
};

struct Color 
{
    float x{ 0.F };
    float y{ 0.F };
    float z{ 0.F };
    float w{ 0.F };

    EXPOSE_COPY_FN(Color)
};
using ColorList = std::vector<Color>;

struct BindingMappingInfo 
{
    IndexList maxBlockCounts{ 0 };
    IndexList maxSamplerTextureCounts{ 0 };
    IndexList maxSamplerCounts{ 0 };
    IndexList maxTextureCounts{ 0 };
    IndexList maxBufferCounts{ 0 };
    IndexList maxImageCounts{ 0 };
    IndexList maxSubpassInputCounts{ 0 };

    IndexList setIndices{ 0 };

    EXPOSE_COPY_FN(BindingMappingInfo)
};

struct DeviceInfo 
{
    BindingMappingInfo bindingMappingInfo;

    EXPOSE_COPY_FN(DeviceInfo)
};

struct Attribute 
{
    std::string name;
    Format format{ Format::UNKNOWN };
    bool isNormalized{ false };
    uint32_t stream{ 0 };
    bool isInstanced{ false };
    uint32_t location{ 0 };

    EXPOSE_COPY_FN(Attribute)
};
using AttributeList = std::vector<Attribute>;

struct TextureSubresLayers 
{
    uint32_t mipLevel{ 0 };
    uint32_t baseArrayLayer{ 0 };
    uint32_t layerCount{ 1 };

    EXPOSE_COPY_FN(TextureSubresLayers)
};

enum class DescriptorType : uint32_t 
{
    UNKNOWN = 0,
    UNIFORM_BUFFER = 0x1,
    DYNAMIC_UNIFORM_BUFFER = 0x2,
    STORAGE_BUFFER = 0x4,
    DYNAMIC_STORAGE_BUFFER = 0x8,
    SAMPLER_TEXTURE = 0x10,
    SAMPLER = 0x20,
    TEXTURE = 0x40,
    STORAGE_IMAGE = 0x80,
    INPUT_ATTACHMENT = 0x100,
};
CC_ENUM_BITWISE_OPERATORS(DescriptorType);

enum class ShaderStageFlagBit : uint32_t 
{
    NONE = 0x0,
    VERTEX = 0x1,
    CONTROL = 0x2,
    EVALUATION = 0x4,
    GEOMETRY = 0x8,
    FRAGMENT = 0x10,
    COMPUTE = 0x20,
    ALL = 0x3f,
};
using ShaderStageFlags = ShaderStageFlagBit;
CC_ENUM_BITWISE_OPERATORS(ShaderStageFlagBit);

enum class BlendFactor : uint32_t 
{
    ZERO,
    ONE,
    SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    ONE_MINUS_DST_ALPHA,
    SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_SRC_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA_SATURATE,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA,
};
CC_ENUM_CONVERSION_OPERATOR(BlendFactor);

enum class BlendOp : uint32_t 
{
    ADD,
    SUB,
    REV_SUB,
    MIN,
    MAX,
};
CC_ENUM_CONVERSION_OPERATOR(BlendOp);

enum class ColorMask : uint32_t 
{
    NONE = 0x0,
    R = 0x1,
    G = 0x2,
    B = 0x4,
    A = 0x8,
    ALL = R | G | B | A,
};
CC_ENUM_BITWISE_OPERATORS(ColorMask);

struct BlendTarget 
{
    uint32_t blend{ 0 };
    BlendFactor blendSrc{ BlendFactor::ONE };
    BlendFactor blendDst{ BlendFactor::ZERO };
    BlendOp blendEq{ BlendOp::ADD };
    BlendFactor blendSrcAlpha{ BlendFactor::ONE };
    BlendFactor blendDstAlpha{ BlendFactor::ZERO };
    BlendOp blendAlphaEq{ BlendOp::ADD };
    ColorMask blendColorMask{ ColorMask::ALL };

    void reset() 
    {
        *this = BlendTarget();
    }

    EXPOSE_COPY_FN(BlendTarget)
};

using BlendTargetList = std::vector<BlendTarget>;

struct BlendState 
{
    uint32_t isA2C{ 0 };
    uint32_t isIndepend{ 0 };
    Color blendColor;
    BlendTargetList targets{ 1 };

    void setTarget(index_t index, const BlendTarget& target) 
    {
        if (index >= targets.size()) {
            targets.resize(index + 1);
        }
        targets[index] = target;
    }

    void reset() 
    {
        *this = BlendState();
    }

    void destroy() {}

    EXPOSE_COPY_FN(BlendState)
};

enum class ComparisonFunc : uint32_t 
{
    NEVER,
    LESS,
    EQUAL,
    LESS_EQUAL,
    GREATER,
    NOT_EQUAL,
    GREATER_EQUAL,
    ALWAYS,
};
CC_ENUM_CONVERSION_OPERATOR(ComparisonFunc);

enum class StencilOp : uint32_t 
{
    ZERO,
    KEEP,
    REPLACE,
    INCR,
    DECR,
    INVERT,
    INCR_WRAP,
    DECR_WRAP,
};
CC_ENUM_CONVERSION_OPERATOR(StencilOp);

struct RasterizerState 
{
    uint32_t isDiscard{ 0 };
    PolygonMode polygonMode{ PolygonMode::FILL };
    ShadeModel shadeModel{ ShadeModel::GOURAND };
    CullMode cullMode{ CullMode::BACK };
    uint32_t isFrontFaceCCW{ 1 };
    uint32_t depthBiasEnabled{ 0 };
    float depthBias{ 0.F };
    float depthBiasClamp{ 0.F };
    float depthBiasSlop{ 0.F };
    uint32_t isDepthClip{ 1 };
    uint32_t isMultisample{ 0 };
    float lineWidth{ 1.F };

    void reset() 
    {
        *this = RasterizerState();
    }

    EXPOSE_COPY_FN(RasterizerState)
};

enum class PolygonMode : uint32_t 
{
    FILL,
    POINT,
    LINE,
};
CC_ENUM_CONVERSION_OPERATOR(PolygonMode);

enum class ShadeModel : uint32_t 
{
    GOURAND,
    FLAT,
};
CC_ENUM_CONVERSION_OPERATOR(ShadeModel);

enum class CullMode : uint32_t 
{
    NONE,
    FRONT,
    BACK,
};
CC_ENUM_CONVERSION_OPERATOR(CullMode);

enum class ResolveMode : uint32_t 
{
    NONE,
    SAMPLE_ZERO,
    AVERAGE,
    MIN,
    MAX,
};
CC_ENUM_CONVERSION_OPERATOR(ResolveMode);

struct SubpassInfo 
{
    IndexList inputs;
    IndexList colors;
    IndexList resolves;
    IndexList preserves;

    uint32_t depthStencil{ INVALID_BINDING };
    uint32_t depthStencilResolve{ INVALID_BINDING };
    ResolveMode depthResolveMode{ ResolveMode::NONE };
    ResolveMode stencilResolveMode{ ResolveMode::NONE };

    EXPOSE_COPY_FN(SubpassInfo)
};
using SubpassInfoList = std::vector<SubpassInfo>;

enum class Type : uint32_t 
{
    UNKNOWN,
    BOOL,
    BOOL2,
    BOOL3,
    BOOL4,
    INT,
    INT2,
    INT3,
    INT4,
    UINT,
    UINT2,
    UINT3,
    UINT4,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    MAT2,
    MAT2X3,
    MAT2X4,
    MAT3X2,
    MAT3,
    MAT3X4,
    MAT4X2,
    MAT4X3,
    MAT4,
    // combined image samplers
    SAMPLER1D,
    SAMPLER1D_ARRAY,
    SAMPLER2D,
    SAMPLER2D_ARRAY,
    SAMPLER3D,
    SAMPLER_CUBE,
    // sampler
    SAMPLER,
    // sampled textures
    TEXTURE1D,
    TEXTURE1D_ARRAY,
    TEXTURE2D,
    TEXTURE2D_ARRAY,
    TEXTURE3D,
    TEXTURE_CUBE,
    // storage images
    IMAGE1D,
    IMAGE1D_ARRAY,
    IMAGE2D,
    IMAGE2D_ARRAY,
    IMAGE3D,
    IMAGE_CUBE,
    // input attachment
    SUBPASS_INPUT,
    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(Type);

enum class VsyncMode : uint32_t 
{
    OFF,
    ON,
    RELAXED,
    MAILBOX,
    HALF,
};
CC_ENUM_CONVERSION_OPERATOR(VsyncMode);

struct SwapchainInfo 
{
    void* windowHandle{ nullptr };
    VsyncMode vsyncMode{ VsyncMode::ON };

    uint32_t width{ 0 };
    uint32_t height{ 0 };

    EXPOSE_COPY_FN(SwapchainInfo)
};

enum class SurfaceTransform : uint32_t 
{
    IDENTITY,
    ROTATE_90,
    ROTATE_180,
    ROTATE_270,
};
CC_ENUM_CONVERSION_OPERATOR(SurfaceTransform);

struct ShaderInfo 
{
    std::string name;
    ShaderStageList stages;
    AttributeList attributes;
    UniformBlockList blocks;
    UniformStorageBufferList buffers;
    UniformSamplerTextureList samplerTextures;
    UniformSamplerList samplers;
    UniformTextureList textures;
    UniformStorageImageList images;
    UniformInputAttachmentList subpassInputs;

    EXPOSE_COPY_FN(ShaderInfo)
};

struct ShaderStage 
{
    ShaderStageFlagBit stage{ ShaderStageFlagBit::NONE };
    std::string source;

    EXPOSE_COPY_FN(ShaderStage)
};
using ShaderStageList = std::vector<ShaderStage>;

enum class MemoryAccessBit : uint32_t 
{
    NONE = 0,
    READ_ONLY = 0x1,
    WRITE_ONLY = 0x2,
    READ_WRITE = READ_ONLY | WRITE_ONLY,
};
using MemoryAccess = MemoryAccessBit;
CC_ENUM_BITWISE_OPERATORS(MemoryAccessBit);

struct UniformStorageBuffer 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    uint32_t count{ 0 };
    MemoryAccess memoryAccess{ MemoryAccessBit::READ_WRITE };

    EXPOSE_COPY_FN(UniformStorageBuffer)
};
using UniformStorageBufferList = std::vector<UniformStorageBuffer>;

struct UniformSamplerTexture 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformSamplerTexture)
};
using UniformSamplerTextureList = std::vector<UniformSamplerTexture>;

struct UniformSampler 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformSampler)
};
using UniformSamplerList = std::vector<UniformSampler>;

struct UniformTexture 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformTexture)
};
using UniformTextureList = std::vector<UniformTexture>;

struct UniformStorageImage 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };
    MemoryAccess memoryAccess{ MemoryAccessBit::READ_WRITE };

    EXPOSE_COPY_FN(UniformStorageImage)
};
using UniformStorageImageList = std::vector<UniformStorageImage>;

struct UniformInputAttachment 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformInputAttachment)
};
using UniformInputAttachmentList = std::vector<UniformInputAttachment>;

enum class MemoryUsageBit : uint32_t 
{
    NONE = 0,
    DEVICE = 0x1,
    HOST = 0x2,
};
using MemoryUsage = MemoryUsageBit;
CC_ENUM_BITWISE_OPERATORS(MemoryUsageBit);

enum class BufferFlagBit : uint32_t 
{
    NONE = 0,
};
using BufferFlags = BufferFlagBit;
CC_ENUM_BITWISE_OPERATORS(BufferFlagBit);

struct alignas(8) BufferInfo {
    BufferUsage usage{ BufferUsageBit::NONE };
    MemoryUsage memUsage{ MemoryUsageBit::NONE };
    uint32_t size{ 0 };
    uint32_t stride{ 1 };
    BufferFlags flags{ BufferFlagBit::NONE };
    uint32_t _padding{ 0 };

    EXPOSE_COPY_FN(BufferInfo)
};

struct BufferViewInfo 
{
    Buffer* buffer{ nullptr };
    uint32_t offset{ 0 };
    uint32_t range{ 0 };

    EXPOSE_COPY_FN(BufferViewInfo)
};

struct FramebufferInfo 
{
    RenderPass* renderPass{ nullptr };
    TextureList colorTextures;
    Texture* depthStencilTexture{ nullptr };

    EXPOSE_COPY_FN(FramebufferInfo)
};

enum class ClearFlagBit : uint32_t 
{
    NONE = 0,
    COLOR = 0x1,
    DEPTH = 0x2,
    STENCIL = 0x4,
    DEPTH_STENCIL = DEPTH | STENCIL,
    ALL = COLOR | DEPTH | STENCIL,
};
using ClearFlags = ClearFlagBit;
CC_ENUM_BITWISE_OPERATORS(ClearFlagBit);

struct BufferTextureCopy 
{
    uint32_t buffOffset{ 0 };
    uint32_t buffStride{ 0 };
    uint32_t buffTexHeight{ 0 };
    Offset texOffset;
    Extent texExtent;
    TextureSubresLayers texSubres;

    EXPOSE_COPY_FN(BufferTextureCopy)
};
using BufferTextureCopyList = std::vector<BufferTextureCopy>;

struct TextureBlit 
{
    TextureSubresLayers srcSubres;
    Offset srcOffset;
    Extent srcExtent;
    TextureSubresLayers dstSubres;
    Offset dstOffset;
    Extent dstExtent;

    EXPOSE_COPY_FN(TextureBlit)
};
using TextureBlitList = std::vector<TextureBlit>;

enum class CommandBufferType : uint32_t 
{
    PRIMARY,
    SECONDARY,
};
CC_ENUM_CONVERSION_OPERATOR(CommandBufferType);

struct CommandBufferInfo 
{
    Queue* queue{ nullptr };
    CommandBufferType type{ CommandBufferType::PRIMARY };

    EXPOSE_COPY_FN(CommandBufferInfo)
};

enum class StencilFace : uint32_t 
{
    FRONT = 0x1,
    BACK = 0x2,
    ALL = 0x3,
};
CC_ENUM_BITWISE_OPERATORS(StencilFace);

struct DispatchInfo 
{
    uint32_t groupCountX{ 0 };
    uint32_t groupCountY{ 0 };
    uint32_t groupCountZ{ 0 };

    Buffer* indirectBuffer{ nullptr };
    uint32_t indirectOffset{ 0 };

    EXPOSE_COPY_FN(DispatchInfo)
};

struct alignas(8) SubpassDependency 
{
    uint32_t srcSubpass{ 0 };
    uint32_t dstSubpass{ 0 };
    GeneralBarrier* generalBarrier{ nullptr };
    BufferBarrier** bufferBarriers{ nullptr };
    Buffer** buffers{ nullptr };
    uint32_t bufferBarrierCount{ 0 };
    TextureBarrier** textureBarriers{ nullptr };
    Texture** textures{ nullptr };
    uint32_t textureBarrierCount{ 0 };

    EXPOSE_COPY_FN(SubpassDependency)
};
using SubpassDependencyList = std::vector<SubpassDependency>;

struct RenderPassInfo 
{
    ColorAttachmentList colorAttachments;
    DepthStencilAttachment depthStencilAttachment;
    SubpassInfoList subpasses;
    SubpassDependencyList dependencies;

    EXPOSE_COPY_FN(RenderPassInfo)
};

struct DescriptorSetLayoutBinding 
{
    uint32_t binding{ INVALID_BINDING };
    DescriptorType descriptorType{ DescriptorType::UNKNOWN };
    uint32_t count{ 0 };
    ShaderStageFlags stageFlags{ ShaderStageFlagBit::NONE };
    SamplerList immutableSamplers;

    EXPOSE_COPY_FN(DescriptorSetLayoutBinding)
};
using DescriptorSetLayoutBindingList = std::vector<DescriptorSetLayoutBinding>;

struct MemoryStatus 
{
    uint32_t bufferSize{ 0 };
    uint32_t textureSize{ 0 };

    EXPOSE_COPY_FN(MemoryStatus)
};

enum class QueueType : uint32_t 
{
    GRAPHICS,
    COMPUTE,
    TRANSFER,
};
CC_ENUM_CONVERSION_OPERATOR(QueueType);

struct QueueInfo 
{
    QueueType type{ QueueType::GRAPHICS };

    EXPOSE_COPY_FN(QueueInfo)
};

enum class QueryType : uint32_t 
{
    OCCLUSION,
    PIPELINE_STATISTICS,
    TIMESTAMP,
};
CC_ENUM_CONVERSION_OPERATOR(QueryType);

struct QueryPoolInfo 
{
    QueryType type{ QueryType::OCCLUSION };
    uint32_t maxQueryObjects{ DEFAULT_MAX_QUERY_OBJECTS };
    bool forceWait{ true };

    EXPOSE_COPY_FN(QueryPoolInfo)
};

struct InputAssemblerInfo 
{
    AttributeList attributes;
    BufferList vertexBuffers;
    Buffer* indexBuffer{ nullptr };
    Buffer* indirectBuffer{ nullptr };

    EXPOSE_COPY_FN(InputAssemblerInfo)
};

struct DescriptorSetInfo 
{
    DescriptorSetLayout* layout{ nullptr };

    EXPOSE_COPY_FN(DescriptorSetInfo)
};

struct DescriptorSetLayoutInfo 
{
    DescriptorSetLayoutBindingList bindings;

    EXPOSE_COPY_FN(DescriptorSetLayoutInfo)
};

struct PipelineLayoutInfo 
{
    DescriptorSetLayoutList setLayouts;

    EXPOSE_COPY_FN(PipelineLayoutInfo)
};

struct PipelineStateInfo 
{
    Shader* shader{ nullptr };
    PipelineLayout* pipelineLayout{ nullptr };
    RenderPass* renderPass{ nullptr };
    InputState inputState;
    RasterizerState rasterizerState;
    DepthStencilState depthStencilState;
    BlendState blendState;
    PrimitiveMode primitive{ PrimitiveMode::TRIANGLE_LIST };
    DynamicStateFlags dynamicStates{ DynamicStateFlagBit::NONE };
    PipelineBindPoint bindPoint{ PipelineBindPoint::GRAPHICS };
    uint32_t subpass{ 0 };

    EXPOSE_COPY_FN(PipelineStateInfo)
};

struct alignas(8) SamplerInfo
{
    Filter minFilter{ Filter::LINEAR };
    Filter magFilter{ Filter::LINEAR };
    Filter mipFilter{ Filter::NONE };
    Address addressU{ Address::WRAP };
    Address addressV{ Address::WRAP };
    Address addressW{ Address::WRAP };
    uint32_t maxAnisotropy{ 0 };
    ComparisonFunc cmpFunc{ ComparisonFunc::ALWAYS };

    EXPOSE_COPY_FN(SamplerInfo)
};

struct alignas(8) GeneralBarrierInfo
{
    AccessFlags prevAccesses{ AccessFlagBit::NONE };
    AccessFlags nextAccesses{ AccessFlagBit::NONE };

    BarrierType type{ BarrierType::FULL };
    uint32_t _padding{ 0 };

    EXPOSE_COPY_FN(GeneralBarrierInfo)
};
using GeneralBarrierInfoList = std::vector<GeneralBarrierInfo>;

struct alignas(8) TextureBarrierInfo
{
    AccessFlags prevAccesses{ AccessFlagBit::NONE };
    AccessFlags nextAccesses{ AccessFlagBit::NONE };

    BarrierType type{ BarrierType::FULL };

    uint32_t baseMipLevel{ 0 };
    uint32_t levelCount{ 1 };
    uint32_t baseSlice{ 0 };
    uint32_t sliceCount{ 1 };

    uint64_t discardContents{ 0 }; // @ts-boolean

    Queue* srcQueue{ nullptr }; // @ts-nullable
    Queue* dstQueue{ nullptr }; // @ts-nullable

    EXPOSE_COPY_FN(TextureBarrierInfo)
};
using TextureBarrierInfoList = std::vector<TextureBarrierInfo>;

struct alignas(8) BufferBarrierInfo
{
    AccessFlags prevAccesses{ AccessFlagBit::NONE };
    AccessFlags nextAccesses{ AccessFlagBit::NONE };

    BarrierType type{ BarrierType::FULL };

    uint32_t offset{ 0 };
    uint32_t size{ 0 };

    uint64_t discardContents{ 0 }; // @ts-boolean

    Queue* srcQueue{ nullptr }; // @ts-nullable
    Queue* dstQueue{ nullptr }; // @ts-nullable

    EXPOSE_COPY_FN(BufferBarrierInfo)
};
using BufferBarrierInfoList = std::vector<BufferBarrierInfo>;

struct DeviceCaps 
{
    uint32_t maxVertexAttributes{ 0 };
    uint32_t maxVertexUniformVectors{ 0 };
    uint32_t maxFragmentUniformVectors{ 0 };
    uint32_t maxTextureUnits{ 0 };
    uint32_t maxImageUnits{ 0 };
    uint32_t maxVertexTextureUnits{ 0 };
    uint32_t maxColorRenderTargets{ 0 };
    uint32_t maxShaderStorageBufferBindings{ 0 };
    uint32_t maxShaderStorageBlockSize{ 0 };
    uint32_t maxUniformBufferBindings{ 0 };
    uint32_t maxUniformBlockSize{ 0 };
    uint32_t maxTextureSize{ 0 };
    uint32_t maxCubeMapTextureSize{ 0 };
    uint32_t uboOffsetAlignment{ 1 };

    uint32_t maxComputeSharedMemorySize{ 0 };
    uint32_t maxComputeWorkGroupInvocations{ 0 };
    Size maxComputeWorkGroupSize;
    Size maxComputeWorkGroupCount;

    bool supportQuery{ false };

    float clipSpaceMinZ{ -1.F };
    float screenSpaceSignY{ 1.F };
    float clipSpaceSignY{ 1.F };

    EXPOSE_COPY_FN(DeviceCaps)
};

enum class API : uint32_t 
{
    UNKNOWN,
    GLES2,
    GLES3,
    METAL,
    VULKAN,
    NVN,
    WEBGL,
    WEBGL2,
    WEBGPU,
};
CC_ENUM_CONVERSION_OPERATOR(API);

enum class Feature : uint32_t 
{
    ELEMENT_INDEX_UINT,
    INSTANCED_ARRAYS,
    MULTIPLE_RENDER_TARGETS,
    BLEND_MINMAX,
    COMPUTE_SHADER,
    INPUT_ATTACHMENT_BENEFIT,
    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(Feature);

enum class FormatFeatureBit : uint32_t 
{
    NONE = 0,
    RENDER_TARGET = 0x1,
    SAMPLED_TEXTURE = 0x2, 
    LINEAR_FILTER = 0x4,
    STORAGE_TEXTURE = 0x8,
    VERTEX_ATTRIBUTE = 0x10, 
};
using FormatFeature = FormatFeatureBit;
CC_ENUM_BITWISE_OPERATORS(FormatFeatureBit);

struct DeviceOptions 
{
    bool enableBarrierDeduce{ true };
};

struct BindingMappingInfo 
{
    IndexList maxBlockCounts{ 0 };
    IndexList maxSamplerTextureCounts{ 0 };
    IndexList maxSamplerCounts{ 0 };
    IndexList maxTextureCounts{ 0 };
    IndexList maxBufferCounts{ 0 };
    IndexList maxImageCounts{ 0 };
    IndexList maxSubpassInputCounts{ 0 };

    IndexList setIndices{ 0 };

    EXPOSE_COPY_FN(BindingMappingInfo)
};

struct DynamicStencilStates 
{
    uint32_t writeMask{ 0 };
    uint32_t compareMask{ 0 };
    uint32_t reference{ 0 };

    EXPOSE_COPY_FN(DynamicStencilStates)
};

struct DynamicStates 
{
    Viewport viewport;
    Rect scissor;
    Color blendConstant;
    float lineWidth{ 1.F };
    float depthBiasConstant{ 0.F };
    float depthBiasClamp{ 0.F };
    float depthBiasSlope{ 0.F };
    float depthMinBounds{ 0.F };
    float depthMaxBounds{ 0.F };

    DynamicStencilStates stencilStatesFront;
    DynamicStencilStates stencilStatesBack;

    EXPOSE_COPY_FN(DynamicStates)
};

enum class PipelineBindPoint : uint32_t 
{
    GRAPHICS,
    COMPUTE,
    RAY_TRACING,
};
CC_ENUM_CONVERSION_OPERATOR(PipelineBindPoint);

enum class PrimitiveMode : uint32_t 
{
    POINT_LIST,
    LINE_LIST,
    LINE_STRIP,
    LINE_LOOP,
    LINE_LIST_ADJACENCY,
    LINE_STRIP_ADJACENCY,
    ISO_LINE_LIST,
    TRIANGLE_LIST,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    TRIANGLE_LIST_ADJACENCY,
    TRIANGLE_STRIP_ADJACENCY,
    TRIANGLE_PATCH_ADJACENCY,
    QUAD_PATCH_LIST,
};
CC_ENUM_CONVERSION_OPERATOR(PrimitiveMode);

struct InputState 
{
    AttributeList attributes;

    EXPOSE_COPY_FN(InputState)
};

enum class ObjectType : uint32_t 
{
    UNKNOWN,
    SWAPCHAIN,
    BUFFER,
    TEXTURE,
    RENDER_PASS,
    FRAMEBUFFER,
    SAMPLER,
    SHADER,
    DESCRIPTOR_SET_LAYOUT,
    PIPELINE_LAYOUT,
    PIPELINE_STATE,
    DESCRIPTOR_SET,
    INPUT_ASSEMBLER,
    COMMAND_BUFFER,
    QUEUE,
    QUERY_POOL,
    GLOBAL_BARRIER,
    TEXTURE_BARRIER,
    BUFFER_BARRIER,
    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(ObjectType);

}