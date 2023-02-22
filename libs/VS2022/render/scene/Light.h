#pragma once

#include "Ptr.h"
#include "Node.h"
#include "Macros.h"

#include <glm/glm.hpp>
#include <string>

namespace ll
{

    class RenderScene;

enum class LightType 
{
    DIRECTIONAL,
    SPHERE,
    SPOT,
    UNKNOWN,
};


class Light
{
public:
    Light();
    virtual ~Light();

    inline void AttachToScene(RenderScene* scene) { _scene = scene; }
    inline void DetachFromScene() { _scene = nullptr; }

    void Destroy();

    virtual void Initialize() 
    {
        _color = glm::vec3(1, 1, 1);
        _colorTemp = 6550.F;
    }

    virtual void Update() {};

    inline bool IsBaked() const { return _baked; }
    inline void SetBaked(bool val) { _baked = val; }

    inline const glm::vec3& getColor() const { return _color; }
    inline void SetColor(const glm::vec3& color) { _color = color; }

    inline bool IsUseColorTemperature() const { return _useColorTemperature; }
    inline void SetUseColorTemperature(bool value) { _useColorTemperature = value; }

    inline float GetColorTemperature() const { return _colorTemp; }
    inline void SetColorTemperature(float val) 
    {
        _colorTemp = val;
        SetColorTemperatureRGB(ColorTemperatureToRGB(val));
    }

    inline Node* GetNode() const { return _node.get(); }
    void SetNode(Node* node);

    inline LightType GetType() const { return _type; }
    inline void SetType(LightType type) { _type = type; }

    inline const std::string& GetName() const { return _name; }
    inline void setName(const std::string& name) { _name = name; }

    inline RenderScene* GetScene() const { return _scene; }

    inline const glm::vec3& GetColorTemperatureRGB() const { return _colorTemperatureRGB; }
    inline void SetColorTemperatureRGB(const glm::vec3& value) { _colorTemperatureRGB = value; }

    static float nt2lm(float size);
    static glm::vec3 ColorTemperatureToRGB(float kelvin);

protected:
    bool _useColorTemperature{ false };
    bool _baked{ false };
    IntrusivePtr<Node> _node;
    float _colorTemp{ 6550.F };
    LightType _type{ LightType::UNKNOWN };
    std::string _name;
    RenderScene* _scene{ nullptr };
    glm::vec3 _color{ 1, 1, 1 };
    glm::vec3 _colorTemperatureRGB;
    glm::vec3 _forward{ 0, 0, -1 };

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(Light)

};

}