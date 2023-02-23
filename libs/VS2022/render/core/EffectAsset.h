#pragma once

#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <variant>
#include <optional>

namespace ll 
{

using IPropertyHandleInfo = std::tuple<std::string, uint32_t, Type>;

using IPropertyValue = std::optional<std::variant<std::vector<float>, std::string>>;

struct IPropertyInfo 
{
    int32_t type;                                    
    std::optional<IPropertyHandleInfo> handleInfo; 
    std::optional<uint32_t> samplerHash;      
    IPropertyValue value;                            
    std::optional<bool> linear;                    
};

struct IPassInfoFull;

struct RasterizerStateInfo 
{
    std::optional<bool> isDiscard;
    std::optional<bool> isFrontFaceCCW;
    std::optional<bool> depthBiasEnabled;
    std::optional<bool> isDepthClip;
    std::optional<bool> isMultisample;

    std::optional<PolygonMode> polygonMode;
    std::optional<ShadeModel> shadeModel;
    std::optional<CullMode> cullMode;

    std::optional<float> depthBias;
    std::optional<float> depthBiasClamp;
    std::optional<float> depthBiasSlop;
    std::optional<float> lineWidth;

    void fromGFXRasterizerState(const RasterizerState& rs) 
    {
        isDiscard = rs.isDiscard;
        isFrontFaceCCW = rs.isFrontFaceCCW;
        depthBiasEnabled = rs.depthBiasEnabled;
        isDepthClip = rs.isDepthClip;
        isMultisample = rs.isMultisample;

        polygonMode = rs.polygonMode;
        shadeModel = rs.shadeModel;
        cullMode = rs.cullMode;

        depthBias = rs.depthBias;
        depthBiasClamp = rs.depthBiasClamp;
        depthBiasSlop = rs.depthBiasSlop;
        lineWidth = rs.lineWidth;
    }

    void assignToGFXRasterizerState(RasterizerState& rs) const 
    {
        if (isDiscard.has_value()) 
        {
            rs.isDiscard = isDiscard.value();
        }
        if (isFrontFaceCCW.has_value()) 
        {
            rs.isFrontFaceCCW = isFrontFaceCCW.value();
        }
        if (depthBiasEnabled.has_value()) 
        {
            rs.depthBiasEnabled = depthBiasEnabled.value();
        }
        if (isDepthClip.has_value()) 
        {
            rs.isDepthClip = isDepthClip.value();
        }
        if (isMultisample.has_value()) 
        {
            rs.isMultisample = isMultisample.value();
        }
        if (polygonMode.has_value()) 
        {
            rs.polygonMode = polygonMode.value();
        }
        if (shadeModel.has_value()) 
        {
            rs.shadeModel = shadeModel.value();
        }
        if (cullMode.has_value()) 
        {
            rs.cullMode = cullMode.value();
        }
        if (depthBias.has_value()) 
        {
            rs.depthBias = depthBias.value();
        }
        if (depthBiasClamp.has_value()) 
        {
            rs.depthBiasClamp = depthBiasClamp.value();
        }
        if (depthBiasSlop.has_value()) 
        {
            rs.depthBiasSlop = depthBiasSlop.value();
        }
        if (lineWidth.has_value()) 
        {
            rs.lineWidth = lineWidth.value();
        }
    }
};

struct DepthStencilStateInfo 
{
    std::optional<bool> depthTest;
    std::optional<bool> depthWrite;
    std::optional<bool> stencilTestFront;
    std::optional<bool> stencilTestBack;

    std::optional<ComparisonFunc> depthFunc;
    std::optional<ComparisonFunc> stencilFuncFront;
    std::optional<uint32_t> stencilReadMaskFront;
    std::optional<uint32_t> stencilWriteMaskFront;
    std::optional<StencilOp> stencilFailOpFront;
    std::optional<StencilOp> stencilZFailOpFront;
    std::optional<StencilOp> stencilPassOpFront;
    std::optional<uint32_t> stencilRefFront;

    std::optional<ComparisonFunc> stencilFuncBack;
    std::optional<uint32_t> stencilReadMaskBack;
    std::optional<uint32_t> stencilWriteMaskBack;
    std::optional<StencilOp> stencilFailOpBack;
    std::optional<StencilOp> stencilZFailOpBack;
    std::optional<StencilOp> stencilPassOpBack;
    std::optional<uint32_t> stencilRefBack;

    void fromGFXDepthStencilState(const DepthStencilState& ds) 
    {
        depthTest = ds.depthTest;
        depthWrite = ds.depthWrite;
        stencilTestFront = ds.stencilTestFront;
        stencilTestBack = ds.stencilTestBack;

        depthFunc = ds.depthFunc;
        stencilFuncFront = ds.stencilFuncFront;
        stencilReadMaskFront = ds.stencilReadMaskFront;
        stencilWriteMaskFront = ds.stencilWriteMaskFront;
        stencilFailOpFront = ds.stencilFailOpFront;
        stencilZFailOpFront = ds.stencilZFailOpFront;
        stencilPassOpFront = ds.stencilPassOpFront;
        stencilRefFront = ds.stencilRefFront;

        stencilFuncBack = ds.stencilFuncBack;
        stencilReadMaskBack = ds.stencilReadMaskBack;
        stencilWriteMaskBack = ds.stencilWriteMaskBack;
        stencilFailOpBack = ds.stencilFailOpBack;
        stencilZFailOpBack = ds.stencilZFailOpBack;
        stencilPassOpBack = ds.stencilPassOpBack;
        stencilRefBack = ds.stencilRefBack;
    }

    void assignToGFXDepthStencilState(DepthStencilState& ds) const 
    {
        if (depthTest.has_value()) 
        {
            ds.depthTest = depthTest.value();
        }
        if (depthWrite.has_value()) 
        {
            ds.depthWrite = depthWrite.value();
        }
        if (stencilTestFront.has_value()) 
        {
            ds.stencilTestFront = stencilTestFront.value();
        }
        if (stencilTestBack.has_value()) 
        {
            ds.stencilTestBack = stencilTestBack.value();
        }
        if (depthFunc.has_value()) 
        {
            ds.depthFunc = depthFunc.value();
        }
        if (stencilFuncFront.has_value()) 
        {
            ds.stencilFuncFront = stencilFuncFront.value();
        }
        if (stencilReadMaskFront.has_value()) 
        {
            ds.stencilReadMaskFront = stencilReadMaskFront.value();
        }
        if (stencilWriteMaskFront.has_value()) 
        {
            ds.stencilWriteMaskFront = stencilWriteMaskFront.value();
        }
        if (stencilFailOpFront.has_value()) 
        {
            ds.stencilFailOpFront = stencilFailOpFront.value();
        }
        if (stencilZFailOpFront.has_value()) 
        {
            ds.stencilZFailOpFront = stencilZFailOpFront.value();
        }
        if (stencilPassOpFront.has_value()) 
        {
            ds.stencilPassOpFront = stencilPassOpFront.value();
        }
        if (stencilRefFront.has_value()) 
        {
            ds.stencilRefFront = stencilRefFront.value();
        }
        if (stencilFuncBack.has_value()) 
        {
            ds.stencilFuncBack = stencilFuncBack.value();
        }
        if (stencilReadMaskBack.has_value()) 
        {
            ds.stencilReadMaskBack = stencilReadMaskBack.value();
        }
        if (stencilWriteMaskBack.has_value()) 
        {
            ds.stencilWriteMaskBack = stencilWriteMaskBack.value();
        }
        if (stencilFailOpBack.has_value()) 
        {
            ds.stencilFailOpBack = stencilFailOpBack.value();
        }
        if (stencilZFailOpBack.has_value()) 
        {
            ds.stencilZFailOpBack = stencilZFailOpBack.value();
        }
        if (stencilPassOpBack.has_value()) 
        {
            ds.stencilPassOpBack = stencilPassOpBack.value();
        }
        if (stencilRefBack.has_value()) 
        {
            ds.stencilRefBack = stencilRefBack.value();
        }
    }
};

struct BlendTargetInfo 
{
    std::optional<bool> blend;
    std::optional<BlendFactor> blendSrc;
    std::optional<BlendFactor> blendDst;
    std::optional<BlendOp> blendEq;
    std::optional<BlendFactor> blendSrcAlpha;
    std::optional<BlendFactor> blendDstAlpha;
    std::optional<BlendOp> blendAlphaEq;
    std::optional<ColorMask> blendColorMask;

    void fromGFXBlendTarget(const BlendTarget& target) 
    {
        blend = target.blend;
        blendSrc = target.blendSrc;
        blendDst = target.blendDst;
        blendEq = target.blendEq;
        blendSrcAlpha = target.blendSrcAlpha;
        blendDstAlpha = target.blendDstAlpha;
        blendAlphaEq = target.blendAlphaEq;
        blendColorMask = target.blendColorMask;
    }

    void assignToGFXBlendTarget(BlendTarget& target) const 
    {
        if (blend.has_value()) 
        {
            target.blend = blend.value();
        }
        if (blendSrc.has_value()) 
        {
            target.blendSrc = blendSrc.value();
        }
        if (blendDst.has_value()) 
        {
            target.blendDst = blendDst.value();
        }
        if (blendEq.has_value()) 
        {
            target.blendEq = blendEq.value();
        }
        if (blendSrcAlpha.has_value()) 
        {
            target.blendSrcAlpha = blendSrcAlpha.value();
        }
        if (blendDstAlpha.has_value()) 
        {
            target.blendDstAlpha = blendDstAlpha.value();
        }
        if (blendAlphaEq.has_value()) 
        {
            target.blendAlphaEq = blendAlphaEq.value();
        }
        if (blendColorMask.has_value()) 
        {
            target.blendColorMask = blendColorMask.value();
        }
    }
};

using BlendTargetInfoList = std::vector<BlendTargetInfo>;

struct BlendStateInfo 
{
    std::optional<bool> isA2C;
    std::optional<bool> isIndepend;
    std::optional<Color> blendColor;
    std::optional<BlendTargetInfoList> targets;

    void fromGFXBlendState(const BlendState& bs) 
    {
        isA2C = bs.isA2C;
        isIndepend = bs.isIndepend;
        blendColor = bs.blendColor;
        size_t len = bs.targets.size();
        if (len > 0) 
        {
            BlendTargetInfoList targetsList(len);
            for (size_t i = 0; i < len; ++i) 
            {
                targetsList[i].fromGFXBlendTarget(bs.targets[i]);
            }
            targets = targetsList;
        }
    }

    void assignToGFXBlendState(BlendState& bs) const 
    {
        if (targets.has_value()) 
        {
            const auto& targetsVal = targets.value();
            bs.targets.resize(targetsVal.size());
            for (size_t i = 0, len = targetsVal.size(); i < len; ++i) 
            {
                targetsVal[i].assignToGFXBlendTarget(bs.targets[i]);
            }
        }

        if (isA2C.has_value()) 
        {
            bs.isA2C = isA2C.value();
        }
        if (isIndepend.has_value()) 
        {
            bs.isIndepend = isIndepend.value();
        }
        if (blendColor.has_value()) 
        {
            bs.blendColor = blendColor.value();
        }
    }
};

struct IPassStates 
{
    std::optional<int32_t> priority;
    std::optional<PrimitiveMode> primitive;
    std::optional<RenderPassStage> stage;
    std::optional<RasterizerStateInfo> rasterizerState;
    std::optional<DepthStencilStateInfo> depthStencilState;
    std::optional<BlendStateInfo> blendState;
    std::optional<DynamicStateFlags> dynamicStates;
    std::optional<std::string> phase;

    IPassStates() = default;
    explicit IPassStates(const IPassInfoFull& o);
    IPassStates& operator=(const IPassInfoFull& o);
    void overrides(const IPassInfoFull& o);
};
using PassOverrides = IPassStates;

using PassPropertyInfoMap = std::map<std::string, IPropertyInfo>;

struct IPassInfoFull final 
{ //cjh } : public IPassInfo {
    // IPassStates
    std::optional<int32_t> priority;
    std::optional<PrimitiveMode> primitive;
    std::optional<RenderPassStage> stage;
    std::optional<RasterizerStateInfo> rasterizerState;
    std::optional<DepthStencilStateInfo> depthStencilState;
    std::optional<BlendStateInfo> blendState;
    std::optional<DynamicStateFlags> dynamicStates;
    std::optional<std::string> phase;
    // IPassInfo
    std::string program; // auto-generated from 'vert' and 'frag'
    std::optional<MacroRecord> embeddedMacros;
    index_t propertyIndex{ CC_INVALID_INDEX };
    std::optional<std::string> switch_;
    std::optional<PassPropertyInfoMap> properties;

    // IPassInfoFull
    // generated part
    index_t passIndex{ 0 };
    MacroRecord defines;
    std::optional<PassOverrides> stateOverrides;

    IPassInfoFull() = default;
    explicit IPassInfoFull(const IPassStates& o) 
    {
        *this = o;
    }
    IPassInfoFull& operator=(const IPassStates& o) 
    {
        priority = o.priority;
        primitive = o.primitive;
        stage = o.stage;
        rasterizerState = o.rasterizerState;
        depthStencilState = o.depthStencilState;
        blendState = o.blendState;
        dynamicStates = o.dynamicStates;
        phase = o.phase;
        return *this;
    }
};

using IPassInfo = IPassInfoFull;

struct ITechniqueInfo 
{
    std::vector<IPassInfoFull> passes;
    std::optional<std::string> name;
};

struct IBlockInfo 
{
    uint32_t binding{ UINT32_MAX };
    std::string name;
    std::vector<Uniform> members;
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct ISamplerTextureInfo 
{
    uint32_t binding{ UINT32_MAX };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct ITextureInfo 
{
    uint32_t set{ 0 };
    uint32_t binding{ UINT32_MAX };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct ISamplerInfo 
{
    uint32_t set{ 0 };
    uint32_t binding{ UINT32_MAX };
    std::string name;
    uint32_t count{ 0 };
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct IBufferInfo 
{
    uint32_t binding{ UINT32_MAX };
    std::string name;
    MemoryAccess memoryAccess{ MemoryAccess::NONE };
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct IImageInfo 
{
    uint32_t binding{ UINT32_MAX };
    std::string name;
    Type type{ Type::UNKNOWN };
    uint32_t count{ 0 };
    MemoryAccess memoryAccess{ MemoryAccess::NONE };
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct IInputAttachmentInfo 
{
    uint32_t set{ 0 };
    uint32_t binding{ UINT32_MAX };
    std::string name;
    uint32_t count{ 0 };
    ShaderStageFlags stageFlags{ ShaderStageFlags::NONE };
};

struct IAttributeInfo 
{
    std::string name;
    Format format{ Format::UNKNOWN };
    bool isNormalized{ false };
    uint32_t stream{ 0U };
    bool isInstanced{ false };
    uint32_t location{ 0U };

    std::vector<std::string> defines;
};

struct IDefineInfo 
{
    std::string name;
    std::string type;
    std::optional<std::vector<int32_t>> range; //cjh number is float?  ?: number[];
    std::optional<std::vector<std::string>> options;
    std::optional<std::string> defaultVal;
};

struct IBuiltin 
{
    std::string name;
    std::vector<std::string> defines;
};

struct IBuiltinInfo 
{
    std::vector<IBuiltin> buffers;
    std::vector<IBuiltin> blocks;
    std::vector<IBuiltin> samplerTextures;
    std::vector<IBuiltin> images;
};

using BuiltinsStatisticsType = std::map<std::string, int32_t>;

struct IBuiltins 
{
    IBuiltinInfo globals;
    IBuiltinInfo locals;
    BuiltinsStatisticsType statistics;
};

struct IShaderSource 
{
    std::string vert;
    std::string frag;
};

struct IShaderInfo 
{
    std::string name;
    std::hash_t hash{ 0xFFFFFFFFU };
    IShaderSource glsl4;
    IShaderSource glsl3;
    IShaderSource glsl1;
    IBuiltins builtins;
    std::vector<IDefineInfo> defines;
    std::vector<IAttributeInfo> attributes;
    std::vector<IBlockInfo> blocks;
    std::vector<ISamplerTextureInfo> samplerTextures;
    std::vector<ISamplerInfo> samplers;
    std::vector<ITextureInfo> textures;
    std::vector<IBufferInfo> buffers;
    std::vector<IImageInfo> images;
    std::vector<IInputAttachmentInfo> subpassInputs;

    const IShaderSource* getSource(const std::string& version) const 
    {
        if (version == "glsl1") return &glsl1;
        if (version == "glsl3") return &glsl3;
        if (version == "glsl4") return &glsl4;
        return nullptr;
    }
};

using IPreCompileInfoValueType = std::variant<std::vector<bool>, std::vector<int32_t>, std::vector<std::string>>;
using IPreCompileInfo = std::map<std::string, IPreCompileInfoValueType>;

class EffectAsset
{
public:
    using Super = Asset;

    EffectAsset() = default;
    virtual ~EffectAsset() = default;
    static void RegisterAsset(EffectAsset* asset);

    static void Remove(const std::string& name);
    static void Remove(EffectAsset* asset);

    static EffectAsset* Get(const std::string& name);

    using RegisteredEffectAssetMap = std::map<std::string, IntrusivePtr<EffectAsset>>;
    static RegisteredEffectAssetMap& GetAll() { return EffectAsset::effects; }

    static bool IsLayoutValid() { return layoutValid; }
    static void SetLayoutValid() { layoutValid = true; }

    inline void SetTechniques(const std::vector<ITechniqueInfo>& val) { _techniques = val; }
    inline void SetShaders(const std::vector<IShaderInfo>& val) { _shaders = val; }
    inline void SetCombinations(const std::vector<IPreCompileInfo>& val) { _combinations = val; }

    inline const std::vector<ITechniqueInfo>& GetTechniques() const { return _techniques; }
    inline const std::vector<IShaderInfo>& GetShaders() const { return _shaders; }
    inline const std::vector<IPreCompileInfo>& GetCombinations() const { return _combinations; }

    bool hideInEditor = false;

    void OnLoaded();
    bool Destroy();
    void InitDefault(const std::optional<std::string>& uuid);
    bool Validate() const;

protected:
    static std::vector<MacroRecord> DoCombine(const std::vector<MacroRecord>& cur, const IPreCompileInfo& info, IPreCompileInfo::iterator iter);
    static std::vector<MacroRecord> GenerateRecords(const std::string& key, const IPreCompileInfoValueType& value);
    static std::vector<MacroRecord> InsertInfoValue(const std::vector<MacroRecord>& records,
        const std::string& key,
        const IPreCompileInfoValueType& value);

    void Precompile();

public:
    std::vector<ITechniqueInfo> _techniques;

    std::vector<IShaderInfo> _shaders;

    std::vector<IPreCompileInfo> _combinations;
    //
protected:
    static RegisteredEffectAssetMap effects;
    static bool layoutValid;

    DISALLOW_COPY_MOVE_ASSIGN(EffectAsset)

    friend class EffectAssetDeserializer;
    friend class Material;
    friend class ProgramLib;
    friend class MaterialInstance;
    friend class BuiltinResMgr;
};

}