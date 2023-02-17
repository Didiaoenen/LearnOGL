#pragma once

#include "Def_common.h"
#include "glWrangler.h"

#include <unordered_map>

namespace ll
{

struct UniformSamplerTexture 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformSamplerTexture)
};
using UniformSamplerTextureList = std::vector<UniformSamplerTexture>;

struct UniformInputAttachment 
{
    uint32_t set{ 0 };
    uint32_t binding{ 0 };
    std::string name;
    uint32_t count{ 0 };

    EXPOSE_COPY_FN(UniformInputAttachment)
};
using UniformInputAttachmentList = std::vector<UniformInputAttachment>;

struct GPUShaderStage 
{
    ShaderStageFlagBit type = ShaderStageFlagBit::NONE;
    std::string source;
    GLuint glShader = 0;
};
using GPUShaderStageList = std::vector<GPUShaderStage>;

struct GPUUniform 
{
    uint32_t binding = INVALID_BINDING;
    std::string name;
    Type type = Type::UNKNOWN;
    uint32_t stride = 0;
    uint32_t count = 0;
    uint32_t size = 0;
    uint32_t offset = 0;
    GLenum glType = 0;
    GLint glLoc = -1;
    std::vector<uint8_t> buff;
};
using GPUUniformList = std::vector<GPUUniform>;

struct GPUUniformBlock 
{
    uint32_t set = 0;
    uint32_t binding = 0;
    uint32_t idx = 0;
    std::string name;
    uint32_t size = 0;
    GPUUniformList glUniforms;
    GPUUniformList glActiveUniforms;
    std::vector<uint32_t> activeUniformIndices;
};
using GPUUniformBlockList = std::vector<GPUUniformBlock>;

struct GPUUniformSamplerTexture 
{
    uint32_t set = 0;
    uint32_t binding = 0;
    std::string name;
    Type type = Type::UNKNOWN;
    uint32_t count = 0U;

    std::vector<GLint> units;
    GLenum glType = 0;
    GLint glLoc = -1;
};
using GPUUniformSamplerTextureList = std::vector<GPUUniformSamplerTexture>;

struct GPUInput 
{
    uint32_t binding = 0;
    std::string name;
    Type type = Type::UNKNOWN;
    uint32_t stride = 0;
    uint32_t count = 0;
    uint32_t size = 0;
    GLenum glType = 0;
    GLint glLoc = -1;
};
using GPUInputList = std::vector<GPUInput>;

struct GPUSwapchain 
{
    EGLSurface glSurface{ GL_NO_SURFACE };
    EGLint eglSwapInterval{ 0 };
    GLuint glFramebuffer{ 0 };
    GPUTexture* gpuColorTexture{ nullptr };
};

struct GPUTexture 
{
    TextureType type{ TextureType::TEX2D };
    Format format{ Format::UNKNOWN };
    TextureUsage usage{ TextureUsageBit::NONE };
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    uint32_t depth{ 1 };
    uint32_t size{ 0 };
    uint32_t arrayLayer{ 1 };
    uint32_t mipLevel{ 1 };
    SampleCount samples{ SampleCount::ONE };
    TextureFlags flags{ TextureFlagBit::NONE };
    bool isPowerOf2{ false };
    bool memoryless{ false };
    GLenum glTarget{ 0 };
    GLenum glInternalFmt{ 0 };
    GLenum glFormat{ 0 };
    GLenum glType{ 0 };
    GLenum glUsage{ 0 };
    GLint glSamples{ 0 };
    GLuint glTexture{ 0 };
    GLuint glRenderbuffer{ 0 };
    GLenum glWrapS{ 0 };
    GLenum glWrapT{ 0 };
    GLenum glMinFilter{ 0 };
    GLenum glMagFilter{ 0 };
    GPUSwapchain* swapchain{ nullptr };
};
using GPUTextureList = std::vector<GPUTexture*>;

struct GPUBuffer 
{
    BufferUsage usage = BufferUsage::NONE;
    MemoryUsage memUsage = MemoryUsage::NONE;
    uint32_t size = 0;
    uint32_t stride = 0;
    uint32_t count = 0;
    GLenum glTarget = 0;
    GLuint glBuffer = 0;
    uint8_t* buffer = nullptr;
    DrawInfoList indirects;
};
using GPUBufferList = std::vector<GPUBuffer*>;

struct GPUSampler 
{
    Filter minFilter = Filter::NONE;
    Filter magFilter = Filter::NONE;
    Filter mipFilter = Filter::NONE;
    Address addressU = Address::CLAMP;
    Address addressV = Address::CLAMP;
    Address addressW = Address::CLAMP;
    GLenum glMinFilter = 0;
    GLenum glMagFilter = 0;
    GLenum glWrapS = 0;
    GLenum glWrapT = 0;
    GLenum glWrapR = 0;
};

struct GPUShader 
{
    std::string name;
    UniformBlockList blocks;
    UniformSamplerTextureList samplerTextures;
    UniformInputAttachmentList subpassInputs;
    GLuint glProgram = 0;
    GPUShaderStageList gpuStages;
    GPUInputList glInputs;
    GPUUniformBlockList glBlocks;
    GPUUniformSamplerTextureList glSamplerTextures;
};

struct GPURenderPass 
{
    struct AttachmentStatistics 
    {
        uint32_t loadSubpass{ SUBPASS_EXTERNAL };
        uint32_t storeSubpass{ SUBPASS_EXTERNAL };
    };

    ColorAttachmentList colorAttachments;
    DepthStencilAttachment depthStencilAttachment;
    SubpassInfoList subpasses;

    std::vector<AttachmentStatistics> statistics; // per attachment
};

struct GPUAttribute 
{
    std::string name;
    GLuint glBuffer = 0;
    GLenum glType = 0;
    uint32_t size = 0;
    uint32_t count = 0;
    uint32_t stride = 1;
    uint32_t componentCount = 1;
    bool isNormalized = false;
    bool isInstanced = false;
    uint32_t offset = 0;
};
using GPUAttributeList = std::vector<GPUAttribute>;

struct GPUInputAssembler 
{
    AttributeList attributes;
    GPUBufferList gpuVertexBuffers;
    GPUBuffer* gpuIndexBuffer = nullptr;
    GPUBuffer* gpuIndirectBuffer = nullptr;
    GPUAttributeList glAttribs;
    GLenum glIndexType = 0;
    std::unordered_map<size_t, GLuint> glVAOs;
};

struct ObjectCache 
{
    uint32_t subpassIdx = 0U;
    GPURenderPass* gpuRenderPass = nullptr;
    GPUFramebuffer* gpuFramebuffer = nullptr;
    GPUPipelineState* gpuPipelineState = nullptr;
    GPUInputAssembler* gpuInputAssembler = nullptr;
    GLenum glPrimitive = 0;
    Rect renderArea;
    ColorList clearColors;
    float clearDepth = 1.F;
    uint32_t clearStencil = 0U;
};

class GPUStateCache 
{
public:
    GLuint glArrayBuffer = 0;
    GLuint glElementArrayBuffer = 0;
    GLuint glUniformBuffer = 0;
    GLuint glVAO = 0;
    uint32_t texUint = 0;
    std::vector<GLuint> glTextures;
    GLuint glProgram = 0;
    std::vector<bool> glEnabledAttribLocs;
    std::vector<bool> glCurrentAttribLocs;
    GLuint glFramebuffer = 0;
    GLuint glRenderbuffer = 0;
    GLuint glReadFBO = 0;
    Viewport viewport;
    Rect scissor;
    RasterizerState rs;
    DepthStencilState dss;
    BlendState bs;
    bool isCullFaceEnabled = true;
    bool isStencilTestEnabled = false;
    std::unordered_map<std::string, uint32_t> texUnitCacheMap;
    ObjectCache gfxStateCache;

    void initialize(size_t texUnits, size_t vertexAttributes) 
    {
        glTextures.resize(texUnits, 0U);
        glEnabledAttribLocs.resize(vertexAttributes, false);
        glCurrentAttribLocs.resize(vertexAttributes, false);
    }

    void reset() {
        glArrayBuffer = 0;
        glElementArrayBuffer = 0;
        glUniformBuffer = 0;
        glVAO = 0;
        texUint = 0;
        glTextures.assign(glTextures.size(), 0U);
        glProgram = 0;
        glEnabledAttribLocs.assign(glEnabledAttribLocs.size(), false);
        glCurrentAttribLocs.assign(glCurrentAttribLocs.size(), false);
        glFramebuffer = 0;
        glReadFBO = 0;
        isCullFaceEnabled = true;
        isStencilTestEnabled = false;

        viewport = Viewport();
        scissor = Rect();
        rs = RasterizerState();
        dss = DepthStencilState();
        bs = BlendState();

        gfxStateCache.gpuRenderPass = nullptr;
        gfxStateCache.gpuFramebuffer = nullptr;
        gfxStateCache.gpuPipelineState = nullptr;
        gfxStateCache.gpuInputAssembler = nullptr;
        gfxStateCache.glPrimitive = 0U;
        gfxStateCache.subpassIdx = 0U;
    }
};


class GPUFramebuffer final
{
public:
    GPURenderPass* gpuRenderPass{ nullptr };
    GPUTextureList gpuColorTextures;
    GPUTexture* gpuDepthStencilTexture{ nullptr };
    bool usesFBF{ false };
    uint32_t lodLevel{ 0 };

    struct GLFramebufferInfo {
        GLuint glFramebuffer{ 0U };
        uint32_t width{ UINT_MAX };
        uint32_t height{ UINT_MAX };
    };

    struct GLFramebuffer 
    {
        inline void initialize(GPUSwapchain* sc) { swapchain = sc; }
        inline void initialize(const GLFramebufferInfo& info) {
            _glFramebuffer = info.glFramebuffer;
            _width = info.width;
            _height = info.height;
        }
        inline GLuint getFramebuffer() const { return swapchain ? swapchain->glFramebuffer : _glFramebuffer; }
        inline uint32_t getWidth() const { return swapchain ? swapchain->gpuColorTexture->width : _width; }
        inline uint32_t getHeight() const { return swapchain ? swapchain->gpuColorTexture->height : _height; }

        void destroy(GPUStateCache* cache, GPUFramebufferCacheMap* framebufferCacheMap);

        GPUSwapchain* swapchain{ nullptr };

    private:
        GLuint _glFramebuffer{ 0U };
        uint32_t _width{ 0U };
        uint32_t _height{ 0U };
    };

    struct Framebuffer {
        GLFramebuffer framebuffer;

        GLbitfield resolveMask{ 0U };
        GLFramebuffer resolveFramebuffer;
    };

    std::vector<Framebuffer> instances;

    std::vector<uint32_t> uberColorAttachmentIndices;
    uint32_t uberDepthStencil{ INVALID_BINDING };
    Framebuffer uberInstance;

    uint32_t uberOnChipOutput{ INVALID_BINDING };
    uint32_t uberFinalOutput{ INVALID_BINDING };
};

class GPUFramebufferCacheMap final 
{
public:
    explicit GPUFramebufferCacheMap(GPUStateCache* cache) : _cache(cache) {}

    void registerExternal(GLuint glFramebuffer, const GPUTexture* gpuTexture) 
    {
        bool isTexture = gpuTexture->glTexture;
        GLuint glResource = isTexture ? gpuTexture->glTexture : gpuTexture->glRenderbuffer;
        auto& cacheMap = isTexture ? _textureMap : _renderbufferMap;

        if (!cacheMap[glResource].glFramebuffer) 
        {
            cacheMap[glResource] = { glFramebuffer, true };
        }
    }

    void unregisterExternal(GLuint glFramebuffer) 
    {
        for (auto& fbos : _textureMap) 
        {
            if (fbos.second.glFramebuffer == glFramebuffer) 
            {
                fbos.second.glFramebuffer = 0;
                return;
            }
        }
        for (auto& fbos : _renderbufferMap) 
        {
            if (fbos.second.glFramebuffer == glFramebuffer) 
            {
                fbos.second.glFramebuffer = 0;
                return;
            }
        }
    }

    GLuint getFramebufferFromTexture(const GPUTexture* gpuTexture) 
    {
        bool isTexture = gpuTexture->glTexture;
        GLuint glResource = isTexture ? gpuTexture->glTexture : gpuTexture->glRenderbuffer;
        auto& cacheMap = isTexture ? _textureMap : _renderbufferMap;

        if (!cacheMap.count(glResource)) 
        {
            GLuint glFramebuffer = 0U;
            glGenFramebuffers(1, &glFramebuffer);
            if (_cache->glFramebuffer != glFramebuffer) 
            {
                glBindFramebuffer(GL_FRAMEBUFFER, glFramebuffer);
                _cache->glFramebuffer = glFramebuffer;
            }

            const FormatInfo& info = GFX_FORMAT_INFOS[static_cast<uint32_t>(gpuTexture->format)];
            if (isTexture) 
            {
                if (info.hasDepth) 
                {
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gpuTexture->glTarget, glResource, 0);
                    if (info.hasStencil) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, gpuTexture->glTarget, glResource, 0);
                }
                else 
                {
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gpuTexture->glTarget, glResource, 0);
                }
            }
            else 
            {
                if (info.hasDepth) 
                {
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gpuTexture->glTarget, glResource);
                    if (info.hasStencil) glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, gpuTexture->glTarget, glResource);
                }
                else 
                {
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gpuTexture->glTarget, glResource);
                }
            }

            GLenum status;
            status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            assert(status == GL_FRAMEBUFFER_COMPLETE);

            cacheMap[glResource].glFramebuffer = glFramebuffer;
        }

        return cacheMap[glResource].glFramebuffer;
    }

    void onTextureDestroy(const GPUTexture* gpuTexture) 
    {
        bool isTexture = gpuTexture->glTexture;
        GLuint glResource = isTexture ? gpuTexture->glTexture : gpuTexture->glRenderbuffer;
        auto& cacheMap = isTexture ? _textureMap : _renderbufferMap;

        if (cacheMap.count(glResource)) 
        {
            GLuint glFramebuffer = cacheMap[glResource].glFramebuffer;
            if (!glFramebuffer) return;

            if (_cache->glFramebuffer == glFramebuffer) 
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                _cache->glFramebuffer = 0;
            }
            glDeleteFramebuffers(1, &glFramebuffer);
            cacheMap.erase(glResource);
        }
    }

private:
    GPUStateCache* _cache = nullptr;

    struct FramebufferRecord {
        GLuint glFramebuffer{ 0 };
        bool isExternal{ false };
    };
    using CacheMap = std::unordered_map<GLuint, FramebufferRecord>;
    CacheMap _renderbufferMap;
    CacheMap _textureMap;
};

struct RasterizerState 
{
    uint32_t isDiscard{ 0 };
    PolygonMode polygonMode{ PolygonMode::FILL };
    ShadeModel shadeModel{ ShadeModel::GOURAND };
    CullMode cullMode{ CullMode::BACK };
    uint32_t isFrontFaceCCW{ 1 };
    uint32_t depthBiasEnabled{ 0 };
    float depthBias{ 0.F };
    float depthBiasClamp{ 0.F };
    float depthBiasSlop{ 0.F };
    uint32_t isDepthClip{ 1 };
    uint32_t isMultisample{ 0 };
    float lineWidth{ 1.F };

    void reset() 
    {
        *this = RasterizerState();
    }

    EXPOSE_COPY_FN(RasterizerState)
};

struct DepthStencilState 
{
    uint32_t depthTest{ 1 };
    uint32_t depthWrite{ 1 };
    ComparisonFunc depthFunc{ ComparisonFunc::LESS };
    uint32_t stencilTestFront{ 0 };
    ComparisonFunc stencilFuncFront{ ComparisonFunc::ALWAYS };
    uint32_t stencilReadMaskFront{ 0xffffffff };
    uint32_t stencilWriteMaskFront{ 0xffffffff };
    StencilOp stencilFailOpFront{ StencilOp::KEEP };
    StencilOp stencilZFailOpFront{ StencilOp::KEEP };
    StencilOp stencilPassOpFront{ StencilOp::KEEP };
    uint32_t stencilRefFront{ 1 };
    uint32_t stencilTestBack{ 0 };
    ComparisonFunc stencilFuncBack{ ComparisonFunc::ALWAYS };
    uint32_t stencilReadMaskBack{ 0xffffffff };
    uint32_t stencilWriteMaskBack{ 0xffffffff };
    StencilOp stencilFailOpBack{ StencilOp::KEEP };
    StencilOp stencilZFailOpBack{ StencilOp::KEEP };
    StencilOp stencilPassOpBack{ StencilOp::KEEP };
    uint32_t stencilRefBack{ 1 };

    void reset() 
    {
        *this = DepthStencilState();
    }

    EXPOSE_COPY_FN(DepthStencilState)
};

struct BlendState 
{
    uint32_t isA2C{ 0 };
    uint32_t isIndepend{ 0 };
    Color blendColor;
    BlendTargetList targets{ 1 };

    void setTarget(index_t index, const BlendTarget& target) 
    {
        if (index >= targets.size()) 
        {
            targets.resize(index + 1);
        }
        targets[index] = target;
    }

    void reset() 
    {
        *this = BlendState();
    }

    void destroy() {}

    EXPOSE_COPY_FN(BlendState)
};

struct DescriptorSetLayoutBinding 
{
    uint32_t binding{ INVALID_BINDING };
    DescriptorType descriptorType{ DescriptorType::UNKNOWN };
    uint32_t count{ 0 };
    ShaderStageFlags stageFlags{ ShaderStageFlagBit::NONE };
    SamplerList immutableSamplers;

    EXPOSE_COPY_FN(DescriptorSetLayoutBinding)
};
using DescriptorSetLayoutBindingList = std::vector<DescriptorSetLayoutBinding>;

struct GPUDescriptorSetLayout 
{
    DescriptorSetLayoutBindingList bindings;
    std::vector<uint32_t> dynamicBindings;

    std::vector<uint32_t> bindingIndices;
    std::vector<uint32_t> descriptorIndices;
    uint32_t descriptorCount = 0U;
};
using GPUDescriptorSetLayoutList = std::vector<GPUDescriptorSetLayout*>;

struct GPUPipelineLayout 
{
    GPUDescriptorSetLayoutList setLayouts;

    std::vector<std::vector<int>> dynamicOffsetIndices;
    std::vector<uint32_t> dynamicOffsetOffsets;
    std::vector<uint32_t> dynamicOffsets;
    uint32_t dynamicOffsetCount = 0U;
};

struct GPUPipelineState 
{
    GLenum glPrimitive = GL_TRIANGLES;
    GPUShader* gpuShader = nullptr;
    RasterizerState rs;
    DepthStencilState dss;
    BlendState bs;
    DynamicStateList dynamicStates;
    GPUPipelineLayout* gpuLayout = nullptr;
    GPURenderPass* gpuRenderPass = nullptr;
    GPUPipelineLayout* gpuPipelineLayout = nullptr;
};

struct GPUBufferView 
{
    GPUBuffer* gpuBuffer = nullptr;
    uint32_t offset = 0U;
    uint32_t range = 0U;
};

struct GPUDescriptor 
{
    DescriptorType type = DescriptorType::UNKNOWN;
    GPUBuffer* gpuBuffer = nullptr;
    GPUBufferView* gpuBufferView = nullptr;
    GPUTexture* gpuTexture = nullptr;
    GPUSampler* gpuSampler = nullptr;
};
using GPUDescriptorList = std::vector<GPUDescriptor>;

struct GPUDescriptorSet 
{
    GPUDescriptorList gpuDescriptors;
    const std::vector<uint32_t>* descriptorIndices = nullptr;
};

struct DynamicStencilStates 
{
    uint32_t writeMask{ 0 };
    uint32_t compareMask{ 0 };
    uint32_t reference{ 0 };

    EXPOSE_COPY_FN(DynamicStencilStates)
};

struct DynamicStates 
{
    Viewport viewport;
    Rect scissor;
    Color blendConstant;
    float lineWidth{ 1.F };
    float depthBiasConstant{ 0.F };
    float depthBiasClamp{ 0.F };
    float depthBiasSlope{ 0.F };
    float depthMinBounds{ 0.F };
    float depthMaxBounds{ 0.F };

    DynamicStencilStates stencilStatesFront;
    DynamicStencilStates stencilStatesBack;

    EXPOSE_COPY_FN(DynamicStates)
};

struct BufferTextureCopy 
{
    uint32_t buffOffset{ 0 };
    uint32_t buffStride{ 0 };
    uint32_t buffTexHeight{ 0 };
    Offset texOffset;
    Extent texExtent;
    TextureSubresLayers texSubres;

    EXPOSE_COPY_FN(BufferTextureCopy)
};
using BufferTextureCopyList = std::vector<BufferTextureCopy>;

struct TextureBlit 
{
    TextureSubresLayers srcSubres;
    Offset srcOffset;
    Extent srcExtent;
    TextureSubresLayers dstSubres;
    Offset dstOffset;
    Extent dstExtent;

    EXPOSE_COPY_FN(TextureBlit)
};
using TextureBlitList = std::vector<TextureBlit>;

struct GPUConstantRegistry 
{
    size_t currentBoundThreadID{ 0U };

    MSRTSupportLevel mMSRT{ MSRTSupportLevel::NONE };
    FBFSupportLevel mFBF{ FBFSupportLevel::NONE };

    bool useVAO = false;
    bool useDrawInstanced = false;
    bool useInstancedArrays = false;
    bool useDiscardFramebuffer = false;
};

class GPUContext final 
{
public:
    bool Initialize(GPUStateCache* stateCache, GPUConstantRegistry* constantRegistry);
    void Destroy();

    EGLint eglMajorVersion{ 0 };
    EGLint eglMinorVersion{ 0 };
    EGLDisplay eglDisplay{ EGL_NO_DISPLAY };
    EGLConfig eglConfig{ nullptr };
    std::vector<EGLint> eglAttributes;

    EGLSurface eglDefaultSurface{ EGL_NO_SURFACE };
    EGLContext eglDefaultContext{ EGL_NO_CONTEXT };

    void MakeCurrent(const GPUSwapchain* drawSwapchain = nullptr, const GPUSwapchain* readSwapchain = nullptr);
    void BindContext(bool bound);

    void Present(const GPUSwapchain* swapchain);

    inline bool CheckExtension(const std::string& extension) const 
    {
        return std::find(_extensions.begin(), _extensions.end(), extension) != _extensions.end();
    }

private:
    bool MakeCurrent(EGLSurface drawSurface, EGLSurface readSurface, EGLContext context, bool updateCache = true);
    EGLContext GetSharedContext();
    void ResetStates() const;

    EGLSurface _eglCurrentDrawSurface{ EGL_NO_SURFACE };
    EGLSurface _eglCurrentReadSurface{ EGL_NO_SURFACE };
    EGLContext _eglCurrentContext{ EGL_NO_CONTEXT };
    EGLint _eglCurrentInterval{ 0 };

    GPUStateCache* _stateCache{ nullptr };
    GPUConstantRegistry* _constantRegistry{ nullptr };

    std::unordered_map<size_t, EGLContext> _sharedContexts;

    std::vector<std::string> _extensions;
};

}
