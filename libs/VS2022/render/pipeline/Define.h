
#pragma once

#include "../base/Ptr.h"
#include "../base/Math.h"
#include "../base/Value.h"
#include "../base/Def_type.h"
#include "../base/Def_common.h"

#include <map>
#include <vector>
#include <string>
#include <functional>

namespace ll
{

class Light;
class Model;
class Device;
class RenderFlow;
class RenderStage;

class SkinningJointCapacity 
{
public:
    static uint32_t jointUniformCapacity;
};

constexpr float SHADOW_CAMERA_MAX_FAR = 2000.0F;
const float COEFFICIENT_OF_EXPANSION = 2.0F * sqrtf(3.0F);

struct RenderObject 
{
    float depth = 0.0F;
    const Model* model = nullptr;
};
using RenderObjectList = std::vector<struct RenderObject>;

struct RenderTargetInfo 
{
    uint32_t width = 0;
    uint32_t height = 0;
};

struct RenderPassData
{
    uint32_t priority = 0;
    uint32_t hash = 0;
    float depth = 0.0F;
    uint32_t shaderID = 0;
    uint32_t passIndex = 0;
    //const SubModel* subModel = nullptr;
};
using RenderPassList = std::vector<RenderPassData>;

using ColorDesc = ColorAttachment;
using ColorDescList = std::vector<ColorDesc>;

using DepthStencilDesc = DepthStencilAttachment;

struct RenderPassDesc 
{
    uint32_t index = 0;
    ColorDescList colorAttachments;
    DepthStencilDesc depthStencilAttachment;
};
using RenderPassDescList = std::vector<RenderPassDesc>;

struct RenderTextureDesc 
{
    std::string name;
    TextureType type = TextureType::TEX2D;
    TextureUsage usage = TextureUsage::COLOR_ATTACHMENT;
    Format format = Format::UNKNOWN;
    int width = -1;
    int height = -1;
};
using RenderTextureDescList = std::vector<RenderTextureDesc>;

struct FrameBufferDesc 
{
    std::string name;
    uint32_t renderPass = 0;
    std::vector<std::string> colorTextures;
    std::string depthStencilTexture;
};
using FrameBufferDescList = std::vector<FrameBufferDesc>;

enum class RenderFlowType : uint8_t 
{
    SCENE,
    POSTPROCESS,
    UI,
};
CC_ENUM_CONVERSION_OPERATOR(RenderFlowType)

using RenderStageList = std::vector<IntrusivePtr<RenderStage>>;
using RenderFlowList = std::vector<IntrusivePtr<RenderFlow>>;
using LightList = std::vector<Light*>;
using UintList = std::vector<uint32_t>;

enum class RenderPassStage 
{
    DEFAULT = 100,
    UI = 200,
};
CC_ENUM_CONVERSION_OPERATOR(RenderPassStage)

    struct InternalBindingDesc 
{
    DescriptorType type;
    UniformBlock blockInfo;
    UniformSamplerTexture samplerInfo;
    Value defaultValue;
};

struct InternalBindingInst : public InternalBindingDesc 
{
    Buffer* buffer = nullptr;
    Sampler* sampler = nullptr;
    Texture* texture = nullptr;
};

struct RenderQueueCreateInfo 
{
    bool isTransparent = false;
    uint32_t phases = 0;
    std::function<bool(const RenderPassData& a, const RenderPassData& b)> sortFunc;
};

enum class RenderPriority {
    MIN = 0,
    MAX = 0xff,
    DEFAULT = 0x80,
};
CC_ENUM_CONVERSION_OPERATOR(RenderPriority)

    enum class RenderQueueSortMode 
{
    FRONT_TO_BACK,
    BACK_TO_FRONT,
};
CC_ENUM_CONVERSION_OPERATOR(RenderQueueSortMode)

struct RenderQueueDesc 
{
    bool isTransparent = false;
    RenderQueueSortMode sortMode = RenderQueueSortMode::FRONT_TO_BACK;
    std::vector<std::string> stages;
};
using RenderQueueDescList = std::vector<RenderQueueDesc>;

uint32_t getPhaseID(const std::string& phase);

inline bool OpaqueCompareFn(const RenderPassData& a, const RenderPassData& b)
{
    if (a.hash != b.hash) 
    {
        return a.hash < b.hash;
    }

    if (IsNotEqualF(a.depth, b.depth)) {
        return a.depth < b.depth;
    }

    return a.shaderID < b.shaderID;
}

inline bool TransparentCompareFn(const RenderPassData& a, const RenderPassData& b)
{
    if (a.priority != b.priority) 
    {
        return a.priority < b.priority;
    }

    if (a.hash != b.hash) 
    {
        return a.hash < b.hash;
    }

    if (IsNotEqualF(a.depth, b.depth)) 
    {
        return b.depth < a.depth;
    }

    return a.shaderID < b.shaderID;
}

inline uint32_t ConvertPhase(const std::vector<std::string>& stages) 
{
    uint32_t phase = 0;
    for (const auto& stage : stages) 
    {
        phase |= getPhaseID(stage);
    }
    return phase;
}

using RenderQueueSortFunc = std::function<int(const RenderPassData&, const RenderPassData&)>;

inline RenderQueueSortFunc ConvertQueueSortFunc(const RenderQueueSortMode& mode) 
{
    std::function<int(const RenderPassData&, const RenderPassData&)> sortFunc = OpaqueCompareFn;
    switch (mode) {
    case RenderQueueSortMode::BACK_TO_FRONT:
        sortFunc = TransparentCompareFn;
        break;
    case RenderQueueSortMode::FRONT_TO_BACK:
        sortFunc = OpaqueCompareFn;
        break;
    default:
        break;
    }

    return sortFunc;
}

enum class PipelineGlobalBindings 
{
    UBO_GLOBAL,
    UBO_CAMERA,
    UBO_SHADOW,
    UBO_CSM, // should reserve slot for this optional ubo

    SAMPLER_SHADOWMAP,
    SAMPLER_ENVIRONMENT,
    SAMPLER_SPOT_SHADOW_MAP,
    SAMPLER_DIFFUSEMAP,

    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(PipelineGlobalBindings)

enum class ModelLocalBindings
{
    UBO_LOCAL,
    UBO_FORWARD_LIGHTS,
    UBO_SKINNING_ANIMATION,
    UBO_SKINNING_TEXTURE,
    UBO_MORPH,
    UBO_UI_LOCAL,

    SAMPLER_JOINTS,
    SAMPLER_MORPH_POSITION,
    SAMPLER_MORPH_NORMAL,
    SAMPLER_MORPH_TANGENT,
    SAMPLER_LIGHTMAP,
    SAMPLER_SPRITE,
    SAMPLER_REFLECTION,

    STORAGE_REFLECTION,

    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(ModelLocalBindings)

enum class SetIndex 
{
    GLOBAL,
    MATERIAL,
    LOCAL,
    COUNT,
};
CC_ENUM_CONVERSION_OPERATOR(SetIndex)

extern uint32_t globalSet;
extern uint32_t materialSet;
extern uint32_t localSet;

extern BindingMappingInfo bindingMappingInfo;

struct UBOLocalBatched 
{
    static constexpr uint32_t BATCHING_COUNT = 10;
    static constexpr uint32_t MAT_WORLDS_OFFSET = 0;
    static constexpr uint32_t COUNT = 16 * UBOLocalBatched::BATCHING_COUNT;
    static constexpr uint32_t SIZE = UBOLocalBatched::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_LOCAL);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOLocal 
{
    static constexpr uint32_t MAT_WORLD_OFFSET = 0;
    static constexpr uint32_t MAT_WORLD_IT_OFFSET = UBOLocal::MAT_WORLD_OFFSET + 16;
    static constexpr uint32_t LIGHTINGMAP_UVPARAM = UBOLocal::MAT_WORLD_IT_OFFSET + 16;
    static constexpr uint32_t LOCAL_SHADOW_BIAS = UBOLocal::LIGHTINGMAP_UVPARAM + 4;
    static constexpr uint32_t COUNT = UBOLocal::LOCAL_SHADOW_BIAS + 4;
    static constexpr uint32_t SIZE = UBOLocal::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_LOCAL);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOWorldBound 
{
    static constexpr uint32_t WORLD_BOUND_CENTER = 0;
    static constexpr uint32_t WORLD_BOUND_HALF_EXTENTS = UBOWorldBound::WORLD_BOUND_CENTER + 4;
    static constexpr uint32_t COUNT = UBOWorldBound::WORLD_BOUND_HALF_EXTENTS + 4;
    static constexpr uint32_t SIZE = UBOWorldBound::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_LOCAL);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOForwardLight 
{
    static constexpr uint32_t LIGHTS_PER_PASS = 1;
    static constexpr uint32_t LIGHT_POS_OFFSET = 0;
    static constexpr uint32_t LIGHT_COLOR_OFFSET = UBOForwardLight::LIGHT_POS_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint32_t LIGHT_SIZE_RANGE_ANGLE_OFFSET = UBOForwardLight::LIGHT_COLOR_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint32_t LIGHT_DIR_OFFSET = UBOForwardLight::LIGHT_SIZE_RANGE_ANGLE_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint32_t COUNT = UBOForwardLight::LIGHT_DIR_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint32_t SIZE = UBOForwardLight::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_FORWARD_LIGHTS);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBODeferredLight 
{
    static constexpr uint32_t LIGHTS_PER_PASS = 10;
};

struct UBOSkinningTexture 
{
    static constexpr uint32_t JOINTS_TEXTURE_INFO_OFFSET = 0;
    static constexpr uint32_t COUNT = UBOSkinningTexture::JOINTS_TEXTURE_INFO_OFFSET + 4;
    static constexpr uint32_t SIZE = UBOSkinningTexture::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_SKINNING_TEXTURE);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOSkinningAnimation 
{
    static constexpr uint32_t JOINTS_ANIM_INFO_OFFSET = 0;
    static constexpr uint32_t COUNT = UBOSkinningAnimation::JOINTS_ANIM_INFO_OFFSET + 4;
    static constexpr uint32_t SIZE = UBOSkinningAnimation::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_SKINNING_ANIMATION);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOSkinning 
{
    static uint32_t count;
    static uint32_t size;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_SKINNING_TEXTURE);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static UniformBlock layout;
    static const std::string NAME;
    static void InitLayout(uint32_t capacity);
};

struct UBOMorph 
{
    static constexpr uint32_t MAX_MORPH_TARGET_COUNT = 60;
    static constexpr uint32_t OFFSET_OF_WEIGHTS = 0;
    static constexpr uint32_t OFFSET_OF_DISPLACEMENT_TEXTURE_WIDTH = 4 * MAX_MORPH_TARGET_COUNT;
    static constexpr uint32_t OFFSET_OF_DISPLACEMENT_TEXTURE_HEIGHT = OFFSET_OF_DISPLACEMENT_TEXTURE_WIDTH + 4;
    static constexpr uint32_t OFFSET_OF_VERTICES_COUNT = OFFSET_OF_DISPLACEMENT_TEXTURE_HEIGHT + 4;
    static const uint32_t COUNT_BASE_4_BYTES;
    static const uint32_t SIZE;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_MORPH);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOUILocal 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::UBO_UI_LOCAL);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

enum class ForwardStagePriority 
{
    FORWARD = 10,
    UI = 20
};
CC_ENUM_CONVERSION_OPERATOR(ForwardStagePriority)

enum class ForwardFlowPriority 
{
    SHADOW = 0,
    FORWARD = 1,
    UI = 10,
};
CC_ENUM_CONVERSION_OPERATOR(ForwardFlowPriority)

enum class RenderFlowTag 
{
    SCENE,
    POSTPROCESS,
    UI,
};
CC_ENUM_CONVERSION_OPERATOR(RenderFlowTag)

enum class DeferredStagePriority 
{
    GBUFFER = 10,
    LIGHTING = 15,
    TRANSPARANT = 18,
    BLOOM = 19,
    POSTPROCESS = 20,
    UI = 30
};
CC_ENUM_CONVERSION_OPERATOR(DeferredStagePriority)

enum class DeferredFlowPriority 
{
    SHADOW = 0,
    MAIN = 1,
    UI = 10
};
CC_ENUM_CONVERSION_OPERATOR(DeferredFlowPriority)

struct UBOGlobal 
{
    static constexpr uint32_t TIME_OFFSET = 0;
    static constexpr uint32_t SCREEN_SIZE_OFFSET = UBOGlobal::TIME_OFFSET + 4;
    static constexpr uint32_t NATIVE_SIZE_OFFSET = UBOGlobal::SCREEN_SIZE_OFFSET + 4;

    static constexpr uint32_t DEBUG_VIEW_MODE_OFFSET = UBOGlobal::NATIVE_SIZE_OFFSET + 4;
    static constexpr uint32_t DEBUG_VIEW_COMPOSITE_PACK_1_OFFSET = UBOGlobal::DEBUG_VIEW_MODE_OFFSET + 4;
    static constexpr uint32_t DEBUG_VIEW_COMPOSITE_PACK_2_OFFSET = UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_1_OFFSET + 4;
    static constexpr uint32_t DEBUG_VIEW_COMPOSITE_PACK_3_OFFSET = UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_2_OFFSET + 4;

    static constexpr uint32_t COUNT = UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_3_OFFSET + 4;

    static constexpr uint32_t SIZE = UBOGlobal::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::UBO_GLOBAL);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOCamera 
{
    static constexpr uint32_t MAT_VIEW_OFFSET = 0;
    static constexpr uint32_t MAT_VIEW_INV_OFFSET = UBOCamera::MAT_VIEW_OFFSET + 16;
    static constexpr uint32_t MAT_PROJ_OFFSET = UBOCamera::MAT_VIEW_INV_OFFSET + 16;
    static constexpr uint32_t MAT_PROJ_INV_OFFSET = UBOCamera::MAT_PROJ_OFFSET + 16;
    static constexpr uint32_t MAT_VIEW_PROJ_OFFSET = UBOCamera::MAT_PROJ_INV_OFFSET + 16;
    static constexpr uint32_t MAT_VIEW_PROJ_INV_OFFSET = UBOCamera::MAT_VIEW_PROJ_OFFSET + 16;
    static constexpr uint32_t CAMERA_POS_OFFSET = UBOCamera::MAT_VIEW_PROJ_INV_OFFSET + 16;
    static constexpr uint32_t SURFACE_TRANSFORM_OFFSET = UBOCamera::CAMERA_POS_OFFSET + 4;
    static constexpr uint32_t SCREEN_SCALE_OFFSET = UBOCamera::SURFACE_TRANSFORM_OFFSET + 4;
    static constexpr uint32_t EXPOSURE_OFFSET = UBOCamera::SCREEN_SCALE_OFFSET + 4;
    static constexpr uint32_t MAIN_LIT_DIR_OFFSET = UBOCamera::EXPOSURE_OFFSET + 4;
    static constexpr uint32_t MAIN_LIT_COLOR_OFFSET = UBOCamera::MAIN_LIT_DIR_OFFSET + 4;
    static constexpr uint32_t AMBIENT_SKY_OFFSET = UBOCamera::MAIN_LIT_COLOR_OFFSET + 4;
    static constexpr uint32_t AMBIENT_GROUND_OFFSET = UBOCamera::AMBIENT_SKY_OFFSET + 4;
    static constexpr uint32_t GLOBAL_FOG_COLOR_OFFSET = UBOCamera::AMBIENT_GROUND_OFFSET + 4;
    static constexpr uint32_t GLOBAL_FOG_BASE_OFFSET = UBOCamera::GLOBAL_FOG_COLOR_OFFSET + 4;
    static constexpr uint32_t GLOBAL_FOG_ADD_OFFSET = UBOCamera::GLOBAL_FOG_BASE_OFFSET + 4;
    static constexpr uint32_t GLOBAL_NEAR_FAR_OFFSET = UBOCamera::GLOBAL_FOG_ADD_OFFSET + 4;
    static constexpr uint32_t GLOBAL_VIEW_PORT_OFFSET = UBOCamera::GLOBAL_NEAR_FAR_OFFSET + 4;
    static constexpr uint32_t COUNT = UBOCamera::GLOBAL_VIEW_PORT_OFFSET + 4;
    static constexpr uint32_t SIZE = UBOCamera::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::UBO_CAMERA);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOShadow 
{
    static constexpr uint32_t MAT_LIGHT_VIEW_OFFSET = 0;
    static constexpr uint32_t MAT_LIGHT_VIEW_PROJ_OFFSET = UBOShadow::MAT_LIGHT_VIEW_OFFSET + 16;
    static constexpr uint32_t SHADOW_INV_PROJ_DEPTH_INFO_OFFSET = UBOShadow::MAT_LIGHT_VIEW_PROJ_OFFSET + 16;
    static constexpr uint32_t SHADOW_PROJ_DEPTH_INFO_OFFSET = UBOShadow::SHADOW_INV_PROJ_DEPTH_INFO_OFFSET + 4;
    static constexpr uint32_t SHADOW_PROJ_INFO_OFFSET = UBOShadow::SHADOW_PROJ_DEPTH_INFO_OFFSET + 4;
    static constexpr uint32_t SHADOW_NEAR_FAR_LINEAR_SATURATION_INFO_OFFSET = UBOShadow::SHADOW_PROJ_INFO_OFFSET + 4;
    static constexpr uint32_t SHADOW_WIDTH_HEIGHT_PCF_BIAS_INFO_OFFSET = UBOShadow::SHADOW_NEAR_FAR_LINEAR_SATURATION_INFO_OFFSET + 4;
    static constexpr uint32_t SHADOW_LIGHT_PACKING_NBIAS_NULL_INFO_OFFSET = UBOShadow::SHADOW_WIDTH_HEIGHT_PCF_BIAS_INFO_OFFSET + 4;
    static constexpr uint32_t SHADOW_COLOR_OFFSET = UBOShadow::SHADOW_LIGHT_PACKING_NBIAS_NULL_INFO_OFFSET + 4;
    static constexpr uint32_t PLANAR_NORMAL_DISTANCE_INFO_OFFSET = UBOShadow::SHADOW_COLOR_OFFSET + 4;
    static constexpr uint32_t COUNT = UBOShadow::PLANAR_NORMAL_DISTANCE_INFO_OFFSET + 4;
    static constexpr uint32_t SIZE = UBOShadow::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::UBO_SHADOW);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct UBOCSM 
{
    static constexpr uint32_t CSM_LEVEL_COUNT = 4;
    static constexpr uint32_t CSM_VIEW_DIR_0_OFFSET = 0;
    static constexpr uint32_t CSM_VIEW_DIR_1_OFFSET = UBOCSM::CSM_VIEW_DIR_0_OFFSET + 4 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t CSM_VIEW_DIR_2_OFFSET = UBOCSM::CSM_VIEW_DIR_1_OFFSET + 4 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t CSM_ATLAS_OFFSET = UBOCSM::CSM_VIEW_DIR_2_OFFSET + 4 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t MAT_CSM_VIEW_PROJ_LEVELS_OFFSET = UBOCSM::CSM_ATLAS_OFFSET + 4 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t CSM_PROJ_DEPTH_INFO_LEVELS_OFFSET = UBOCSM::MAT_CSM_VIEW_PROJ_LEVELS_OFFSET + 16 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t CSM_PROJ_INFO_LEVELS_OFFSET = UBOCSM::CSM_PROJ_DEPTH_INFO_LEVELS_OFFSET + 4 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t CSM_SPLITS_INFO_OFFSET = UBOCSM::CSM_PROJ_INFO_LEVELS_OFFSET + 4 * UBOCSM::CSM_LEVEL_COUNT;
    static constexpr uint32_t COUNT = UBOCSM::CSM_SPLITS_INFO_OFFSET + 4;
    static constexpr uint32_t SIZE = UBOCSM::COUNT * 4;
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::UBO_CSM);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformBlock LAYOUT;
    static const std::string NAME;
};

struct DescriptorSetLayoutInfos 
{
    DescriptorSetLayoutBindingList bindings;
    std::unordered_map<std::string, UniformBlock> blocks;
    std::unordered_map<std::string, UniformSamplerTexture> samplers;
    std::unordered_map<std::string, UniformStorageImage> storeImages;
};
extern DescriptorSetLayoutInfos globalDescriptorSetLayout;
extern DescriptorSetLayoutInfos localDescriptorSetLayout;

enum class LayerList : uint32_t 
{
    NONE = 0,
    IGNORE_RAYCAST = (1 << 20),
    GIZMOS = (1 << 21),
    EDITOR = (1 << 22),
    UI_3D = (1 << 23),
    SCENE_GIZMO = (1 << 24),
    UI_2D = (1 << 25),

    PROFILER = (1 << 28),
    DEFAULT = (1 << 30),
    ALL = 0xffffffff,
};
CC_ENUM_CONVERSION_OPERATOR(LayerList)

const uint32_t CAMERA_DEFAULT_MASK = ~static_cast<uint32_t>(LayerList::UI_2D) & ~static_cast<uint32_t>(LayerList::PROFILER);

uint32_t nextPow2(uint32_t val);

bool supportsR16HalfFloatTexture(const Device* device);

bool supportsR32FloatTexture(const Device* device);

extern uint32_t skyboxFlag;

struct SHADOWMAP 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::SAMPLER_SHADOWMAP);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct ENVIRONMENT 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::SAMPLER_ENVIRONMENT);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct SPOTSHADOWMAP 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::SAMPLER_SPOT_SHADOW_MAP);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct DIFFUSEMAP 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(PipelineGlobalBindings::SAMPLER_DIFFUSEMAP);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct JOINTTEXTURE 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_JOINTS);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct REALTIMEJOINTTEXTURE 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_JOINTS);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct POSITIONMORPH 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_MORPH_POSITION);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct NORMALMORPH 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_MORPH_NORMAL);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct TANGENTMORPH 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_MORPH_TANGENT);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct LIGHTMAPTEXTURE 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_LIGHTMAP);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct SPRITETEXTURE 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_SPRITE);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct REFLECTIONTEXTURE 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_REFLECTION);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformSamplerTexture LAYOUT;
    static const std::string NAME;
};

struct REFLECTIONSTORAGE 
{
    static constexpr uint32_t BINDING = static_cast<uint32_t>(ModelLocalBindings::STORAGE_REFLECTION);
    static const DescriptorSetLayoutBinding DESCRIPTOR;
    static const UniformStorageImage LAYOUT;
    static const std::string NAME;
};

static constexpr uint32_t CLUSTER_LIGHT_BINDING = 4;
static constexpr uint32_t CLUSTER_LIGHT_INDEX_BINDING = 5;
static constexpr uint32_t CLUSTER_LIGHT_GRID_BINDING = 6;

void LocalDescriptorSetLayoutResizeMaxJoints(uint32_t maxCount);

}