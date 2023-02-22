#include "Define.h"

void ll::LocalDescriptorSetLayoutResizeMaxJoints(uint32_t maxCount)
{
    ll::UBOSkinning::InitLayout(maxCount);
    localDescriptorSetLayout.blocks[ll::UBOSkinning::NAME] = ll::UBOSkinning::layout;
    localDescriptorSetLayout.bindings[ll::UBOSkinning::BINDING] = ll::UBOSkinning::DESCRIPTOR;
}
