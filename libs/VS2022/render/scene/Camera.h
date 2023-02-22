#pragma once

#include "../base/Ptr.h"
#include "../base/Macros.h"
#include "../base/Frustum.h"
#include "../base/Def_common.h"
#include "../pipeline/Define.h"

#include <glm/glm.hpp>
#include <string>
#include <optional>

namespace ll
{

    class Ray;
    class Node;
    class Device;
    class RenderScene;
    class RenderWindow;
    class GeometryRenderer;

enum class CameraAperture 
{
    F1_8,
    F2_0,
    F2_2,
    F2_5,
    F2_8,
    F3_2,
    F3_5,
    F4_0,
    F4_5,
    F5_0,
    F5_6,
    F6_3,
    F7_1,
    F8_0,
    F9_0,
    F10_0,
    F11_0,
    F13_0,
    F14_0,
    F16_0,
    F18_0,
    F20_0,
    F22_0,
};

enum class CameraISO 
{
    ISO100,
    ISO200,
    ISO400,
    ISO800,
};

enum class CameraShutter 
{
    D1,
    D2,
    D4,
    D8,
    D15,
    D30,
    D60,
    D125,
    D250,
    D500,
    D1000,
    D2000,
    D4000,
};

enum class CameraProjection 
{
    ORTHO,
    PERSPECTIVE,
    UNKNOWN
};

enum class CameraFOVAxis 
{
    VERTICAL,
    HORIZONTAL,
};

enum class CameraType 
{
    DEFAULT = -1,
    LEFT_EYE = 0,
    RIGHT_EYE = 1,
    MAIN = 2,
};

enum class TrackingType 
{
    NO_TRACKING = 0,
    POSITION_AND_ROTATION = 1,
    POSITION = 2,
    ROTATION = 3,
};

struct ICameraInfo 
{
    std::string name;
    Node* node{ nullptr };
    CameraProjection projection;
    
    std::optional<uint32_t> targetDisplay;
    RenderWindow* window{ nullptr };
    uint32_t priority{ 0 };
    std::optional<std::string> pipeline;
    CameraType cameraType{ CameraType::DEFAULT };
    TrackingType trackingType{ TrackingType::NO_TRACKING };
};

class Camera
{
public:
    static constexpr int32_t SKYBOX_FLAG{ static_cast<int32_t>(ClearFlagBit::STENCIL) << 1 };

    explicit Camera(Device* device);
    ~Camera();

    bool Initialize(const ICameraInfo& info);
    void Destroy();
    void AttachToScene(RenderScene* scene);
    void DetachFromScene();
    void Resize(uint32_t width, uint32_t height);
    void SetFixedSize(uint32_t width, uint32_t height);
    void SyncCameraEditor(const Camera& camera);
    void Update(bool forceUpdate = false);
    void ChangeTargetWindow(RenderWindow* window);

    Ray ScreenPointToRay(float x, float y);

    glm::vec3 ScreenToWorld(const glm::vec3& screenPos);

    glm::vec3 WorldToScreen(const glm::vec3& worldPos);

    glm::mat4 WorldMatrixToScreen(const glm::mat4& worldMatrix, uint32_t width, uint32_t height);

    void SetNode(Node* val);
    inline Node* GetNode() const { return _node.get(); }

    inline void SetEnabled(bool val) { _enabled = val; }
    inline bool IsEnabled() const { return _enabled; }

    inline void SetOrthoHeight(float val) 
    {
        _orthoHeight = val;
        _isProjDirty = true;
    }
    inline float GetOrthoHeight() const { return _orthoHeight; }

    inline void SetProjectionType(CameraProjection val) 
    {
        _proj = val;
        _isProjDirty = true;
    }
    inline CameraProjection GetProjectionType() const { return _proj; }

    inline void SetFovAxis(CameraFOVAxis axis) 
    {
        _fovAxis = axis;
        _isProjDirty = true;
    }
    inline CameraFOVAxis GetFovAxis() const { return _fovAxis; }

    inline void SetFov(float fov) 
    {
        _fov = fov;
        _isProjDirty = true;
    }
    inline float GetFov() const { return _fov; }

    inline void SetNearClip(float nearClip) 
    {
        _nearClip = nearClip;
        _isProjDirty = true;
    }
    inline float GetNearClip() const { return _nearClip; }

    inline void SetFarClip(float farClip) 
    {
        _farClip = farClip;
        _isProjDirty = true;
    }
    inline float GetFarClip() const { return _farClip; }

    inline void SetClearColor(const Color& val) { _clearColor = val; }
    inline const Color& GetClearColor() const { return _clearColor; }

    inline const glm::vec4& GetViewport() const { return _viewport; }
    void GetViewport(const Rect& val);
    void GetViewportInOrientedSpace(const Rect& val);

    inline RenderScene* GetScene() const { return _scene; }
    inline const std::string& GetName() const { return _name; }
    inline uint32_t GetWidth() const { return _width; }
    inline uint32_t GetHeight() const { return _height; }
    inline float GetAspect() const { return _aspect; }
    inline const glm::mat4& GetMatView() const { return _matView; }
    inline const glm::mat4& GetMatProj() const { return _matProj; }
    inline const glm::mat4& GetMatProjInv() const { return _matProjInv; }
    inline const glm::mat4& GetMatViewProj() const { return _matViewProj; }
    inline const glm::mat4& GetMatViewProjInv() const { return _matViewProjInv; }

    inline void SetFrustum(const Frustum& val) 
    {
        *_frustum = val;
    }
    inline const Frustum& GetFrustum() const { return *_frustum; }

    inline void SetWindow(RenderWindow* val) { _window = val; }
    inline RenderWindow* GetWindow() const { return _window; }

    inline void SetForward(const glm::vec3& val) { _forward = val; }
    inline const glm::vec3& GetForward() const { return _forward; }

    inline void SetPosition(const glm::vec3& val) { _position = val; }
    inline const glm::vec3& GetPosition() const { return _position; }

    inline void SetVisibility(uint32_t vis) { _visibility = vis; }
    inline uint32_t GetVisibility() const { return _visibility; }

    inline uint32_t GetPriority() const { return _priority; }
    inline void SetPriority(uint32_t val) { _priority = val; }

    inline void SetAperture(CameraAperture val) 
    {
        _aperture = val;
        _apertureValue = Camera::FSTOPS[static_cast<int>(_aperture)];
        UpdateExposure();
    }
    inline CameraAperture GetAperture() const { return _aperture; }

    inline float GetApertureValue() const { return _apertureValue; }

    inline void SetShutter(CameraShutter val) 
    {
        _shutter = val;
        _shutterValue = Camera::SHUTTERS[static_cast<int>(_shutter)];
        UpdateExposure();
    }
    inline CameraShutter GetShutter() const { return _shutter; }

    inline float GetShutterValue() const { return _shutterValue; }

    inline void SetIso(CameraISO val) 
    {
        _iso = val;
        _isoValue = Camera::ISOS[static_cast<int>(_iso)];
        UpdateExposure();
    }
    inline CameraISO GetIso() const { return _iso; }

    inline float GetIsoValue() const { return _isoValue; }

    inline void SetEc(float val) { _ec = val; }
    inline float GetEc() const { return _ec; }

    inline float GetExposure() const { return _exposure; }

    inline ClearFlagBit GetClearFlag() const { return _clearFlag; }
    inline void SetClearFlag(ClearFlagBit flag) { _clearFlag = flag; }

    inline float GetClearDepth() const { return _clearDepth; }
    inline void SetClearDepth(float depth) { _clearDepth = depth; }

    inline uint32_t GetClearStencil() const { return _clearStencil; }
    inline void SetClearStencil(uint32_t stencil) { _clearStencil = stencil; }

    inline bool IsWindowSize() const { return _isWindowSize; }
    inline void SetWindowSize(bool val) { _isWindowSize = val; }

    inline float GetScreenScale() const { return _screenScale; }
    inline void SetScreenScale(float val) { _screenScale = val; }

    inline SurfaceTransform GetSurfaceTransform() const { return _curTransform; }

    void InitGeometryRenderer();
    inline GeometryRenderer* SetGeometryRenderer() const 
    {
        return nullptr;
    }

    void DetachCamera();

    inline CameraType GetCameraType() const { return _cameraType; }
    inline void SetCameraType(CameraType type) { _cameraType = type; }

    inline TrackingType GetTrackingType() const { return _trackingType; }
    inline void SetTrackingType(TrackingType type) { _trackingType = type; }

    inline bool IsCullingEnabled() const { return _isCullingEnabled; }
    inline void SetCullingEnable(bool val) { _isCullingEnabled = val; }
protected:
    void SetExposure(float ev100);

private:
    void UpdateExposure();
    void UpdateAspect(bool oriented = true);

    bool _isWindowSize{ true };
    float _screenScale{ 0.F };
    Device* _device{ nullptr };
    RenderScene* _scene{ nullptr };
    IntrusivePtr<Node> _node;
    std::string _name;
    bool _enabled{ false };
    bool _isCullingEnabled{ true };
    CameraProjection _proj{ CameraProjection::UNKNOWN };
    float _aspect{ 0.F };
    float _orthoHeight{ 10.0F };
    CameraFOVAxis _fovAxis{ CameraFOVAxis::VERTICAL };
    float _fov{ static_cast<float>(glm::radians(45.F)) };
    float _nearClip{ 1.0F };
    float _farClip{ 1000.0F };
    Color _clearColor{ 0.2, 0.2, 0.2, 1 };
    glm::vec4 _viewport{ 0, 0, 1, 1 };
    glm::vec4 _orientedViewport{ 0, 0, 1, 1 };
    SurfaceTransform _curTransform{ SurfaceTransform::IDENTITY };
    bool _isProjDirty{ true };
    glm::mat4 _matView;
    glm::mat4 _matProj;
    glm::mat4 _matProjInv;
    glm::mat4 _matViewProj;
    glm::mat4 _matViewProjInv;
    Frustum* _frustum{ nullptr };
    glm::vec3 _forward;
    glm::vec3 _position;
    uint32_t _priority{ 0 };
    CameraAperture _aperture{ CameraAperture::F16_0 };
    float _apertureValue{ 0.F };
    CameraShutter _shutter{ CameraShutter::D125 };
    float _shutterValue{ 0.F };
    CameraISO _iso{ CameraISO::ISO100 };
    float _isoValue{ 0.F };
    float _ec = { 0.F };
    RenderWindow* _window{ nullptr };
    uint32_t _width{ 0 };
    uint32_t _height{ 0 };
    ClearFlagBit _clearFlag{ ClearFlagBit::NONE };
    float _clearDepth{ 1.0F };
    CameraType _cameraType{ CameraType::DEFAULT };
    TrackingType _trackingType{ TrackingType::NO_TRACKING };

    static const std::vector<float> FSTOPS;
    static const std::vector<float> SHUTTERS;
    static const std::vector<float> ISOS;

    uint32_t _visibility = CAMERA_DEFAULT_MASK;
    float _exposure{ 0.F };
    uint32_t _clearStencil{ 0 };

    DISALLOW_COPY_MOVE_ASSIGN(Camera)
};

}