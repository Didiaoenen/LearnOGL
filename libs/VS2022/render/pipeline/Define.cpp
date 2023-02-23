#include "Define.h"

#include "../base/Device.h"

#include <string>

namespace ll
{

static uint32_t globalUBOCount = static_cast<uint32_t>(PipelineGlobalBindings::SAMPLER_SHADOWMAP);
static uint32_t globalSamplerCount = static_cast<uint32_t>(PipelineGlobalBindings::COUNT) - globalUBOCount;

static uint32_t localUBOCount = static_cast<uint32_t>(ModelLocalBindings::SAMPLER_JOINTS);
static uint32_t localSamplerCount = static_cast<uint32_t>(ModelLocalBindings::STORAGE_REFLECTION) - localUBOCount;
static uint32_t localStorageImageCount = static_cast<uint32_t>(ModelLocalBindings::COUNT) - localUBOCount - localSamplerCount;

uint32_t globalSet = static_cast<uint32_t>(SetIndex::GLOBAL);
uint32_t materialSet = static_cast<uint32_t>(SetIndex::MATERIAL);
uint32_t localSet = static_cast<uint32_t>(SetIndex::LOCAL);

BindingMappingInfo bindingMappingInfo = 
{
    {globalUBOCount, 0, localUBOCount},         // Uniform Buffer Counts
    {globalSamplerCount, 0, localSamplerCount}, // Combined Sampler Texture Counts
    {0, 0, 0},                                  // Sampler Counts
    {0, 0, 0},                                  // Texture Counts
    {0, 0, 0},                                  // Storage Buffer Counts
    {0, 0, localStorageImageCount},             // Storage Image Counts
    {0, 0, 0},                                  // Subpass Input Counts
    {0, 2, 1},                                  // Set Order Indices
};

DescriptorSetLayoutInfos globalDescriptorSetLayout;
DescriptorSetLayoutInfos localDescriptorSetLayout;
const std::string UBOGlobal::NAME = "CCGlobal";
const DescriptorSetLayoutBinding UBOGlobal::DESCRIPTOR = {
    UBOGlobal::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::ALL,
    {},
};

const UniformBlock UBOGlobal::LAYOUT = 
{
    globalSet,
    UBOGlobal::BINDING,
    UBOGlobal::NAME,
    //{
    //    {"cc_time", Type::FLOAT4, 1},
    //    {"cc_screenSize", Type::FLOAT4, 1},
    //    {"cc_nativeSize", Type::FLOAT4, 1},

    //    {"cc_debug_view_mode", Type::FLOAT, 4},
    //    {"cc_debug_view_composite_pack_1", Type::FLOAT, 4},
    //    {"cc_debug_view_composite_pack_2", Type::FLOAT, 4},
    //    {"cc_debug_view_composite_pack_3", Type::FLOAT, 4},
    //},
    UniformList(),
    1,
};

const std::string UBOLocalBatched::NAME = "CCLocalBatched";
const DescriptorSetLayoutBinding UBOLocalBatched::DESCRIPTOR = 
{
    UBOLocalBatched::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};
const UniformBlock UBOLocalBatched::LAYOUT = 
{
    localSet,
    UBOLocalBatched::BINDING,
    UBOLocalBatched::NAME,
    //{
    //    {"cc_matWorlds", Type::MAT4, static_cast<uint32_t>(UBOLocalBatched::BATCHING_COUNT)},
    //},
    UniformList(),
    1,
};

const std::string UBOCamera::NAME = "CCCamera";
const DescriptorSetLayoutBinding UBOCamera::DESCRIPTOR = 
{
    UBOCamera::BINDING,
    DescriptorType::DYNAMIC_UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::ALL,
    {},
};

const UniformBlock UBOCamera::LAYOUT = 
{
    globalSet,
    UBOCamera::BINDING,
    UBOCamera::NAME,
    //{
    //    {"cc_matView", Type::MAT4, 1},
    //    {"cc_matViewInv", Type::MAT4, 1},
    //    {"cc_matProj", Type::MAT4, 1},
    //    {"cc_matProjInv", Type::MAT4, 1},
    //    {"cc_matViewProj", Type::MAT4, 1},
    //    {"cc_matViewProjInv", Type::MAT4, 1},
    //    {"cc_cameraPos", Type::FLOAT4, 1},
    //    {"cc_surfaceTransform", Type::FLOAT4, 1},
    //    {"cc_screenScale", Type::FLOAT4, 1},
    //    {"cc_exposure", Type::FLOAT4, 1},
    //    {"cc_mainLitDir", Type::FLOAT4, 1},
    //    {"cc_mainLitColor", Type::FLOAT4, 1},
    //    {"cc_ambientSky", Type::FLOAT4, 1},
    //    {"cc_ambientGround", Type::FLOAT4, 1},
    //    {"cc_fogColor", Type::FLOAT4, 1},
    //    {"cc_fogBase", Type::FLOAT4, 1},
    //    {"cc_fogAdd", Type::FLOAT4, 1},
    //    {"cc_nearFar", Type::FLOAT4, 1},
    //    {"cc_viewPort", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOShadow::NAME = "CCShadow";
const DescriptorSetLayoutBinding UBOShadow::DESCRIPTOR = 
{
    UBOShadow::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::ALL,
    {},
};

const UniformBlock UBOShadow::LAYOUT = 
{
    globalSet,
    UBOShadow::BINDING,
    UBOShadow::NAME,
    //{
    //    {"cc_matLightView", Type::MAT4, 1},
    //    {"cc_matLightViewProj", Type::MAT4, 1},
    //    {"cc_shadowInvProjDepthInfo", Type::FLOAT4, 1},
    //    {"cc_shadowProjDepthInfo", Type::FLOAT4, 1},
    //    {"cc_shadowProjInfo", Type::FLOAT4, 1},
    //    {"cc_shadowNFLSInfo", Type::FLOAT4, 1},
    //    {"cc_shadowWHPBInfo", Type::FLOAT4, 1},
    //    {"cc_shadowLPNNInfo", Type::FLOAT4, 1},
    //    {"cc_shadowColor", Type::FLOAT4, 1},
    //    {"cc_planarNDInfo", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOCSM::NAME = "CCCSM";
const DescriptorSetLayoutBinding UBOCSM::DESCRIPTOR = 
{
    UBOCSM::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::ALL,
    {},
};

const UniformBlock UBOCSM::LAYOUT = 
{
    globalSet,
    UBOCSM::BINDING,
    UBOCSM::NAME,
    //{
    //    {"cc_csmViewDir0", Type::FLOAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_csmViewDir1", Type::FLOAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_csmViewDir2", Type::FLOAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_csmAtlas", Type::FLOAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_matCSMViewProj", Type::MAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_csmProjDepthInfo", Type::FLOAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_csmProjInfo", Type::FLOAT4, UBOCSM::CSM_LEVEL_COUNT},
    //    {"cc_csmSplitsInfo", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOLocal::NAME = "CCLocal";
const DescriptorSetLayoutBinding UBOLocal::DESCRIPTOR = 
{
    UBOLocal::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX | ShaderStageFlagBit::COMPUTE,
    {},
};

const UniformBlock UBOLocal::LAYOUT = 
{
    localSet,
    UBOLocal::BINDING,
    UBOLocal::NAME,
    //{
    //    {"cc_matWorld", Type::MAT4, 1},
    //    {"cc_matWorldIT", Type::MAT4, 1},
    //    {"cc_lightingMapUVParam", Type::FLOAT4, 1},
    //    {"cc_localShadowBias", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOWorldBound::NAME = "CCWorldBound";
const DescriptorSetLayoutBinding UBOWorldBound::DESCRIPTOR = 
{
    UBOWorldBound::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX | ShaderStageFlagBit::COMPUTE,
    {},
};

const UniformBlock UBOWorldBound::LAYOUT = 
{
    localSet,
    UBOWorldBound::BINDING,
    UBOWorldBound::NAME,
    //{
    //    {"cc_worldBoundCenter", Type::FLOAT4, 1},
    //    {"cc_worldBoundHalfExtents", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOForwardLight::NAME = "CCForwardLight";
const DescriptorSetLayoutBinding UBOForwardLight::DESCRIPTOR = 
{
    UBOForwardLight::BINDING,
    DescriptorType::DYNAMIC_UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformBlock UBOForwardLight::LAYOUT = 
{
    localSet,
    UBOForwardLight::BINDING,
    UBOForwardLight::NAME,
    //{
    //    {"cc_lightPos", Type::FLOAT4, static_cast<uint32_t>(UBOForwardLight::LIGHTS_PER_PASS)},
    //    {"cc_lightColor", Type::FLOAT4, static_cast<uint32_t>(UBOForwardLight::LIGHTS_PER_PASS)},
    //    {"cc_lightSizeRangeAngle", Type::FLOAT4, static_cast<uint32_t>(UBOForwardLight::LIGHTS_PER_PASS)},
    //    {"cc_lightDir", Type::FLOAT4, static_cast<uint32_t>(UBOForwardLight::LIGHTS_PER_PASS)},
    //},
    UniformList(),
    1,
};

const std::string UBOSkinningTexture::NAME = "CCSkinningTexture";
const DescriptorSetLayoutBinding UBOSkinningTexture::DESCRIPTOR = 
{
    UBOSkinningTexture::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformBlock UBOSkinningTexture::LAYOUT = 
{
    localSet,
    UBOSkinningTexture::BINDING,
    UBOSkinningTexture::NAME,
    //{
    //    {"cc_jointTextureInfo", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOSkinningAnimation::NAME = "CCSkinningAnimation";
const DescriptorSetLayoutBinding UBOSkinningAnimation::DESCRIPTOR = 
{
    UBOSkinningAnimation::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformBlock UBOSkinningAnimation::LAYOUT = 
{
    localSet,
    UBOSkinningAnimation::BINDING,
    UBOSkinningAnimation::NAME,
    //{
    //    {"cc_jointAnimInfo", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

uint32_t SkinningJointCapacity::jointUniformCapacity = 0;
uint32_t UBOSkinning::count = 0;
uint32_t UBOSkinning::size = 0;
const std::string UBOSkinning::NAME = "CCSkinning";
const DescriptorSetLayoutBinding UBOSkinning::DESCRIPTOR = 
{
    UBOSkinning::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

UniformBlock UBOSkinning::layout = 
{
    localSet,
    UBOSkinning::BINDING,
    UBOSkinning::NAME,
    //{
    //    {"cc_joints", Type::FLOAT4, 0},
    //},
    UniformList(),
    1,
};

void UBOSkinning::InitLayout(uint32_t capacity) 
{
    UBOSkinning::count = capacity * 12;
    UBOSkinning::size = UBOSkinning::count * sizeof(float);
    UBOSkinning::layout.members[0].count = capacity * 3;
}

const uint32_t UBOMorph::COUNT_BASE_4_BYTES = static_cast<uint32_t>(4 * std::ceil(UBOMorph::MAX_MORPH_TARGET_COUNT / 4) + 4);
const uint32_t UBOMorph::SIZE = UBOMorph::COUNT_BASE_4_BYTES * 4;
const std::string UBOMorph::NAME = "CCMorph";
const DescriptorSetLayoutBinding UBOMorph::DESCRIPTOR = 
{
    UBOMorph::BINDING,
    DescriptorType::UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformBlock UBOMorph::LAYOUT = 
{
    localSet,
    UBOMorph::BINDING,
    UBOMorph::NAME,
    //{
    //    {"cc_displacementWeights", Type::FLOAT4, static_cast<uint32_t>(UBOMorph::MAX_MORPH_TARGET_COUNT / 4)},
    //    {"cc_displacementTextureInfo", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string UBOUILocal::NAME = "CCUILocal";
const DescriptorSetLayoutBinding UBOUILocal::DESCRIPTOR = 
{
    UBOUILocal::BINDING,
    DescriptorType::DYNAMIC_UNIFORM_BUFFER,
    1,
    ShaderStageFlagBit::VERTEX,
};

const UniformBlock UBOUILocal::LAYOUT = 
{
    localSet,
    UBOUILocal::BINDING,
    UBOUILocal::NAME,
    //{
    //    {"cc_local_data", Type::FLOAT4, 1},
    //},
    UniformList(),
    1,
};

const std::string SHADOWMAP::NAME = "cc_shadowMap";
const DescriptorSetLayoutBinding SHADOWMAP::DESCRIPTOR = 
{
    SHADOWMAP::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture SHADOWMAP::LAYOUT = 
{
    globalSet,
    SHADOWMAP::BINDING,
    SHADOWMAP::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string ENVIRONMENT::NAME = "cc_environment";
const DescriptorSetLayoutBinding ENVIRONMENT::DESCRIPTOR = 
{
    ENVIRONMENT::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture ENVIRONMENT::LAYOUT = 
{
    globalSet,
    ENVIRONMENT::BINDING,
    ENVIRONMENT::NAME,
    Type::SAMPLER_CUBE,
    1,
};

const std::string SPOTSHADOWMAP::NAME = "cc_spotShadowMap";
const DescriptorSetLayoutBinding SPOTSHADOWMAP::DESCRIPTOR = 
{
    SPOTSHADOWMAP::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture SPOTSHADOWMAP::LAYOUT = 
{
    globalSet,
    SPOTSHADOWMAP::BINDING,
    SPOTSHADOWMAP::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string DIFFUSEMAP::NAME = "cc_diffuseMap";
const DescriptorSetLayoutBinding DIFFUSEMAP::DESCRIPTOR = 
{
    DIFFUSEMAP::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture DIFFUSEMAP::LAYOUT = 
{
    globalSet,
    DIFFUSEMAP::BINDING,
    DIFFUSEMAP::NAME,
    Type::SAMPLER_CUBE,
    1,
};

const std::string JOINTTEXTURE::NAME = "cc_jointTexture";
const DescriptorSetLayoutBinding JOINTTEXTURE::DESCRIPTOR = 
{
    JOINTTEXTURE::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformSamplerTexture JOINTTEXTURE::LAYOUT = 
{
    localSet,
    JOINTTEXTURE::BINDING,
    JOINTTEXTURE::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string REALTIMEJOINTTEXTURE::NAME = "cc_realtimeJoint";
const DescriptorSetLayoutBinding REALTIMEJOINTTEXTURE::DESCRIPTOR = 
{
    REALTIMEJOINTTEXTURE::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformSamplerTexture REALTIMEJOINTTEXTURE::LAYOUT = 
{
    localSet,
    REALTIMEJOINTTEXTURE::BINDING,
    REALTIMEJOINTTEXTURE::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string POSITIONMORPH::NAME = "cc_PositionDisplacements";
const DescriptorSetLayoutBinding POSITIONMORPH::DESCRIPTOR = 
{
    POSITIONMORPH::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformSamplerTexture POSITIONMORPH::LAYOUT = 
{
    localSet,
    POSITIONMORPH::BINDING,
    POSITIONMORPH::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string NORMALMORPH::NAME = "cc_NormalDisplacements";
const DescriptorSetLayoutBinding NORMALMORPH::DESCRIPTOR = 
{
    NORMALMORPH::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformSamplerTexture NORMALMORPH::LAYOUT = 
{
    localSet,
    NORMALMORPH::BINDING,
    NORMALMORPH::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string TANGENTMORPH::NAME = "cc_TangentDisplacements";
const DescriptorSetLayoutBinding TANGENTMORPH::DESCRIPTOR = 
{
    TANGENTMORPH::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::VERTEX,
    {},
};

const UniformSamplerTexture TANGENTMORPH::LAYOUT = 
{
    localSet,
    TANGENTMORPH::BINDING,
    TANGENTMORPH::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string LIGHTMAPTEXTURE::NAME = "cc_lightingMap";
const DescriptorSetLayoutBinding LIGHTMAPTEXTURE::DESCRIPTOR = 
{
    LIGHTMAPTEXTURE::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture LIGHTMAPTEXTURE::LAYOUT = 
{
    localSet,
    LIGHTMAPTEXTURE::BINDING,
    LIGHTMAPTEXTURE::NAME,
    Type::SAMPLER2D,
    1,
};

const std::string SPRITETEXTURE::NAME = "cc_spriteTexture";
const DescriptorSetLayoutBinding SPRITETEXTURE::DESCRIPTOR = 
{
    SPRITETEXTURE::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture SPRITETEXTURE::LAYOUT = 
{
    localSet,
    static_cast<uint32_t>(ModelLocalBindings::SAMPLER_SPRITE),
    "cc_spriteTexture",
    Type::SAMPLER2D,
    1,
};

const std::string REFLECTIONTEXTURE::NAME = "cc_reflectionTexture";
const DescriptorSetLayoutBinding REFLECTIONTEXTURE::DESCRIPTOR = 
{
    REFLECTIONTEXTURE::BINDING,
    DescriptorType::SAMPLER_TEXTURE,
    1,
    ShaderStageFlagBit::FRAGMENT,
    {},
};

const UniformSamplerTexture REFLECTIONTEXTURE::LAYOUT = 
{
    localSet,
    static_cast<uint32_t>(ModelLocalBindings::SAMPLER_REFLECTION),
    "cc_reflectionTexture",
    Type::SAMPLER2D,
    1,
};

const std::string REFLECTIONSTORAGE::NAME = "cc_reflectionStorage";
const DescriptorSetLayoutBinding REFLECTIONSTORAGE::DESCRIPTOR = 
{
    REFLECTIONSTORAGE::BINDING,
    DescriptorType::STORAGE_IMAGE,
    1,
    ShaderStageFlagBit::COMPUTE,
    {},
};

const UniformStorageImage REFLECTIONSTORAGE::LAYOUT = 
{
    localSet,
    static_cast<uint32_t>(ModelLocalBindings::STORAGE_REFLECTION),
    "cc_reflectionStorage",
    Type::IMAGE2D,
    1,
};

uint32_t skyboxFlag = static_cast<uint32_t>(ClearFlagBit::STENCIL) << 1;

uint32_t nextPow2(uint32_t val) 
{
    --val;
    val |= (val >> 1);
    val |= (val >> 2);
    val |= (val >> 4);
    val |= (val >> 8);
    val |= (val >> 16);
    ++val;
    return val;
}

bool supportsR16HalfFloatTexture(const Device* device) 
{
    return hasAllFlags(device->GetFormatFeatures(Format::R16F), FormatFeature::RENDER_TARGET | FormatFeature::SAMPLED_TEXTURE);
}

bool supportsR32FloatTexture(const Device* device) 
{
    return hasAllFlags(device->GetFormatFeatures(Format::R32F), FormatFeature::RENDER_TARGET | FormatFeature::SAMPLED_TEXTURE);
}

static std::unordered_map<std::string, uint32_t> phases; //cjh how to clear this global variable when exiting game?
static uint32_t phaseNum = 0;

uint32_t getPhaseID(const std::string& phaseName) 
{
    const auto iter = phases.find(phaseName);
    if (iter == phases.end()) 
    {
        phases.emplace(phaseName, 1 << phaseNum);
        ++phaseNum;
    }
    return phases.at(phaseName);
}

void LocalDescriptorSetLayoutResizeMaxJoints(uint32_t maxCount) 
{
    UBOSkinning::InitLayout(maxCount);
    localDescriptorSetLayout.blocks[UBOSkinning::NAME] = UBOSkinning::layout;
    localDescriptorSetLayout.bindings[UBOSkinning::BINDING] = UBOSkinning::DESCRIPTOR;
}

}