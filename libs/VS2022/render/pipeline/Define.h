
#include "Ptr.h"
#include "Def_type.h"
#include "Value.h"
#include "Buffer.h"
#include "RenderFlow.h"

#include <vector>

namespace ll
{

    class Light;
    class Model;

using RenderStageList = std::vector<IntrusivePtr<RenderStage>>;
using RenderFlowList = std::vector<IntrusivePtr<RenderFlow>>;
using RenderObjectList = std::vector<struct RenderObject>;
using LightList = std::vector<Light*>;
using UintList = std::vector<uint32_t>;

const uint32_t CAMERA_DEFAULT_MASK = ~static_cast<uint32_t>(LayerList::UI_2D) & ~static_cast<uint32_t>(LayerList::PROFILER);

enum class RenderFlowType : uint8_t 
{
    SCENE,
    POSTPROCESS,
    UI,
};
CC_ENUM_CONVERSION_OPERATOR(RenderFlowType)

enum class PipelineGlobalBindings
{
    UBO_GLOBAL,
    UBO_CAMERA,
    UBO_SHADOW,
    UBO_CSM,

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

struct DescriptorSetLayoutInfos
{
    DescriptorSetLayoutBindingList bindings;
    std::unordered_map<std::string, UniformBlock> blocks;
    std::unordered_map<std::string, UniformSamplerTexture> samplers;
    std::unordered_map<std::string, UniformStorageImage> storeImages;
};
DescriptorSetLayoutInfos globalDescriptorSetLayout;
DescriptorSetLayoutInfos localDescriptorSetLayout;

extern DescriptorSetLayoutInfos globalDescriptorSetLayout;
extern DescriptorSetLayoutInfos localDescriptorSetLayout;

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

struct RenderObject 
{
    float depth = 0.0F;
    const Model* model = nullptr;
};

static uint32_t globalUBOCount = static_cast<uint32_t>(PipelineGlobalBindings::SAMPLER_SHADOWMAP);
static uint32_t globalSamplerCount = static_cast<uint32_t>(PipelineGlobalBindings::COUNT) - globalUBOCount;

static uint32_t localUBOCount = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_JOINTS);
static uint32_t localSamplerCount = static_cast<uint32_t>(ModelLocalBindings::STORAGE_REFLECTION) - localUBOCount;
static uint32_t localStorageImageCount = static_cast<uint32_t>(ModelLocalBindings::COUNT) - localUBOCount - localSamplerCount;

BindingMappingInfo bindingMappingInfo = 
{
    {globalUBOCount, 0, localUBOCount},
    {globalSamplerCount, 0, localSamplerCount},
    {0, 0, 0},                                 
    {0, 0, 0},                                
    {0, 0, 0},                             
    {0, 0, localStorageImageCount},          
    {0, 0, 0},                               
    {0, 2, 1},                             
};

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

void LocalDescriptorSetLayoutResizeMaxJoints(uint32_t maxCount) 
{
    UBOSkinning::InitLayout(maxCount);
    localDescriptorSetLayout.blocks[UBOSkinning::NAME] = UBOSkinning::layout;
    localDescriptorSetLayout.bindings[UBOSkinning::BINDING] = UBOSkinning::DESCRIPTOR;
}

}