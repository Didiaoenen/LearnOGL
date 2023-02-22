#pragma once

#include "Light.h"
#include "Ambient.h"
#include "Shadows.h"

#include <glm/glm.hpp>

namespace ll
{



class DirectionalLight final : public Light
{
public:
    DirectionalLight();
    ~DirectionalLight() override;

    void Initialize() override;
    void Update() override;

    inline void SetShadowEnabled(bool enabled) 
    {
        _shadowEnabled = enabled;
        Activate();
    }
    inline void SetShadowPcf(PCFType pcf) 
    {
        _shadowPcf = pcf;
        Activate();
    }
    inline void SetShadowBias(float bias) { _shadowBias = bias; }
    inline void SetShadowNormalBias(float normalBias) { _shadowNormalBias = normalBias; }
    inline void SetShadowSaturation(float saturation) { _shadowSaturation = saturation; }
    inline void SetShadowDistance(float distance) { _shadowDistance = distance; }
    inline void SetShadowInvisibleOcclusionRange(float invisibleOcclusionRange) { _shadowInvisibleOcclusionRange = invisibleOcclusionRange; }
    inline void SetCSMLevel(CSMLevel csmLevel) 
    {
        _csmLevel = csmLevel;
        Activate();
    }
    inline void SetCSMLayerLambda(float lambda) { _csmLayerLambda = lambda; }
    inline void SetCSMNeedUpdate(bool isCSMNeedUpdate) { _isCSMNeedUpdate = isCSMNeedUpdate; }
    inline void SetCSMOptimizationMode(CSMOptimizationMode csmOptimizationMode) { _csmOptimizationMode = csmOptimizationMode; }
    inline void SetShadowFixedArea(bool fixedArea) 
    {
        _shadowFixedArea = fixedArea;
        Activate();
    }
    inline void SetShadowNear(float nearValue) { _shadowNear = nearValue; }
    inline void SetShadowFar(float farValue) { _shadowFar = farValue; }
    inline void SetShadowOrthoSize(float orthoSize) { _shadowOrthoSize = orthoSize; }

    inline bool IsShadowEnabled() const { return _shadowEnabled; }
    inline PCFType GetShadowPcf() const { return _shadowPcf; }
    inline float GetShadowBias() const { return _shadowBias; }
    inline float GetShadowNormalBias() const { return _shadowNormalBias; }
    inline float GetShadowSaturation() const { return _shadowSaturation; }
    inline float GetShadowDistance() const { return _shadowDistance; }
    inline float GetShadowInvisibleOcclusionRange() const { return _shadowInvisibleOcclusionRange; }
    inline CSMLevel GetCSMLevel() const { return _csmLevel; }
    inline float GetCSMLayerLambda() const { return _csmLayerLambda; }
    inline bool IsCSMNeedUpdate() const { return _isCSMNeedUpdate; }
    inline CSMOptimizationMode GetCSMOptimizationMode() const { return _csmOptimizationMode; }
    inline bool IsShadowFixedArea() const { return _shadowFixedArea; }
    inline float GetShadowNear() const { return _shadowNear; }
    inline float GetShadowFar() const { return _shadowFar; }
    inline float GetShadowOrthoSize() const { return _shadowOrthoSize; }

    inline const glm::vec3& GetDirection() const { return _dir; }
    inline void SetDirection(const glm::vec3& dir) { _dir = dir; }
    inline void SetIlluminanceHDR(float value) { _illuminanceHDR = value; }
    inline void SetIlluminanceLDR(float value) { _illuminanceLDR = value; }
    inline float GetIlluminanceHDR() const { return _illuminanceHDR; }
    inline float GetIlluminanceLDR() const { return _illuminanceLDR; }
    float GetIlluminance() const;
    void SetIlluminance(float value);

private:
    void Activate() const;

    float _illuminanceHDR{ Ambient::SUN_ILLUM };
    float _illuminanceLDR{ 1.F };
    glm::vec3 _dir{ 1.0F, -1.0F, -1.0F };

    bool _shadowEnabled{ false };
    PCFType _shadowPcf{ PCFType::HARD };
    float _shadowBias{ 0.0F };
    float _shadowNormalBias{ 0.0F };
    float _shadowSaturation{ 0.75F };
    float _shadowDistance{ 50.0F };
    float _shadowInvisibleOcclusionRange{ 200.0F };
    CSMLevel _csmLevel{ CSMLevel::LEVEL_3 };
    float _csmLayerLambda{ 0.75F };
    bool _isCSMNeedUpdate{ false };
    CSMOptimizationMode _csmOptimizationMode{ CSMOptimizationMode::REMOVE_DUPLICATES };
    bool _shadowFixedArea{ false };
    float _shadowNear{ 0.1F };
    float _shadowFar{ 10.0F };
    float _shadowOrthoSize{ 1.0F };

    DISALLOW_COPY_MOVE_ASSIGN(DirectionalLight)
};

}