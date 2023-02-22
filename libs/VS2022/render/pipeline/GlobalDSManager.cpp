#include "GlobalDSManager.h"

#include "Define.h"

void ll::GlobalDSManager::Activate(Device* device)
{
}

void ll::GlobalDSManager::BindBuffer(uint32_t binding, Buffer* buffer)
{
}

void ll::GlobalDSManager::BindTexture(uint32_t binding, Texture* texture)
{
}

void ll::GlobalDSManager::BindSampler(uint32_t binding, Sampler* sampler)
{
}

void ll::GlobalDSManager::Update()
{
}

ll::DescriptorSet* ll::GlobalDSManager::GetOrCreateDescriptorSet(const Light* light)
{
	return nullptr;
}

void ll::GlobalDSManager::Destroy()
{
}

void ll::GlobalDSManager::SetDescriptorSetLayout()
{
    globalDescriptorSetLayout.bindings.resize(static_cast<size_t>(PipelineGlobalBindings::COUNT));

    globalDescriptorSetLayout.blocks[UBOGlobal::NAME] = UBOGlobal::LAYOUT;
    globalDescriptorSetLayout.bindings[UBOGlobal::BINDING] = UBOGlobal::DESCRIPTOR;
    globalDescriptorSetLayout.blocks[UBOCamera::NAME] = UBOCamera::LAYOUT;
    globalDescriptorSetLayout.bindings[UBOCamera::BINDING] = UBOCamera::DESCRIPTOR;
    globalDescriptorSetLayout.blocks[UBOShadow::NAME] = UBOShadow::LAYOUT;
    globalDescriptorSetLayout.bindings[UBOShadow::BINDING] = UBOShadow::DESCRIPTOR;
    globalDescriptorSetLayout.blocks[UBOCSM::NAME] = UBOCSM::LAYOUT;
    globalDescriptorSetLayout.bindings[UBOCSM::BINDING] = UBOCSM::DESCRIPTOR;
    globalDescriptorSetLayout.samplers[SHADOWMAP::NAME] = SHADOWMAP::LAYOUT;
    globalDescriptorSetLayout.bindings[SHADOWMAP::BINDING] = SHADOWMAP::DESCRIPTOR;
    globalDescriptorSetLayout.samplers[ENVIRONMENT::NAME] = ENVIRONMENT::LAYOUT;
    globalDescriptorSetLayout.bindings[ENVIRONMENT::BINDING] = ENVIRONMENT::DESCRIPTOR;
    globalDescriptorSetLayout.samplers[SPOTSHADOWMAP::NAME] = SPOTSHADOWMAP::LAYOUT;
    globalDescriptorSetLayout.bindings[SPOTSHADOWMAP::BINDING] = SPOTSHADOWMAP::DESCRIPTOR;
    globalDescriptorSetLayout.samplers[DIFFUSEMAP::NAME] = DIFFUSEMAP::LAYOUT;
    globalDescriptorSetLayout.bindings[DIFFUSEMAP::BINDING] = DIFFUSEMAP::DESCRIPTOR;

    localDescriptorSetLayout.bindings.resize(static_cast<size_t>(ModelLocalBindings::COUNT));
    localDescriptorSetLayout.blocks[UBOLocalBatched::NAME] = UBOLocalBatched::LAYOUT;
    localDescriptorSetLayout.bindings[UBOLocalBatched::BINDING] = UBOLocalBatched::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOLocal::NAME] = UBOLocal::LAYOUT;
    localDescriptorSetLayout.bindings[UBOLocal::BINDING] = UBOLocal::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOWorldBound::NAME] = UBOWorldBound::LAYOUT;
    localDescriptorSetLayout.bindings[UBOWorldBound::BINDING] = UBOWorldBound::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOForwardLight::NAME] = UBOForwardLight::LAYOUT;
    localDescriptorSetLayout.bindings[UBOForwardLight::BINDING] = UBOForwardLight::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOSkinningTexture::NAME] = UBOSkinningTexture::LAYOUT;
    localDescriptorSetLayout.bindings[UBOSkinningTexture::BINDING] = UBOSkinningTexture::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOSkinningAnimation::NAME] = UBOSkinningAnimation::LAYOUT;
    localDescriptorSetLayout.bindings[UBOSkinningAnimation::BINDING] = UBOSkinningAnimation::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOSkinning::NAME] = UBOSkinning::layout;
    localDescriptorSetLayout.bindings[UBOSkinning::BINDING] = UBOSkinning::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOMorph::NAME] = UBOMorph::LAYOUT;
    localDescriptorSetLayout.bindings[UBOMorph::BINDING] = UBOMorph::DESCRIPTOR;
    localDescriptorSetLayout.blocks[UBOUILocal::NAME] = UBOUILocal::LAYOUT;
    localDescriptorSetLayout.bindings[UBOUILocal::BINDING] = UBOUILocal::DESCRIPTOR;
    localDescriptorSetLayout.samplers[JOINTTEXTURE::NAME] = JOINTTEXTURE::LAYOUT;
    localDescriptorSetLayout.bindings[JOINTTEXTURE::BINDING] = JOINTTEXTURE::DESCRIPTOR;
    localDescriptorSetLayout.samplers[REALTIMEJOINTTEXTURE::NAME] = REALTIMEJOINTTEXTURE::LAYOUT;
    localDescriptorSetLayout.bindings[REALTIMEJOINTTEXTURE::BINDING] = REALTIMEJOINTTEXTURE::DESCRIPTOR;
    localDescriptorSetLayout.samplers[POSITIONMORPH::NAME] = POSITIONMORPH::LAYOUT;
    localDescriptorSetLayout.bindings[POSITIONMORPH::BINDING] = POSITIONMORPH::DESCRIPTOR;
    localDescriptorSetLayout.samplers[NORMALMORPH::NAME] = NORMALMORPH::LAYOUT;
    localDescriptorSetLayout.bindings[NORMALMORPH::BINDING] = NORMALMORPH::DESCRIPTOR;
    localDescriptorSetLayout.samplers[TANGENTMORPH::NAME] = TANGENTMORPH::LAYOUT;
    localDescriptorSetLayout.bindings[TANGENTMORPH::BINDING] = TANGENTMORPH::DESCRIPTOR;
    localDescriptorSetLayout.samplers[LIGHTMAPTEXTURE::NAME] = LIGHTMAPTEXTURE::LAYOUT;
    localDescriptorSetLayout.bindings[LIGHTMAPTEXTURE::BINDING] = LIGHTMAPTEXTURE::DESCRIPTOR;
    localDescriptorSetLayout.samplers[SPRITETEXTURE::NAME] = SPRITETEXTURE::LAYOUT;
    localDescriptorSetLayout.bindings[SPRITETEXTURE::BINDING] = SPRITETEXTURE::DESCRIPTOR;
    localDescriptorSetLayout.samplers[REFLECTIONTEXTURE::NAME] = REFLECTIONTEXTURE::LAYOUT;
    localDescriptorSetLayout.bindings[REFLECTIONTEXTURE::BINDING] = REFLECTIONTEXTURE::DESCRIPTOR;
    localDescriptorSetLayout.storeImages[REFLECTIONSTORAGE::NAME] = REFLECTIONSTORAGE::LAYOUT;
    localDescriptorSetLayout.bindings[REFLECTIONSTORAGE::BINDING] = REFLECTIONSTORAGE::DESCRIPTOR;
}
