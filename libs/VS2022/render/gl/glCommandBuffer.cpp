#include "glCommandBuffer.h"

#include "../base/Math.h"
#include "../common/CommandPool.h"

#include "glBuffer.h"
#include "glDevice.h"
#include "glTexture.h"
#include "glCommands.h"
#include "glRenderPass.h"
#include "glFrameBuffer.h"
#include "glDescriptorSet.h"
#include "glPipelineState.h"
#include "glInputAssembler.h"
#include "glWrangler.h"

#include <glm/glm.hpp>

ll::glCommandBuffer::glCommandBuffer()
{
}

ll::glCommandBuffer::~glCommandBuffer()
{
}

void ll::glCommandBuffer::Begin(RenderPass* renderPass, uint32_t subpass, FrameBuffer* frameBuffer)
{
    _cmdAllocator->ClearCmds(_curCmdPackage);
    _curGPUPipelineState = nullptr;
    _curGPUInputAssember = nullptr;
    _curGPUDescriptorSets.assign(_curGPUDescriptorSets.size(), nullptr);

    _numDrawCalls = 0;
    _numInstances = 0;
    _numTriangles = 0;
}

void ll::glCommandBuffer::End()
{
    if (_isStateInvalid) 
    {
        BindStates();
    }

    _pendingPackages.push(_curCmdPackage);
    if (!_freePackages.empty()) 
    {
        _curCmdPackage = _freePackages.front();
        _freePackages.pop();
    }
    else 
    {
        _curCmdPackage = new CmdPackage;
    }
}

void ll::glCommandBuffer::BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil, CommandBuffer* const* secondaryCBs, uint32_t secondaryCBCount)
{
    _curSubpassIdx = 0U;

    CmdBeginRenderPass* cmd = _cmdAllocator->beginRenderPassCmdPool.Alloc();
    cmd->subpassIdx = _curSubpassIdx;
    cmd->gpuRenderPass = static_cast<glRenderPass*>(renderPass)->GpuRenderPass();
    cmd->gpuFBO = static_cast<glFrameBuffer*>(fbo)->GpuFBO();
    cmd->renderArea = renderArea;
    size_t numClearColors = cmd->gpuRenderPass->colorAttachments.size();
    memcpy(cmd->clearColors, colors, numClearColors * sizeof(Color));
    cmd->clearDepth = depth;
    cmd->clearStencil = stencil;
    _curCmdPackage->beginRenderPassCmds.push(cmd);
    _curCmdPackage->cmds.push(CmdType::BEGIN_RENDER_PASS);
    _curDynamicStates.viewport = { renderArea.x, renderArea.y, renderArea.width, renderArea.height };
    _curDynamicStates.scissor = renderArea;
}

void ll::glCommandBuffer::EndRenderPass()
{
    _curCmdPackage->cmds.push(CmdType::END_RENDER_PASS);
}

void ll::glCommandBuffer::BindPipelineState(PipelineState* pso)
{
    GPUPipelineState* gpuPipelineState = static_cast<glPipelineState*>(pso)->GpuPipelineState();
    if (_curGPUPipelineState != gpuPipelineState) 
    {
        _curGPUPipelineState = gpuPipelineState;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet, uint32_t dynamicOffsetCount, const uint32_t* dynamicOffsets)
{
    GPUDescriptorSet* gpuDescriptorSet = static_cast<glDescriptorSet*>(descriptorSet)->GpuDescriptorSet();
    if (_curGPUDescriptorSets[set] != gpuDescriptorSet) 
    {
        _curGPUDescriptorSets[set] = gpuDescriptorSet;
        _isStateInvalid = true;
    }
    if (dynamicOffsetCount) 
    {
        _curDynamicOffsets[set].assign(dynamicOffsets, dynamicOffsets + dynamicOffsetCount);
        _isStateInvalid = true;
    }
    else if (!_curDynamicOffsets[set].empty()) 
    {
        _curDynamicOffsets[set].assign(_curDynamicOffsets[set].size(), 0);
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::BindInputAssembler(InputAssembler* ia)
{
    _curGPUInputAssember = static_cast<glInputAssembler*>(ia)->GpuInputAssembler();
    _isStateInvalid = true;
}

void ll::glCommandBuffer::SetViewport(const Viewport& vp)
{
    if ((_curDynamicStates.viewport.left != vp.left) ||
        (_curDynamicStates.viewport.top != vp.top) ||
        (_curDynamicStates.viewport.width != vp.width) ||
        (_curDynamicStates.viewport.height != vp.height) ||
        IsNotEqualF(_curDynamicStates.viewport.minDepth, vp.minDepth) ||
        IsNotEqualF(_curDynamicStates.viewport.maxDepth, vp.maxDepth))
    {
        _curDynamicStates.viewport = vp;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::SetScissor(const Rect& rect)
{
    if ((_curDynamicStates.scissor.x != rect.x) ||
        (_curDynamicStates.scissor.y != rect.y) ||
        (_curDynamicStates.scissor.width != rect.width) ||
        (_curDynamicStates.scissor.height != rect.height)) 
    {
        _curDynamicStates.scissor = rect;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::SetLineWidth(float width)
{
    if (IsNotEqualF(_curDynamicStates.lineWidth, width))
    {
        _curDynamicStates.lineWidth = width;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::SetDepthBias(float constant, float clamp, float slope)
{
    if (IsNotEqualF(_curDynamicStates.depthBiasConstant, constant) ||
        IsNotEqualF(_curDynamicStates.depthBiasClamp, clamp) ||
        IsNotEqualF(_curDynamicStates.depthBiasSlope, slope))
    {
        _curDynamicStates.depthBiasConstant = constant;
        _curDynamicStates.depthBiasClamp = clamp;
        _curDynamicStates.depthBiasSlope = slope;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::SetBlendConstants(const Color& constants)
{
    if (IsNotEqualF(_curDynamicStates.blendConstant.x, constants.x) ||
        IsNotEqualF(_curDynamicStates.blendConstant.y, constants.y) ||
        IsNotEqualF(_curDynamicStates.blendConstant.z, constants.z) ||
        IsNotEqualF(_curDynamicStates.blendConstant.w, constants.w))
    {
        _curDynamicStates.blendConstant.x = constants.x;
        _curDynamicStates.blendConstant.y = constants.y;
        _curDynamicStates.blendConstant.z = constants.z;
        _curDynamicStates.blendConstant.w = constants.w;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::SetDepthBound(float minBounds, float maxBounds)
{
    if (IsNotEqualF(_curDynamicStates.depthMinBounds, minBounds) ||
        IsNotEqualF(_curDynamicStates.depthMaxBounds, maxBounds))
    {
        _curDynamicStates.depthMinBounds = minBounds;
        _curDynamicStates.depthMaxBounds = maxBounds;
        _isStateInvalid = true;
    }
}

void ll::glCommandBuffer::SetStencilWriteMask(StencilFace face, uint32_t mask)
{
    auto update = [&](ll::DynamicStencilStates& stencilState) 
    {
        if (stencilState.writeMask != mask) 
        {
            stencilState.writeMask = mask;
            _isStateInvalid = true;
        }
    };
    //if (hasFlag(face, StencilFace::FRONT)) update(_curDynamicStates.stencilStatesFront);
    //if (hasFlag(face, StencilFace::BACK)) update(_curDynamicStates.stencilStatesBack);
}

void ll::glCommandBuffer::SetStencilCompareMask(StencilFace face, uint32_t ref, uint32_t mask)
{
    auto update = [&](ll::DynamicStencilStates& stencilState) 
    {
        if ((stencilState.reference != ref) ||
            (stencilState.compareMask != mask)) 
        {
            stencilState.reference = ref;
            stencilState.compareMask = mask;
            _isStateInvalid = true;
        }
    };
    //if (hasFlag(face, StencilFace::FRONT)) update(_curDynamicStates.stencilStatesFront);
    //if (hasFlag(face, StencilFace::BACK)) update(_curDynamicStates.stencilStatesBack);
}

void ll::glCommandBuffer::NextSubpass()
{
    _curCmdPackage->cmds.push(CmdType::END_RENDER_PASS);
    CmdBeginRenderPass* cmd = _cmdAllocator->beginRenderPassCmdPool.Alloc();
    cmd->subpassIdx = ++_curSubpassIdx;
    _curCmdPackage->beginRenderPassCmds.push(cmd);
    _curCmdPackage->cmds.push(CmdType::BEGIN_RENDER_PASS);
}

void ll::glCommandBuffer::Draw(const DrawInfo& info)
{
    if (_isStateInvalid) 
    {
        BindStates();
    }

    CmdDraw* cmd = _cmdAllocator->drawCmdPool.Alloc();
    cmd->drawInfo = info;
    _curCmdPackage->drawCmds.push(cmd);
    _curCmdPackage->cmds.push(CmdType::DRAW);

    ++_numDrawCalls;
    _numInstances += info.instanceCount;
    uint32_t indexCount = info.indexCount ? info.indexCount : info.vertexCount;
    if (_curGPUPipelineState) 
    {
        switch (_curGPUPipelineState->glPrimitive) {
        case GL_TRIANGLES: 
        {
            _numTriangles += indexCount / 3 * std::max(info.instanceCount, 1U);
            break;
        }
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN: 
        {
            _numTriangles += (indexCount - 2) * std::max(info.instanceCount, 1U);
            break;
        }
        default:
            break;
        }
    }
}

void ll::glCommandBuffer::UpdateBuffer(Buffer* buff, const void* data, uint32_t size)
{
    GPUBuffer* gpuBuffer = static_cast<glBuffer*>(buff)->GpuBuffer();
    if (gpuBuffer) 
    {
        CmdUpdateBuffer* cmd = _cmdAllocator->updateBufferCmdPool.Alloc();
        cmd->gpuBuffer = gpuBuffer;
        cmd->size = size;
        cmd->buffer = static_cast<const uint8_t*>(data);

        _curCmdPackage->updateBufferCmds.push(cmd);
        _curCmdPackage->cmds.push(CmdType::UPDATE_BUFFER);
    }
}

void ll::glCommandBuffer::CopyBuffersToTexture(const uint8_t* const* buffers, Texture* texture, const BufferTextureCopy* regions, uint32_t count)
{
    GPUTexture* gpuTexture = static_cast<glTexture*>(texture)->GpuTexture();
    if (gpuTexture) 
    {
        CmdCopyBufferToTexture* cmd = _cmdAllocator->copyBufferToTextureCmdPool.Alloc();
        cmd->gpuTexture = gpuTexture;
        cmd->regions = regions;
        cmd->count = count;
        cmd->buffers = buffers;

        _curCmdPackage->copyBufferToTextureCmds.push(cmd);
        _curCmdPackage->cmds.push(CmdType::COPY_BUFFER_TO_TEXTURE);
    }
}

void ll::glCommandBuffer::BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlit* regions, uint32_t count, Filter filter)
{
    CmdBlitTexture* cmd = _cmdAllocator->blitTextureCmdPool.Alloc();
    if (srcTexture) cmd->gpuTextureSrc = static_cast<glTexture*>(srcTexture)->GpuTexture();
    if (dstTexture) cmd->gpuTextureDst = static_cast<glTexture*>(dstTexture)->GpuTexture();
    cmd->regions = regions;
    cmd->count = count;
    cmd->filter = filter;

    _curCmdPackage->blitTextureCmds.push(cmd);
    _curCmdPackage->cmds.push(CmdType::BLIT_TEXTURE);
}

void ll::glCommandBuffer::Execute(CommandBuffer* const* cmdBuffs, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i) 
    {
        auto* cmdBuff = static_cast<glCommandBuffer*>(cmdBuffs[i]);
        CmdPackage* cmdPackage = cmdBuff->_pendingPackages.front();

        for (uint32_t j = 0; j < cmdPackage->beginRenderPassCmds.size(); ++j) 
        {
            CmdBeginRenderPass* cmd = cmdPackage->beginRenderPassCmds[j];
            ++cmd->refCount;
            _curCmdPackage->beginRenderPassCmds.push(cmd);
        }
        for (uint32_t j = 0; j < cmdPackage->bindStatesCmds.size(); ++j) 
        {
            CmdBindStates* cmd = cmdPackage->bindStatesCmds[j];
            ++cmd->refCount;
            _curCmdPackage->bindStatesCmds.push(cmd);
        }
        for (uint32_t j = 0; j < cmdPackage->drawCmds.size(); ++j) 
        {
            CmdDraw* cmd = cmdPackage->drawCmds[j];
            ++cmd->refCount;
            _curCmdPackage->drawCmds.push(cmd);
        }
        for (uint32_t j = 0; j < cmdPackage->updateBufferCmds.size(); ++j) 
        {
            CmdUpdateBuffer* cmd = cmdPackage->updateBufferCmds[j];
            ++cmd->refCount;
            _curCmdPackage->updateBufferCmds.push(cmd);
        }
        for (uint32_t j = 0; j < cmdPackage->copyBufferToTextureCmds.size(); ++j) 
        {
            CmdCopyBufferToTexture* cmd = cmdPackage->copyBufferToTextureCmds[j];
            ++cmd->refCount;
            _curCmdPackage->copyBufferToTextureCmds.push(cmd);
        }
        for (uint32_t j = 0; j < cmdPackage->blitTextureCmds.size(); ++j) 
        {
            CmdBlitTexture* cmd = cmdPackage->blitTextureCmds[j];
            ++cmd->refCount;
            _curCmdPackage->blitTextureCmds.push(cmd);
        }
        _curCmdPackage->cmds.concat(cmdPackage->cmds);

        _numDrawCalls += cmdBuff->_numDrawCalls;
        _numInstances += cmdBuff->_numInstances;
        _numTriangles += cmdBuff->_numTriangles;

        cmdBuff->_pendingPackages.pop();
        cmdBuff->_freePackages.push(cmdPackage);
    }
}

void ll::glCommandBuffer::DoInit(const CommandBufferInfo& info)
{
    _type = info.type;
    _queue = info.queue;

    _cmdAllocator = new GPUCommandAllocator;
    _curCmdPackage = new CmdPackage;

    size_t setCount = ll::glDevice::GetInstance()->GetBindingMappingInfo().setIndices.size();
    _curGPUDescriptorSets.resize(setCount);
    _curDynamicOffsets.resize(setCount);
}

void ll::glCommandBuffer::DoDestroy()
{
}

void ll::glCommandBuffer::BindStates()
{
    CmdBindStates* cmd = _cmdAllocator->bindStatesCmdPool.Alloc();

    cmd->gpuPipelineState = _curGPUPipelineState;
    cmd->gpuInputAssembler = _curGPUInputAssember;
    cmd->gpuDescriptorSets = _curGPUDescriptorSets;

    if (_curGPUPipelineState) 
    {
        std::vector<uint32_t>& dynamicOffsetOffsets = _curGPUPipelineState->gpuPipelineLayout->dynamicOffsetOffsets;
        cmd->dynamicOffsets.resize(_curGPUPipelineState->gpuPipelineLayout->dynamicOffsetCount);
        for (size_t i = 0U; i < _curDynamicOffsets.size(); i++) 
        {
            size_t count = dynamicOffsetOffsets[i + 1] - dynamicOffsetOffsets[i];
            count = std::min(count, _curDynamicOffsets[i].size());
            if (count) memcpy(&cmd->dynamicOffsets[dynamicOffsetOffsets[i]], _curDynamicOffsets[i].data(), count * sizeof(uint32_t));
        }
    }
    cmd->dynamicStates = _curDynamicStates;

    _curCmdPackage->bindStatesCmds.push(cmd);
    _curCmdPackage->cmds.push(CmdType::BIND_STATES);
    _isStateInvalid = false;
}
