#pragma once

#include "RenderCommonTypes.h"

namespace ll
{

enum class DescriptorTypeOrder 
{
    UNIFORM_BUFFER,
    DYNAMIC_UNIFORM_BUFFER,
    SAMPLER_TEXTURE,
    SAMPLER,
    TEXTURE,
    STORAGE_BUFFER,
    DYNAMIC_STORAGE_BUFFER,
    STORAGE_IMAGE,
    INPUT_ATTACHMENT,
};

struct Descriptor 
{
    Descriptor() = default;
    Descriptor(Type typeIn) noexcept
        : type(typeIn) {}

    Type type{ Type::UNKNOWN };
    uint32_t  count{ 1 };
};

struct DescriptorBlockIndex 
{
    DescriptorBlockIndex() = default;
    DescriptorBlockIndex(UpdateFrequency updateFrequencyIn, ParameterType parameterTypeIn, DescriptorTypeOrder descriptorTypeIn, ShaderStageFlagBit visibilityIn) noexcept
        : updateFrequency(updateFrequencyIn),
        parameterType(parameterTypeIn),
        descriptorType(descriptorTypeIn),
        visibility(visibilityIn) {}

    UpdateFrequency         updateFrequency{ UpdateFrequency::PER_INSTANCE };
    ParameterType           parameterType{ ParameterType::CONSTANTS };
    DescriptorTypeOrder     descriptorType{ DescriptorTypeOrder::UNIFORM_BUFFER };
    ShaderStageFlagBit visibility{ ShaderStageFlagBit::NONE };
};

struct DescriptorBlockFlattened 
{
    std::vector<std::string>    descriptorNames;
    std::vector<std::string>    uniformBlockNames;
    std::vector<Descriptor>     descriptors;
    std::vector<UniformBlock>   uniformBlocks;
    uint32_t                    capacity{ 0 };
    uint32_t                    count{ 0 };
};

}