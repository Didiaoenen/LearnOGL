#pragma once

#include "Def_common.h"

namespace ll
{

class Shader
{
public:
	Shader();
	virtual ~Shader();

	void Initialize(const ShaderInfo& info);
	void Destroy();

    inline const std::string& GetName() const { return _name; }
    inline const ShaderStageList& GetStages() const { return _stages; }
    inline const AttributeList& GetAttributes() const { return _attributes; }
    inline const UniformBlockList& GetBlocks() const { return _blocks; }
    inline const UniformStorageBufferList& GetBuffers() const { return _buffers; }
    inline const UniformSamplerTextureList& GetSamplerTextures() const { return _samplerTextures; }
    inline const UniformSamplerList& GetSamplers() const { return _samplers; }
    inline const UniformTextureList& GetTextures() const { return _textures; }
    inline const UniformStorageImageList& GetImages() const { return _images; }
    inline const UniformInputAttachmentList& GetSubpassInputs() const { return _subpassInputs; }

protected:
    virtual void DoInit(const ShaderInfo& info) = 0;
    virtual void DoDestroy() = 0;

    std::string _name;
    ShaderStageList _stages;
    AttributeList _attributes;
    UniformBlockList _blocks;
    UniformStorageBufferList _buffers;
    UniformSamplerTextureList _samplerTextures;
    UniformSamplerList _samplers;
    UniformTextureList _textures;
    UniformStorageImageList _images;
    UniformInputAttachmentList _subpassInputs;

};

}