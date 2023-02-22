#pragma once

#include "glObjects.h"

namespace ll
{

    class glDevice;

class CmdBeginRenderPass final : public Cmd 
{
public:
    GPURenderPass* gpuRenderPass = nullptr;
    GPUFramebuffer* gpuFBO = nullptr;
    Rect renderArea;
    Color clearColors[MAX_ATTACHMENTS];
    float clearDepth = 1.0F;
    uint32_t clearStencil = 0;
    uint32_t subpassIdx = 0U;

    CmdBeginRenderPass() : Cmd(CmdType::BEGIN_RENDER_PASS) {}

    void clear() override 
    {
        gpuFBO = nullptr;
        gpuRenderPass = nullptr;
    }
};

class CmdBindStates final : public Cmd 
{
public:
    GPUPipelineState* gpuPipelineState = nullptr;
    GPUInputAssembler* gpuInputAssembler = nullptr;
    std::vector<GPUDescriptorSet*> gpuDescriptorSets;
    std::vector<uint32_t> dynamicOffsets;
    DynamicStates dynamicStates;

    CmdBindStates() : Cmd(CmdType::BIND_STATES) {}

    void clear() override 
    {
        gpuPipelineState = nullptr;
        gpuInputAssembler = nullptr;
        gpuDescriptorSets.clear();
        dynamicOffsets.clear();
    }
};

class CmdDraw final : public Cmd 
{
public:
    DrawInfo drawInfo;

    CmdDraw() : Cmd(CmdType::DRAW) {}
    void clear() override {}
};

class CmdUpdateBuffer final : public Cmd 
{
public:
    GPUBuffer* gpuBuffer = nullptr;
    const uint8_t* buffer = nullptr;
    uint32_t size = 0;
    uint32_t offset = 0;

    CmdUpdateBuffer() : Cmd(CmdType::UPDATE_BUFFER) {}

    void clear() override 
    {
        gpuBuffer = nullptr;
        buffer = nullptr;
    }
};

class CmdCopyBufferToTexture final : public Cmd 
{
public:
    GPUTexture* gpuTexture = nullptr;
    const BufferTextureCopy* regions = nullptr;
    uint32_t count = 0U;
    const uint8_t* const* buffers = nullptr;

    CmdCopyBufferToTexture() : Cmd(CmdType::COPY_BUFFER_TO_TEXTURE) {}

    void clear() override 
    {
        gpuTexture = nullptr;
        regions = nullptr;
        count = 0U;
        buffers = nullptr;
    }
};

class CmdBlitTexture final : public Cmd 
{
public:
    GPUTexture* gpuTextureSrc = nullptr;
    GPUTexture* gpuTextureDst = nullptr;
    const TextureBlit* regions = nullptr;
    uint32_t count = 0U;
    Filter filter = Filter::POINT;

    CmdBlitTexture() : Cmd(CmdType::BLIT_TEXTURE) {}

    void clear() override 
    {
        gpuTextureSrc = nullptr;
        gpuTextureDst = nullptr;
        regions = nullptr;
        count = 0U;
    }
};

struct CmdPackage 
{
    CachedArray<CmdType> cmds;
    CachedArray<CmdBeginRenderPass*> beginRenderPassCmds;
    CachedArray<CmdBindStates*> bindStatesCmds;
    CachedArray<CmdDraw*> drawCmds;
    CachedArray<CmdUpdateBuffer*> updateBufferCmds;
    CachedArray<CmdCopyBufferToTexture*> copyBufferToTextureCmds;
    CachedArray<CmdBlitTexture*> blitTextureCmds;
};

class GPUCommandAllocator final 
{
public:
    CommandPool<CmdBeginRenderPass> beginRenderPassCmdPool;
    CommandPool<CmdBindStates> bindStatesCmdPool;
    CommandPool<CmdDraw> drawCmdPool;
    CommandPool<CmdUpdateBuffer> updateBufferCmdPool;
    CommandPool<CmdCopyBufferToTexture> copyBufferToTextureCmdPool;
    CommandPool<CmdBlitTexture> blitTextureCmdPool;

    void ClearCmds(CmdPackage* cmdPackage) 
    {
        if (cmdPackage->beginRenderPassCmds.size()) 
        {
            beginRenderPassCmdPool.FreeCmds(cmdPackage->beginRenderPassCmds);
        }
        if (cmdPackage->bindStatesCmds.size()) 
        {
            bindStatesCmdPool.FreeCmds(cmdPackage->bindStatesCmds);
        }
        if (cmdPackage->drawCmds.size()) 
        {
            drawCmdPool.FreeCmds(cmdPackage->drawCmds);
        }
        if (cmdPackage->updateBufferCmds.size()) 
        {
            updateBufferCmdPool.FreeCmds(cmdPackage->updateBufferCmds);
        }
        if (cmdPackage->copyBufferToTextureCmds.size()) 
        {
            copyBufferToTextureCmdPool.FreeCmds(cmdPackage->copyBufferToTextureCmds);
        }
        if (cmdPackage->blitTextureCmds.size()) 
        {
            blitTextureCmdPool.FreeCmds(cmdPackage->blitTextureCmds);
        }

        cmdPackage->cmds.clear();
    }

    inline void Reset() 
    {
        beginRenderPassCmdPool.Release();
        bindStatesCmdPool.Release();
        drawCmdPool.Release();
        updateBufferCmdPool.Release();
        copyBufferToTextureCmdPool.Release();
        blitTextureCmdPool.Release();
    }
};

void cmdFuncCreateBuffer(glDevice* device, GPUBuffer* gpuBuffer);
void cmdFuncDestroyBuffer(glDevice* device, GPUBuffer* gpuBuffer);
void cmdFuncResizeBuffer(glDevice* device, GPUBuffer* gpuBuffer);
void cmdFuncCreateTexture(glDevice* device, GPUTexture* gpuTexture);
void cmdFuncDestroyTexture(glDevice* device, GPUTexture* gpuTexture);
void cmdFuncResizeTexture(glDevice* device, GPUTexture* gpuTexture);
void cmdFuncCreateSampler(glDevice* device, GPUSampler* gpuSampler);
void cmdFuncDestroySampler(glDevice* device, GPUSampler* gpuSampler);
void cmdFuncCreateShader(glDevice* device, GPUShader* gpuShader);
void cmdFuncDestroyShader(glDevice* device, GPUShader* gpuShader);
void cmdFuncCreateRenderPass(glDevice* device, GPURenderPass* gpuRenderPass);
void cmdFuncDestroyRenderPass(glDevice* device, GPURenderPass* gpuRenderPass);
void cmdFuncCreateInputAssembler(glDevice* device, GPUInputAssembler* gpuInputAssembler);
void cmdFuncDestroyInputAssembler(glDevice* device, GPUInputAssembler* gpuInputAssembler);
void cmdFuncCreateFramebuffer(glDevice* device, GPUFramebuffer* gpuFBO);
void cmdFuncDestroyFramebuffer(glDevice* device, GPUFramebuffer* gpuFBO);

void cmdFuncBeginRenderPass(glDevice* device, uint32_t subpassIdx,
    GPURenderPass* gpuRenderPass = nullptr,
    GPUFramebuffer* gpuFramebuffer = nullptr,
    const Rect* renderArea = nullptr,
    const Color* clearColors = nullptr,
    float clearDepth = 1.F,
    uint32_t clearStencil = 0);

void cmdFuncEndRenderPass(glDevice* device);

void cmdFuncBindState(glDevice* device,
    GPUPipelineState* gpuPipelineState,
    GPUInputAssembler* gpuInputAssembler,
    const GPUDescriptorSet* const* gpuDescriptorSets,
    const uint32_t* dynamicOffsets = nullptr,
    const DynamicStates* dynamicStates = nullptr);

void cmdFuncDraw(glDevice* device, const DrawInfo& drawInfo);

void cmdFuncUpdateBuffer(glDevice* device,
    GPUBuffer* gpuBuffer,
    const void* buffer,
    uint32_t offset,
    uint32_t size);

void cmdFuncCopyBuffersToTexture(glDevice* device,
    const uint8_t* const* buffers,
    GPUTexture* gpuTexture,
    const BufferTextureCopy* regions,
    uint32_t count);

void cmdFuncCopyTextureToBuffers(glDevice* device,
    GPUTexture* gpuTexture,
    uint8_t* const* buffers,
    const BufferTextureCopy* regions,
    uint32_t count);

void cmdFuncBlitTexture(glDevice* device,
    GPUTexture* gpuTextureSrc,
    GPUTexture* gpuTextureDst,
    const TextureBlit* regions,
    uint32_t count,
    Filter filter);

void cmdFuncExecuteCmds(glDevice* device, CmdPackage* cmdPackage);

}
