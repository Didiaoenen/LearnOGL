
#include "Ptr.h"
#include "Def_type.h"
#include "Value.h"
#include "Model.h"
#include "Buffer.h"
#include "RenderFlow.h"

#include <vector>

namespace ll
{

using RenderFlowList = std::vector<IntrusivePtr<RenderFlow>>;
using RenderObjectList = std::vector<struct RenderObject>;

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


}