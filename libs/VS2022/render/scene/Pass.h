#pragma once

#include "../base/Ptr.h"
#include "../base/Macros.h"
#include "../base/Def_common.h"
#include "../core/PassUtils.h"
#include "../pipeline/Define.h"
#include "../core/EffectAsset.h"
#include "../core/ProgramLib.h"
#include "../scene/Define.h"

#include <map>
#include <string>
#include <vector>
#include <optional>

namespace ll
{

class Root;
class Buffer;
class Device;
class Shader;
class Sampler;
class Texture;
class ArrayBuffer;
class DescriptorSet;
class BatchedBuffer;
class InstancedBuffer;

struct PassDynamicsValue 
{
    bool dirty{ false };
    float value{ 0.F };
};
using IPassDynamics = std::map<uint32_t, PassDynamicsValue>;

enum class BatchingSchemes 
{
    NONE = 0,
    INSTANCING = 1,
    VB_MERGING = 2,
};

struct IBlockRef 
{
    float* data{ nullptr };
    size_t count{ 0 };
    size_t offset{ 0 };
};

class Pass
{
public:
    static Type GetTypeFromHandle(uint32_t handle) 
    {
        return GetTypeFromHandle(handle);
    }

    static uint32_t GetBindingFromHandle(uint32_t handle) 
    {
        return GetBindingFromHandle(handle);
    }

    static uint32_t GetCountFromHandle(uint32_t handle) 
    {
        return GetCountFromHandle(handle);
    }

    static uint32_t GetOffsetFromHandle(uint32_t handle) 
    {
        return GetOffsetFromHandle(handle);
    }

    static void FillPipelineInfo(Pass* pass, const IPassInfoFull& info);

    Pass();
    explicit Pass(Root* root);
    virtual ~Pass();

    void Initialize(const IPassInfoFull& info);

    uint32_t GetHandle(const std::string& name, uint32_t offset = 0, Type targetType = Type::UNKNOWN) const;

    uint32_t GetBinding(const std::string& name) const;

    void SetUniform(uint32_t handle, const MaterialProperty& value);

    MaterialProperty& GetUniform(uint32_t handle, MaterialProperty& out) const;

    void SetUniformArray(uint32_t handle, const MaterialPropertyList& value);

    void BindTexture(uint32_t binding, Texture* value, uint32_t index = 0);

    void BindSampler(uint32_t binding, Sampler* value, uint32_t index = 0);

    void SetDynamicState(DynamicStateFlagBit state, float value);

    virtual void OverridePipelineStates(const IPassInfo& original, const PassOverrides& overrides);

    void Update();

    InstancedBuffer* GetInstancedBuffer(int32_t extraKey = 0);
    BatchedBuffer* GetBatchedBuffer(int32_t extraKey = 0);

    void Destroy();

    void ResetUniform(const std::string& name);

    void ResetTexture(const std::string& name);

    void ResetTexture(const std::string& name, uint32_t index);

    void ResetUBOs();

    void ResetTextures();

    virtual bool TryCompile();
    virtual bool TryCompile(const std::optional<MacroRecord>& /*defineOverrides*/) { return Pass::TryCompile(); }

    Shader* GetShaderVariant();
    Shader* GetShaderVariant(const std::vector<IMacroPatch>& patches);

    IPassInfoFull GetPassInfoFull() const;

    inline Root* GetRoot() const { return _root; }
    inline Device* GetDevice() const { return _device; }
    inline IProgramInfo* GetShaderInfo() const { return _shaderInfo; }
    DescriptorSetLayout* GetLocalSetLayout() const;
    inline const std::string& GetProgram() const { return _programName; }
    inline const Record<std::string, IPropertyInfo>& GetProperties() const { return _properties; }
    inline const MacroRecord& GetDefines() const { return _defines; }
    inline MacroRecord& GetDefines() { return _defines; }
    inline index_t GetPassIndex() const { return _passIndex; }
    inline index_t GetPropertyIndex() const { return _propertyIndex; }
    // data
    inline const IPassDynamics& GetDynamics() const { return _dynamics; }
    inline const std::vector<IBlockRef>& GetBlocks() const { return _blocks; }
    inline ArrayBuffer* GetRootBlock() { return _rootBlock; }
    inline bool IsRootBufferDirty() const { return _rootBufferDirty; }
    inline void _setRootBufferDirty(bool val) { _rootBufferDirty = val; } // NOLINT(readability-identifier-naming)
    // states
    inline RenderPriority GetPriority() const { return _priority; }
    inline PrimitiveMode GetPrimitive() const { return _primitive; }
    inline RenderPassStage GetStage() const { return _stage; }
    inline uint32_t GetPhase() const { return _phase; }
    inline const RasterizerState* GetRasterizerState() const { return &_rs; }
    inline const DepthStencilState* GetDepthStencilState() const { return &_depthStencilState; }
    inline const BlendState* GetBlendState() const { return &_blendState; }
    inline DynamicStateFlagBit GetDynamicStates() const { return _dynamicStates; }
    inline BatchingSchemes GetBatchingScheme() const { return _batchingScheme; }
    inline DescriptorSet* GetDescriptorSet() const { return _descriptorSet; }
    inline PipelineLayout* GetPipelineLayout() const { return _pipelineLayout; }

    // Only for UI
    void InitPassFromTarget(Pass* target, const DepthStencilState& dss, uint32_t hashFactor);
    void UpdatePassHash();

    virtual void BeginChangeStatesSilently() {}
    virtual void EndChangeStatesSilently() {}

protected:
    void SetState(const BlendState& bs, const DepthStencilState& dss, const RasterizerState& rs, DescriptorSet* ds);
    void DoInit(const IPassInfoFull& info, bool copyDefines = false);
    virtual void SyncBatchingScheme();

    // internal resources
    IntrusivePtr<Buffer> _rootBuffer;
    std::vector<IntrusivePtr<Buffer>> _buffers;
    IntrusivePtr<DescriptorSet> _descriptorSet;
    IntrusivePtr<PipelineLayout> _pipelineLayout;
    // internal data
    index_t _passIndex{ 0 };
    index_t _propertyIndex{ 0 };
    std::string _programName;
    IPassDynamics _dynamics;
    Record<std::string, uint32_t> _propertyHandleMap;
    IntrusivePtr<ArrayBuffer> _rootBlock;
    std::vector<IBlockRef> _blocks; // Point to position in _rootBlock

    IProgramInfo* _shaderInfo; // weakref to template of ProgramLib
    MacroRecord _defines;
    Record<std::string, IPropertyInfo> _properties;
    IntrusivePtr<Shader> _shader;
    BlendState _blendState{};
    DepthStencilState _depthStencilState{};
    RasterizerState _rs{};
    RenderPriority _priority{ RenderPriority::DEFAULT };
    RenderPassStage _stage{ RenderPassStage::DEFAULT };
    uint32_t _phase{ 0 };
    std::string _phaseString;
    PrimitiveMode _primitive{ PrimitiveMode::TRIANGLE_LIST };
    BatchingSchemes _batchingScheme{ BatchingSchemes::NONE };
    DynamicStateFlagBit _dynamicStates{ DynamicStateFlagBit::NONE };
    Record<int32_t, IntrusivePtr<InstancedBuffer>> _instancedBuffers;
    Record<int32_t, IntrusivePtr<BatchedBuffer>> _batchedBuffers;

    Root* _root{ nullptr };
    Device* _device{ nullptr };

    bool _rootBufferDirty{ false };

    DISALLOW_COPY_MOVE_ASSIGN(Pass)
};

}