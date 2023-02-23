#pragma once

#include "../base/Ptr.h"
#include "../base/Def_type.h"
#include "../base/Macros.h"
#include "../core/EffectAsset.h"
#include "PassUtils.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace ll
{

class Pass;

struct IMaterialInfo 
{
    EffectAsset* effectAsset{ nullptr };
    std::optional<std::string> effectName;
    std::optional<uint32_t> technique;

    using DefinesType = std::variant<MacroRecord, std::vector<MacroRecord>>;
    std::optional<DefinesType> defines;

    using PassOverridesType = std::variant<PassOverrides, std::vector<PassOverrides>>;
    std::optional<PassOverridesType> states;
};

class Material
{
public:
    using Super = Asset;

    Material();
    virtual ~Material();

    void Initialize(const IMaterialInfo& info);
    void Reset(const IMaterialInfo& info);

    void InitDefault(const std::optional<std::string>& uuid);
    bool Validate() const;

    bool Destroy();

    virtual void RecompileShaders(const MacroRecord& overrides) 
    {
        Material::RecompileShaders(overrides, CC_INVALID_INDEX);
    }
    virtual void RecompileShaders(const MacroRecord& overrides, int32_t passIdx);

    virtual void OverridePipelineStates(const PassOverrides& overrides) 
    {
        Material::OverridePipelineStates(overrides, CC_INVALID_INDEX);
    }
    virtual void OverridePipelineStates(const PassOverrides& overrides, int32_t passIdx);

    void OnLoaded();

    void ResetUniforms(bool clearPasses = true);

    void SetProperty(const std::string& name, const MaterialPropertyVariant& val, int32_t passIdx = CC_INVALID_INDEX);

    void SetPropertyNull(const std::string& name, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyFloat32(const std::string& name, float val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyInt32(const std::string& name, int32_t val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyVec2(const std::string& name, const glm::vec2& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyVec3(const std::string& name, const glm::vec3& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyVec4(const std::string& name, const glm::vec4& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyColor(const std::string& name, const Color& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyMat3(const std::string& name, const glm::mat3& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyMat4(const std::string& name, const glm::mat4& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyQuaternion(const std::string& name, const glm::quat& val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyTextureBase(const std::string& name, TextureBase* val, int32_t passIdx = CC_INVALID_INDEX);
    void SetPropertyGFXTexture(const std::string& name, Texture* val, int32_t passIdx = CC_INVALID_INDEX);

    void setPropertyFloat32Array(const std::string& name, const std::vector<float>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyInt32Array(const std::string& name, const std::vector<int32_t>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyVec2Array(const std::string& name, const std::vector<glm::vec2>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyVec3Array(const std::string& name, const std::vector<glm::vec3>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyVec4Array(const std::string& name, const std::vector<glm::vec4>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyColorArray(const std::string& name, const std::vector<Color>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyMat3Array(const std::string& name, const std::vector<glm::mat3>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyMat4Array(const std::string& name, const std::vector<glm::mat4>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyQuaternionArray(const std::string& name, const std::vector<glm::quat>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyTextureBaseArray(const std::string& name, const std::vector<TextureBase*>& val, int32_t passIdx = CC_INVALID_INDEX);
    void setPropertyGFXTextureArray(const std::string& name, const std::vector<Texture*>& val, int32_t passIdx = CC_INVALID_INDEX);

    const MaterialPropertyVariant* GetProperty(const std::string& name, int32_t passIdx = CC_INVALID_INDEX) const;

    void Copy(const Material* mat, IMaterialInfo* overrides = nullptr);

    void FillInfo(const IMaterialInfo& info);

    IntrusivePtr<EffectAsset> _effectAsset;

    uint32_t _techIdx{ 0 };

    std::vector<MacroRecord> _defines;

    std::vector<PassOverrides> _states;

    std::vector<Record<std::string, MaterialPropertyVariant>> _props;
    //

protected:
    std::shared_ptr<std::vector<IntrusivePtr<Pass>>> _passes;

public:
    inline void SetEffectAsset(EffectAsset* val) 
    {
        _effectAsset = val;
    }

    inline EffectAsset* GetEffectAsset() const 
    {
        return _effectAsset.get();
    }

    inline std::string GetEffectName() const 
    {
        return _effectAsset ? _effectAsset->GetName() : "";
    }

    inline uint32_t GetTechniqueIndex() const 
    {
        return _techIdx;
    }

    std::shared_ptr<std::vector<IntrusivePtr<Pass>>>& GetPasses() 
    {
        return _passes;
    }

    virtual Material* GetParent() const 
    {
        return nullptr;
    }

protected:
    void Update(bool keepProps = true);
    bool UploadProperty(Pass* pass, const std::string& name, const MaterialPropertyVariant& val);
    void BindTexture(Pass* pass, uint32_t handle, const MaterialProperty& val, uint32_t index = 0);

    template <typename T1, typename T2>
    void PrepareInfo(const T1& patch, std::vector<T2>& cur) 
    {
        auto* pOneElement = std::get_if<T2>(&patch);
        if (pOneElement != nullptr) 
        {
            size_t len = _effectAsset != nullptr ? _effectAsset->_techniques[_techIdx].passes.size() : 1;

            std::vector<T2> patchArray;
            patchArray.reserve(len);
            for (size_t i = 0; i < len; ++i) 
            {
                patchArray.emplace_back(*pOneElement);
            }

            cur.resize(patchArray.size());

            for (size_t i = 0; i < len; ++i) 
            {
                cur[i] = patchArray[i];
            }
        }
        else 
        {
            auto* pPatchArray = std::get_if<std::vector<T2>>(&patch);
            if (pPatchArray != nullptr) 
            {
                const auto& patchArray = *pPatchArray;
                size_t len = patchArray.size();
                cur.resize(len);

                for (size_t i = 0; i < len; ++i) 
                {
                    cur[i] = patchArray[i];
                }
            }
        }
    }

    virtual void DoDestroy();

    virtual std::vector<IntrusivePtr<Pass>> CreatePasses();

private:
    friend class MaterialDeserializer;

    DISALLOW_COPY_MOVE_ASSIGN(Material)

};

}